/*
** @author:止水清潇menghuanlater
** @date:2017-12-10
** @location:BUAA
*/
//数据段起始地址:0x10010000
#include "globalFunction.h"
#include <fstream>
#include <cstring>
#include <map>
#include "error.h"

#define TEMP_REGISTER 6 //$t4~$t9

static int labelCount = 0;//全局标签计数器
static int tmpVarCount = 0;//全局临时变量计数器
static string funcName = "GLOBAL";//临时变量的所属域,当域发生变化,整个计数器重新洗牌
static int globalStrCount = 0;//全局字符串计数器


static unsigned strMemSize = 0;//字符串占据的大小
unsigned int paramSpBegin;//临时参数栈空间指针
unsigned int currentParamSp;//当前参数栈指针的地址
const int tempStackMax = 100;//设置临时参数栈最大为100字节(最多有25个参数)
const unsigned int dataBaseAddr = 0x10010000;//数据段起始地址
unsigned int returnValueSpace;//函数返回值存放点
unsigned int funcBeginAddr;//整体函数栈的起始地址(即全局数据区域起始地址)


const string tmpCodeToFileName = "tmpCode.txt";//中间代码输出文件
const string mipsCodeToFileName = "mips.asm";//最终汇编代码输出文件

extern vector<FourYuanItem> globalTmpCodeArr;
extern vector<SymbolTableItem> globalSymbolTable;

vector<FourYuanItem> globalTmpCodeArr;//中间代码生成集合
vector<string> constStringSet;//程序需要打印的常量字符串集合,放在.data域
map<string, string> stringWithLabel;//字符串与伪指令标签
map<string, unsigned> maxTempOrderMap;//每个函数最大的临时变量编号

string generateLabel() {
	labelCount++;
	char x[10] = { '\0' };
	sprintf(x, "%d", labelCount);
	return ("Label" + string(x));
}

string generateVar(string func) {
	if (func != funcName) {
		funcName = func;
		tmpVarCount = 0;
	}
	tmpVarCount++;
	char x[10] = {'\0'};
	sprintf(x,"%d",tmpVarCount);
	return ("T" + string(x));
}

string generateStrLabel() {
	globalStrCount++;
	char x[10] = {'\0'};
	sprintf(x,"%d",globalStrCount);
	return ("String" + string(x));
}

//取消字符串中的转义字符，所有的\都加上一个\即可
void cancelEscapeChar(string  & target) {
	vector< unsigned int> indexSets;
	for (unsigned int i = 0; i < target.size(); i++) {
		if(target.at(i) == '\\'){
			indexSets.push_back(i);
		}
	}
	for (unsigned int i = 0; i < indexSets.size(); i++) {
		target.insert(indexSets.at(i)+i,"\\");
	}
}

bool isStringDigit(string target) {
	for (unsigned i = 0; i < target.size(); i++) {
		if (target.at(i) > '9' || target.at(i) < '0') {
			return false;
		}
	}
	return true;
}

int stringToInt(string target) {
	int outcome = 0;
	bool isMinus = false;
	for (unsigned i = 0; i < target.size(); i++) {
		if (i == 0 && target.at(i) == '-') {
			isMinus = true;
			continue;
		}
		if (target.at(i) < '0' || target.at(i) > '9')
			break;
		outcome = outcome * 10 + target.at(i) - '0';
	}
	return isMinus?(-outcome):outcome;
}

void turnToPostfixExp(vector<PostfixItem>tar, vector<PostfixItem> & obj) {
	vector<PostfixItem> tmp;
	if (tar.size() == 1) {
		obj.push_back(tar.at(0));
		return;
	}
	if (tar.size() > 0) {
		PostfixItem t = tar.at(0);
		if (t.type == CharType && (t.number == '+' || t.number == '-')) {
			if (t.number == '-') {
				t.type = IntType;
				t.number = 0;
				tar.insert(tar.begin(),t);
			}
			else {
				tar.erase(tar.begin());
			}
		}
	}
	for (unsigned int i = 0; i < tar.size(); i++) {
		PostfixItem item = tar.at(i);
		if (item.type == CharType) {
			switch (item.number) {
				case '+':
				case '-':
					while (tmp.size() != 0) {
						obj.push_back(tmp.at(tmp.size()-1));
						tmp.pop_back();
					}
					tmp.push_back(item);
					break;
				case '*':
				case '/':
					while (tmp.size() != 0) {
						if (tmp.at(tmp.size() - 1).number == '*' || tmp.at(tmp.size() - 1).number == '/') {
							obj.push_back(tmp.at(tmp.size() - 1));
							tmp.pop_back();
						}
						else {
							break;
						}
					}
					tmp.push_back(item);
					break;
				default:obj.push_back(item);
			}
		}
		else {
			obj.push_back(item);
		}
	}
	while (tmp.size() != 0) {
		obj.push_back(tmp.at(tmp.size()-1));
		tmp.pop_back();
	}
}

//生成计算代码
string calculateExp(vector<PostfixItem> & tar, bool & isSure,ValueType & t,int & ret,int line,bool isCache,vector<FourYuanItem> & cache,string funcName) {
	PostfixItem item,item1;
	FourYuanItem item2;
	string tmpVar;
	isSure = false;
	vector<PostfixItem> tmp;
	if (tar.size() == 1) {
		item = tar.at(0);
		if (item.type == IntType) {
			t = IntType;
			ret = item.number;
			isSure = true;
			return "";
		}
		else if (item.type == CharType) {
			t = CharType;
			ret = item.number;
			isSure = true;
			return "";
		}
		else {
			if (!item.isNotCharVar) {//是字符型变量
				t = CharType;
			}
			return item.str;
		}
	}
	else {
		t = IntType;
		for (unsigned int i = 0; i < tar.size(); i++) {
			item = tar.at(i);
			if (item.type == CharType) {
				char x[15] = { '\0' };
				item2.type = AssignState;
				item2.isTargetArr = item2.isLeftArr = false;
				switch (item.number) {
					case '+':
					case '-': {
						if (tmp.size() > 1) {
							bool isAbleDirect = true;
							int leftDigit, rightDigit;
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
								isAbleDirect = false;
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.right = x;
								rightDigit = tmp.at(tmp.size() - 1).number;
								tmp.pop_back();
							}
							memset(x, 0, 15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.left = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
								isAbleDirect = false;
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.left = x;
								leftDigit = tmp.at(tmp.size() - 1).number;
								tmp.pop_back();
							}
							if (isAbleDirect) {
								item1.type = IntType;
								item1.number = (item.number == '+') ? (leftDigit + rightDigit) : (leftDigit - rightDigit);
								tmp.push_back(item1);
								break;
							}
							tmpVar = generateVar(funcName);
							item2.target = tmpVar;
							item2.op = item.number;
							if (isCache) {
								cache.push_back(item2);
							}
							else {
								globalTmpCodeArr.push_back(item2);
							}
							item1.type = StringType;
							item1.str = tmpVar;
							tmp.push_back(item1);
						}
						break;
					}
					case '*':
					case '/': {
						if (tmp.size() > 1) {
							bool isAbleDirect = true;
							int leftDigit, rightDigit;

							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size() - 1).str;
								isAbleDirect = false;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.right = x;
								rightDigit = tmp.at(tmp.size() - 1).number;
								tmp.pop_back();
							}
							memset(x, 0, 15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.left = tmp.at(tmp.size() - 1).str;
								isAbleDirect = false;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.left = x;
								leftDigit = tmp.at(tmp.size() - 1).number;
								tmp.pop_back();
								if (item.number == '/' && item2.right == "0") {
									cout << "Error(at line " << line << " surround): exist div 0 situation." << endl;
									break;
								}
							}
							if (isAbleDirect) {
								item1.type = IntType;
								item1.number = (item.number == '*') ? (leftDigit*rightDigit) : (leftDigit / rightDigit);
								tmp.push_back(item1);
								break;
							}

							tmpVar = generateVar(funcName);
							item2.target = tmpVar;
							item2.op = item.number;
							if (isCache) {
								cache.push_back(item2);
							}
							else {
								globalTmpCodeArr.push_back(item2);
							}
							item1.type = StringType;
							item1.str = tmpVar;
							tmp.push_back(item1);
						}
						break;
					}
					default:tmp.push_back(item);
				}
			}
			else {
				tmp.push_back(item);
			}
		}
		if (tmp.size() >= 1) {
			if (tmp.at(0).type == IntType) {
				isSure = true;
				t = IntType;
				ret = tmp.at(0).number;
				return "";
			}
			return tmp.at(0).str;
		}
		else {
			return "";
		}
	}
}

void writeTmpCodeToFile() {
	ofstream out(tmpCodeToFileName, ios::out);
	string funcName = "GLOBAL";
	for (unsigned int i = 0; i < globalTmpCodeArr.size(); i++) {
		FourYuanItem item = globalTmpCodeArr.at(i);
		switch (item.type) {
		case ValueParamDeliver:
			out << "Push " << item.target << endl;
			break;
		case FunctionCall:
			out << "Call " << item.target << endl;
			break;
		case AssignState:
			if (item.isTargetArr) {
				out << item.target << "[" << item.index1 << "] = ";
				if (item.isLeftArr) {
					out << item.left << "[" << item.index2 << "]" << endl;
				}
				else {
					out << item.left << " " << item.op << " " << item.right << endl;
				}
			}
			else {
				//查询是否为临时变量
				if (item.target.size() > 0 && item.target.at(0) == 'T') {
					map<string, unsigned>::iterator iter = maxTempOrderMap.find(funcName);
					unsigned order = stringToInt(item.target.substr(1));
					if (iter == maxTempOrderMap.end()) {
						maxTempOrderMap.insert(map<string,unsigned>::value_type(funcName,order));
					}
					else {
						if (iter->second < order)
							iter->second = order;
					}
				}
				out << item.target << " = ";
				if (item.isLeftArr) {
					out << item.left << "[" << item.index2 << "]" << endl;
				}
				else {
					out << item.left << " " << item.op << " " << item.right << endl;
				}
			}
			break;
		case Label:
			out << item.target << ":" << endl;
			break;
		case FunctionDef:
			funcName = item.target;
			if (item.funcType == VoidType) {
				out << "void " + item.target << "()" << endl;
			}
			else if (item.funcType == ReturnIntType) {
				out << "int " + item.target << "()" << endl;
			}else{
				out << "char " + item.target << "()" << endl;
			}
			break;
		case ParamDef:
			if (item.valueType == IntType) {
				out << "Param int " << item.target << endl;
			}
			else {
				out << "Param char " << item.target << endl;
			}
			break;
		case Jump:
			out << "Jump " << item.target << endl;
			break;
		case BEZ:
			out << "BEZ " << item.left << " " << item.target << endl;
			break;
		case BNZ:
			out << "BNZ " << item.left << " " << item.target << endl;
			break;
		case BLZ:
			out << "BLZ " << item.left << " " << item.target << endl;
			break;
		case BLEZ:
			out << "BLEZ " << item.left << " " << item.target << endl;
			break;
		case BGZ:
			out << "BGZ " << item.left << " " << item.target << endl;
			break;
		case BGEZ:
			out << "BGEZ " << item.left << " " << item.target << endl;
			break;
		case ReadChar:
			out << "Read Char " << item.target << endl;
			break;
		case ReadInt:
			out << "Read Int " << item.target << endl;
			break;
		case PrintStr:
			out << "Print string " << '\"'<< item.target <<'\"'<< endl;
			cancelEscapeChar(item.target);
			constStringSet.push_back(item.target);
			break;
		case PrintChar:
			if (item.target == "\n") {
				out << "New Line." << endl;
			}else
				out << "Print char " << '\'' << item.target.at(0) << '\'' << endl;
			break;
		case PrintInt:
			out << "Print int " << stringToInt(item.target) << endl;
			break;
		case PrintId:
			out << "Print id " << item.target << endl;
			break;
		case ReturnInt:
			out << "Ret int " << stringToInt(item.target) << endl;
			break;
		case ReturnChar:
			out << "Ret char " << '\'' << item.target.at(0) << '\'' << endl;
			break;
		case ReturnId:
			out << "Ret id " << item.target << endl;
			break;
		case ReturnEmpty:
			out << "Ret" << endl;
			break;
		default:break;
		}
	}
	out.close();
}
//最终汇编代码生成相关的函数
void generateMipsCode() {
	ofstream out(mipsCodeToFileName, ios::out);
	//首先遍历生成.data的宏汇编伪指令
	out << ".data" << endl;
	generateData(out);
	//修约strMemSize成为4的倍数
	strMemSize = strMemSize + 4 - (strMemSize % 4);
	//临时参数栈基址设置为strMemSize+4
	paramSpBegin = strMemSize+4+dataBaseAddr;
	currentParamSp = paramSpBegin;
	returnValueSpace = strMemSize+dataBaseAddr;
	funcBeginAddr = paramSpBegin + tempStackMax;
	//生成.globl main
	out << ".globl main" << endl;
	//下面着重生成.text
	out << ".text" << endl;
	generateText(out);
	
	out << "#accomplish generate mips code." << endl;
	out.close();
}
//生成汇编Data段指令，最终地址需要给出,用于知道整个函数运行栈的开始点在哪
void generateData(ofstream & out) {
	for (unsigned int i = 0; i < constStringSet.size(); i++) {
		string item = constStringSet.at(i);
		//检查是否是重复的公共字符串
		map<string,string>::iterator iter = stringWithLabel.find(item);
		if(iter!=stringWithLabel.end())
			continue;
		strMemSize += item.size() + 1;//'\0'占一个字节
		string label = generateStrLabel();
		out << "\t" << label << ":.asciiz \"" << item << "\"" << endl;
		stringWithLabel.insert(map<string, string>::value_type(item, label));
	}
}

//全局的变量
void getAddrOfGlobal(string name,string targetReg,ofstream & out) {
	int number = 0;
	unsigned int i;
	for (i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() != Constant)
			break;
	}
	for (; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getId() == name)
			break;
		if (item.getArrSize() == 0)
			number += 4;
		else
			number += item.getArrSize() * 4;
	}
	out << "li " << targetReg << " " << funcBeginAddr + number <<endl;
}
//局部的变量
void getAddrOfLocal(string funcName,string eleName,string targetReg,ofstream & out) {
	int number = 0;
	unsigned int i;
	for (i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() == Function && item.getId() == funcName)
			break;
	}
	for (i = i + 1; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() == Constant)
			continue;
		if (item.getId() == eleName) {
			break;
		}
		if (item.getArrSize() == 0)
			number += 4;
		else
			number += item.getArrSize() * 4;
	}
	out << "addiu " << targetReg << " $fp " << number + 8 << endl;
}
//获取临时变量的地址
void getAddrOfTemp(int order, string targetReg,ofstream & out) {
	//@need:order > TEMP_REGISTER
	out << "move " << targetReg << " $k0" << endl;
	out << "addiu " << targetReg << " " << targetReg << " " << (order-1-TEMP_REGISTER) * 4 << endl;
}

//生成Text段代码的辅助函数
//赋值语句处理(优化了右操作数为0的运算)
void helpAssignStatement(FourYuanItem item,ofstream & out) {
	//使用$t0~$t7
	if (item.isTargetArr) {//a[i] = temp1
		//首先最终赋值元素的地址放在$t0寄存器中,运算结果放在$t1寄存器
		//数组型变量是以G+order+id的形式出现
		int order = stringToInt(item.target.substr(1));
		SymbolTableItem arrayItem = globalSymbolTable.at(order);
		//数组首地址放在$t0中
		if (arrayItem.getFuncName() == "GLOBAL") {//是全局的
			getAddrOfGlobal(arrayItem.getId(),"$t0",out);
		}
		else {
			getAddrOfLocal(arrayItem.getFuncName(),arrayItem.getId(),"$t0",out);
		}
		//观察index1即数组下标
		string index1 = item.index1;
		if (index1.at(0) == 'G') {//在符号表
			order = stringToInt(index1.substr(1));
			SymbolTableItem index1Item = globalSymbolTable.at(order);
			//地址放在$t1
			if (index1Item.getFuncName() == "GLOBAL") {
				getAddrOfGlobal(index1Item.getId(),"$t1",out);
			}
			else {
				getAddrOfLocal(index1Item.getFuncName(),index1Item.getId(),"$t1",out);
			}
			//放在$t1
			out << "lw $t1 0($t1)" << endl;//下标值存入$t1
		}
		else if (index1.at(0) == 'T') {//在临时变量表
			//放在$t1
			int g = stringToInt(index1.substr(1));
			if (g > TEMP_REGISTER) {
				getAddrOfTemp(g, "$t1", out);
				out << "lw $t1 0($t1)" << endl;
			}
			else {
				out << "move $t1 " << "$t" << (g + 3)<<endl;
			}
		}
		else {//纯数字
			int number = stringToInt(index1);
			out << "li $t1 " << number<<endl;
		}
		out << "li $t2 4" << endl;
		out << "mult $t1 $t2" << endl;
		out << "mflo $t1" << endl;
		out << "addu $t0 $t0 $t1" << endl;//最终赋值元素地址存入了$t0
		//结构决定了下面是left + right结构 --->运算结果存在$t1 left值放在$t1 right值放在$t2
		string left = item.left;
		string right = item.right;
		char op = item.op;
		if (left.at(0) == 'G') {//符号表
			order = stringToInt(left.substr(1));
			SymbolTableItem leftItem = globalSymbolTable.at(order);
			if (leftItem.getFuncName() == "GLOBAL") {
				getAddrOfGlobal(leftItem.getId(),"$t1",out);
			}
			else {
				getAddrOfLocal(leftItem.getFuncName(),leftItem.getId(),"$t1",out);
			}
			out << "lw $t1 0($t1)" << endl;
		}
		else if (left.at(0) == 'T') {//临时变量表
			int g = stringToInt(left.substr(1));
			if (g > TEMP_REGISTER) {
				getAddrOfTemp(g, "$t1", out);
				out << "lw $t1 0($t1)" << endl;
			}
			else {
				out << "move $t1 " << "$t" << (g + 3)<<endl;
			}
		}
		else if (left == "Ret") {//函数调用的返回值
			out << "lw $t1 " << returnValueSpace << "($0)" << endl;
		}
		else {//数字
			out << "li $t1 " << stringToInt(left) << endl;
		}
		//右操作数为"0",不需要生成代码
		if (right != "0") {
			if (right.at(0) == 'G') {//符号表
				order = stringToInt(right.substr(1));
				SymbolTableItem rightItem = globalSymbolTable.at(order);
				if (rightItem.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(rightItem.getId(),"$t2",out);
				}
				else {
					getAddrOfLocal(rightItem.getFuncName(),rightItem.getId(),"$t2",out);
				}
				out << "lw $t2 0($t2)" << endl;
			}
			else if (right.at(0) == 'T') {//临时变量表
				int g = stringToInt(right.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$t2", out);
					out << "lw $t2 0($t1)" << endl;
				}
				else {
					out << "move $t2 " << "$t" << (g + 3)<<endl;
				}
			}
			else {//数字
				out << "li $t2 " << stringToInt(right) << endl;
			}
			if (op == '+') {
				out << "addu $t1 $t1 $t2" << endl;
			}
			else if (op == '-') {
				out << "subu $t1 $t1 $t2" << endl;
			}
			else if (op == '*') {
				out << "mult $t1 $t2" << endl;
				out << "mflo $t1" << endl;
			}
			else if (op == '/') {
				out << "div $t1 $t2" << endl;
				out << "mflo $t1" << endl;
			}
		}
		else {
			if (item.op == '*')
				out << "move $t1 $0" << endl;
		}
	}
	else{
		//$t0存放target地址
		bool isTemp = false;
		int g, g1;
		if (item.target.at(0) == 'G') {//符号表内的变量
			int order = stringToInt(item.target.substr(1));
			SymbolTableItem item = globalSymbolTable.at(order);
			if (item.getFuncName() == "GLOBAL") {
				getAddrOfGlobal(item.getId(),"$t0",out);
			}
			else {
				getAddrOfLocal(item.getFuncName(),item.getId(),"$t0",out);
			}
		}
		else if (item.target.at(0) == 'T') {//临时变量
			g1 = g = stringToInt(item.target.substr(1));
			if (g > TEMP_REGISTER) {
				getAddrOfTemp(stringToInt(item.target.substr(1)), "$t0", out);
			}
			else {
				isTemp = true;
			}
		}
		//分析left
		if (item.isLeftArr) {
			//单纯的数组取值
			string left = item.left;
			int order = stringToInt(left.substr(1));
			SymbolTableItem x = globalSymbolTable.at(order);
			//分析索引下标,将数组地址取出放在$t1
			if (x.getFuncName() == "GLOBAL") {
				getAddrOfGlobal(x.getId(),"$t1",out);
			}
			else {
				getAddrOfLocal(x.getFuncName(),x.getId(),"$t1",out);
			}
			//下标地址取出放在$t2
			string index2 = item.index2;
			if (index2.at(0) == 'G') {//在符号表
				order = stringToInt(index2.substr(1));
				SymbolTableItem index2Item = globalSymbolTable.at(order);
				if (index2Item.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(index2Item.getId(),"$t2",out);
				}
				else {
					getAddrOfLocal(index2Item.getFuncName(),index2Item.getId(),"$t2",out);
				}
				out << "lw $t2 0($t2)" << endl;
			}
			else if (index2.at(0) == 'T') {//在临时变量表
				g = stringToInt(index2.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$t2", out);
					out << "lw $t2 0($t2)" << endl;
				}
				else {
					out << "move $t2 " << "$t" << (g + 3)<<endl;
				}
			}
			else {//纯数字
				out << "li $t2 " << stringToInt(index2) << endl;
			}
			out << "li $t3 4" << endl;
			out << "mult $t2 $t3" << endl;
			out << "mflo $t2" << endl;
			out << "addu $t1 $t1 $t2" << endl;
			//取出数据,放在$t1
			out << "lw $t1 0($t1)" << endl;
		}
		else {
			//左右操作数
			int order;
			string left = item.left;
			string right = item.right;
			char op = item.op;
			if (left.at(0) == 'G') {//符号表
				order = stringToInt(left.substr(1));
				SymbolTableItem leftItem = globalSymbolTable.at(order);
				if (leftItem.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(leftItem.getId(),"$t1",out);
				}
				else {
					getAddrOfLocal(leftItem.getFuncName(),leftItem.getId(),"$t1",out);
				}
				out << "lw $t1 0($t1)" << endl;
			}
			else if (left.at(0) == 'T') {//临时变量表
				g = stringToInt(left.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$t1", out);
					out << "lw $t1 0($t1)" << endl;
				}
				else {
					out << "move $t1 " << "$t" << (g + 3)<<endl;
				}
			}
			else if (left == "Ret") {//函数调用的返回值
				out << "lw $t1 " << returnValueSpace << "($0)" << endl;
			}
			else {//数字
				out << "li $t1 " << stringToInt(left) << endl;
			}
			if (right != "0") {
				if (right.at(0) == 'G') {//符号表
					order = stringToInt(right.substr(1));
					SymbolTableItem rightItem = globalSymbolTable.at(order);
					if (rightItem.getFuncName() == "GLOBAL") {
						getAddrOfGlobal(rightItem.getId(), "$t2", out);
					}
					else {
						getAddrOfLocal(rightItem.getFuncName(), rightItem.getId(), "$t2", out);
					}
					out << "lw $t2 0($t2)" << endl;
				}
				else if (right.at(0) == 'T') {//临时变量表
					g = stringToInt(right.substr(1));
					if (g > TEMP_REGISTER) {
						getAddrOfTemp(g, "$t2", out);
						out << "lw $t2 0($t2)" << endl;
					}
					else {
						out << "move $t2 " << "$t" << (g + 3)<<endl;
					}
				}
				else {//数字
					out << "li $t2 " << stringToInt(right) << endl;
				}
				if (op == '+') {
					out << "addu $t1 $t1 $t2" << endl;
				}
				else if (op == '-') {
					out << "subu $t1 $t1 $t2" << endl;
				}
				else if (op == '*') {
					out << "mult $t1 $t2" << endl;
					out << "mflo $t1" << endl;
				}
				else if (op == '/') {
					out << "div $t1 $t2" << endl;
					out << "mflo $t1" << endl;
				}
			}
			else {
				if (item.op == '*')
					out << "move $t1 $0" << endl;
			}
		}
		if (isTemp) {
			out << "move $t" << (g1 + 3) << " $t1" << endl;
			return;
		}
	}
	//从$t1将值存入内存
	out << "sw $t1 0($t0)" << endl;
}
//函数定义处理(空间分配,数据保存等一系列操作)
int getGlobalVarSumSpace() {
	int number = 0;
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() == Function)
			break;
		if (item.getItemType() == Constant)
			continue;
		if (item.getArrSize() == 0)
			number += 4;
		else
			number += item.getArrSize() * 4;
	}
	return number;
}

void initializeStack(string funcName,ofstream & out) {
	//参数计数器
	int paramC = 0;
	int number = 0;//变量不进行初始化
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() == Function && item.getId() == funcName) {
			for (unsigned int j = i + 1; j < globalSymbolTable.size(); j++) {
				item = globalSymbolTable.at(j);
				if (item.getFuncName() != funcName)
					break;
				if (item.getItemType() == Constant)
					continue;
				if (item.getItemType() == Parament) {//是参数
					//借用$v1寄存器作为中转
					out << "lw $v1 " << paramSpBegin + paramC * 4 << "($0)" << endl;
					out << "sw $v1 0($sp)" << endl;
					paramC++;
					out << "addiu $sp $sp 4" << endl;
				}
				else if (item.getItemType() == Variable) {
					if (item.getArrSize() == 0) {
						number += 4;
					}
					else {
						number += 4 * item.getArrSize();
					}
				}
			}
			break;
		}
	}
	out << "addiu $sp $sp " << number << endl;
	//临时变量区入口地址确定,存放入$k0
	out << "move $k0 $sp" << endl;
	out << "move $k1 $0 " << endl;
	//分配所需最大的临时空间
	map<string, unsigned>::iterator iter = maxTempOrderMap.find(funcName);
	if (iter != maxTempOrderMap.end()) {
		if(iter->second>TEMP_REGISTER)
			out << "addiu $sp $sp " << (iter->second - TEMP_REGISTER) * 4<< endl;
		out << "addiu $k1 $0 " << iter->second << endl;
	}
}

void helpFunctionDef(string funcName, ofstream & out) {
	if (funcName == "main") {
		//main函数只需要做全局变量的数据分配
		int size = getGlobalVarSumSpace();
		out << "li $fp " << funcBeginAddr + size << endl;
		out << "addiu $sp $fp 8" << endl;
		initializeStack(funcName,out);
	}
	else {
		//将$k0,$k1寄存器的值保存入栈
		out << "sw $k0 0($sp)" << endl;
		out << "sw $k1 4($sp)" << endl;
		out << "sw $t4 8($sp)" << endl;
		out << "sw $t5 12($sp)" << endl;
		out << "sw $t6 16($sp)" << endl;
		out << "sw $t7 20($sp)" << endl;
		out << "sw $t8 24($sp)" << endl;
		out << "sw $t9 28($sp)" << endl;

		out << "addiu $sp $sp 32" << endl;
		//设置上一级函数的基地址
		out << "sw $fp 4($sp)" << endl;
		//设置fp
		out << "move $fp $sp" << endl;
		//设置返回地址
		out << "sw $ra 0($fp)" << endl;
		//初始化栈空间
		out << "addiu $sp $fp 8" << endl;
		initializeStack(funcName,out);
	}
}
//跳转语句B类统一处理,避免代码过度杂糅重复
void helpBJump(FourYuanItem item,ofstream & out) {
	//把判断的变量值存入$a1寄存器中,再调用转移函数
	string obj = item.left;
	if (obj.at(0) == 'G') {
		int order = stringToInt(obj.substr(1));
		SymbolTableItem item = globalSymbolTable.at(order);
		if (item.getFuncName() == "GLOBAL") {
			getAddrOfGlobal(item.getId(),"$a1",out);
		}
		else {
			getAddrOfLocal(item.getFuncName(),item.getId(), "$a1", out);
		}
		out << "lw $a1 0($a1)" << endl;
	}
	else if (obj.at(0) == 'T') {
		int g = stringToInt(obj.substr(1));
		if (g > TEMP_REGISTER) {
			getAddrOfTemp(g, "$a1", out);
			out << "lw $a1 0($a1)" << endl;
		}
		else {
			out << "move $a1 " << "$t" << (g + 3) << endl;
		}
	}
	switch (item.type)
	{
	case BEZ:
		out << "beq $a1 $0 " << item.target << endl;
		break;
	case BNZ:
		out << "bne $a1 $0 " << item.target << endl;
		break;
	case BLZ:
		out << "bltz $a1 " << item.target << endl;
		break;
	case BLEZ:
		out << "blez $a1 " << item.target << endl;
		break;
	case BGZ:
		out << "bgtz $a1 " << item.target << endl;
		break;
	case BGEZ:
		out << "bgez $a1 " << item.target << endl;
		break;
	default:
		break;
	}
}

//函数返回处理
void helpReturn(ofstream & out) {
	//栈指针恢复到$fp
	out << "move $sp $fp" << endl;
	//$k0 $k1寄存器值恢复
	out << "lw $t9 -4($sp)" << endl;
	out << "lw $t8 -8($sp)" << endl;
	out << "lw $t7 -12($sp)" << endl;
	out << "lw $t6 -16($sp)" << endl;
	out << "lw $t5 -20($sp)" << endl;
	out << "lw $t4 -24($sp)" << endl;
	out << "lw $k1 -28($sp)" << endl;
	out << "lw $k0 -32($sp)" << endl;
	out << "addiu $sp $sp -32" << endl;
	//返回地址存入$ra
	out << "lw $ra 0($fp)" << endl;
	//函数栈区起始地址恢复--->上一级函数基地址$fp恢复
	out << "lw $fp 4($fp)" << endl;
	//执行jr
	out << "jr $ra" << endl;
}

//生成最终的Text段代码
void generateText(ofstream & out) {
	for (unsigned int i = 0; i < globalTmpCodeArr.size(); i++) {
		FourYuanItem item = globalTmpCodeArr.at(i);
		switch (item.type) {
		case ValueParamDeliver:
			//push对应的全部都是变量,取地址
			//首先看push的符号表里面的还是临时生成的变量
			if (item.target.at(0) == 'G') {//符号表内
				int order = stringToInt(item.target.substr(1));
				SymbolTableItem item = globalSymbolTable.at(order);
				if (item.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(item.getId(),"$a2",out);
				}
				else {
					getAddrOfLocal(item.getFuncName(),item.getId(), "$a2", out);
				}
				out << "lw $a2 0($a2)" << endl;
			}
			else {//临时变量
				int g = stringToInt(item.target.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$a2", out);
					out << "lw $a2 0($a2)" << endl;
				}
				else {
					out << "move $a2 " << "$t" << (g + 3) << endl;
				}
			}
			out << "sw $a2 " << currentParamSp << "($0)" << endl;
			currentParamSp += 4;
			break;
		case FunctionCall:
			currentParamSp = paramSpBegin;//回到起点
			//函数调用,跳转,生成所跳转的目标函数运行栈空间的首地址
			out << "jal " << item.target<<endl;//此时mars运行会将返回地址写入到$ra寄存器(函数执行时需要保存它)
			break;
		case AssignState:
			helpAssignStatement(item,out);
			break;
		case Label:
			out << item.target << ":" << endl;
			break;
		case FunctionDef:
			//函数定义要处理的大问题
			out << item.target << ":" << endl;//生成跳转标签
			helpFunctionDef(item.target,out);
			break;
		case ParamDef:
			//忽略处理,因为已经通过符号表在函数定义处处理了变量、参数的空间分配与地址分配
			break;
		case Jump:
			out << "j " << item.target << endl;
			break;
		case BEZ:
		case BNZ:
		case BLZ:
		case BLEZ:
		case BGZ:
		case BGEZ:
			helpBJump(item,out);
			break;
		case ReadChar: 
		case ReadInt:{
			if(item.type == ReadChar)
				out << "li $v0 12" << endl;
			else
				out << "li $v0 5" << endl;
			out << "syscall" << endl;
			int order = stringToInt(item.target.substr(1));
			SymbolTableItem item = globalSymbolTable.at(order);
			if (item.getFuncName() == "GLOBAL") {
				getAddrOfGlobal(item.getId(), "$a3", out);
			}
			else {
				getAddrOfLocal(item.getFuncName(), item.getId(), "$a3", out);
			}
			out << "sw $v0 0($a3)" << endl;
			break;
		}
		case PrintStr: {
			map<string, string>::iterator iter = stringWithLabel.find(item.target);
			if (iter != stringWithLabel.end()) {
				out << "la $a0 " << iter->second << endl;
			}
			out << "li $v0 4" << endl;
			out << "syscall" << endl;
			break;
		}
		case PrintChar:
			out << "li $a0 " << (int)item.target.at(0) << endl;
			out << "li $v0 11" << endl;
			out << "syscall" << endl;
			break;
		case PrintInt:
			out << "li $a0 " << stringToInt(item.target) << endl;
			out << "li $v0 1" << endl;
			out << "syscall" << endl;
			break;
		case PrintId: {
			//判断是打印int还是char
			if (item.target.at(0) == 'G') {
				int order = stringToInt(item.target.substr(1));
				SymbolTableItem item = globalSymbolTable.at(order);
				if (item.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(item.getId(),"$a0",out);
				}
				else {
					getAddrOfLocal(item.getFuncName(),item.getId(), "$a0", out);
				}
				out << "lw $a0 0($a0)" << endl;
			}
			else if (item.target.at(0) == 'T') {
				int g = stringToInt(item.target.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$a0", out);
					out << "lw $a0 0($a0)" << endl;
				}
				else {
					out << "move $a0 " << "$t" << (g + 3) << endl;
				}
			}
			
			if (!item.isNotPrintCharId)
				out << "li $v0 11" << endl;
			else
				out << "li $v0 1" << endl;
			out << "syscall" << endl;
			out << "# com " << "printf " << item.target << endl;
			break;
		}
		case ReturnInt:
		case ReturnChar:
			out << "li $v0 " << stringToInt(item.target) << endl;
			out << "sw $v0 " << returnValueSpace << "($0)" << endl;
			//返回地址
			helpReturn(out);
			break;
		case ReturnId: {
			if (item.target.at(0) == 'G') {
				int order = stringToInt(item.target.substr(1));
				SymbolTableItem item = globalSymbolTable.at(order);
				if (item.getFuncName() == "GLOBAL") {
					getAddrOfGlobal(item.getId(), "$v0", out);
				}
				else {
					getAddrOfLocal(item.getFuncName(), item.getId(), "$v0", out);
				}
				out << "lw $v0 0($v0)" << endl;
			}
			else if (item.target.at(0) == 'T') {
				int g = stringToInt(item.target.substr(1));
				if (g > TEMP_REGISTER) {
					getAddrOfTemp(g, "$v0", out);
					out << "lw $v0 0($v0)" << endl;
				}
				else {
					out << "move $v0 " << "$t" << (g + 3) << endl;
				}
			}
			out << "sw $v0 " << returnValueSpace << "($0)" << endl;
			//返回地址
			helpReturn(out);
			break;
		}
		case ReturnEmpty:
			//返回地址
			helpReturn(out);
			break;
		case OverProcedure:
			out << "li $v0 10" << endl;
			out << "syscall" << endl;
		default:break;
		}
	}
}