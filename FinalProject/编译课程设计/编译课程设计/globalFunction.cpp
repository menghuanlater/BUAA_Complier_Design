/*
** @author:止水清潇menghuanlater
** @date:2017-12-10
** @location:BUAA
*/
#include "globalFunction.h"
#include <fstream>
#include <cstring>
#include <map>
#include "error.h"

static int labelCount = 0;//全局标签计数器
static int tmpVarCount = 0;//全局临时变量计数器
static int globalStrCount = 0;//全局字符串计数器
static unsigned strMemSize = 0;//字符串占据的大小
unsigned int tempParamSp;//临时参数栈空间指针
const int tempStackMax = 100;//设置临时参数栈最大为100字节(最多有25个参数)
unsigned int funcStackSp;//函数栈的起始地址

const string tmpCodeToFileName = "tmpCode.txt";//中间代码输出文件
const string mipsCodeToFileName = "mips.asm";//最终汇编代码输出文件

extern vector<FourYuanItem> globalTmpCodeArr;
extern vector<SymbolTableItem> globalSymbolTable;

vector<FourYuanItem> globalTmpCodeArr;//中间代码生成集合
vector<string> constStringSet;//程序需要打印的常量字符串集合,放在.data域
map<string, string> stringWithLabel;
map<string, unsigned> globalTempVarTable;//临时变量表

string generateLabel() {
	labelCount++;
	char x[10] = { '\0' };
	sprintf(x, "%d", labelCount);
	return ("Label" + string(x));
}

string generateVar() {
	tmpVarCount++;
	char x[10] = {'\0'};
	sprintf(x,"%d",tmpVarCount);
	return ("Temp" + string(x));
}

string generateStrLabel() {
	globalStrCount++;
	char x[10] = {'\0'};
	sprintf(x,"%d",globalStrCount);
	return ("String" + string(x));
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
	for (unsigned i = 0; i < target.size(); i++) {
		if (target.at(i) < '0' || target.at(i) > '9')
			break;
		outcome = outcome * 10 + target.at(i) - '0';
	}
	return outcome;
}

void turnToPostfixExp(vector<PostfixItem>tar, vector<PostfixItem> & obj) {
	vector<PostfixItem> tmp;
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
string calculateExp(vector<PostfixItem> & tar, bool & isSure,ValueType & t,int & ret,int line,bool isCache,vector<FourYuanItem> & cache) {
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
			return item.str;
		}
	}
	else {
		for (unsigned int i = 0; i < tar.size(); i++) {
			item = tar.at(i);
			if (item.type == CharType) {
				char x[15] = { '\0' };
				item2.type = AssignState;
				item2.isTargetArr = item2.isLeftArr = false;
				switch (item.number) {
					case '+':
					case '-':
						if (tmp.size() > 1) {
							tmpVar = generateVar();
							item2.target = tmpVar;
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size()-1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x,"%d",tmp.at(tmp.size()-1).number);
								item2.right = x;
								tmp.pop_back();
							}
							memset(x,0,15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.left = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.left = x;
								tmp.pop_back();
							}
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
					case '*':
					case '/':
						if (tmp.size() > 1) {
							tmpVar = generateVar();
							item2.target = tmpVar;
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.right = x;
								tmp.pop_back();
							}
							memset(x, 0, 15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.left = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.left = x;
								tmp.pop_back();
								if (item.number == '/' && item2.right == "0") {
									cout << "Error(at line " << line << " surround): exist div 0 situation." << endl;
								}
							}
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
					default:tmp.push_back(item);
				}
			}
			else {
				tmp.push_back(item);
			}
		}
		if (tmp.size() >= 1) {
			return tmp.at(0).str;
		}
		else {
			return "";
		}
	}
}

void writeTmpCodeToFile() {
	ofstream out(tmpCodeToFileName, ios::out);
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
			constStringSet.push_back(item.target);
			break;
		case PrintChar:
			if (item.target.at(0) == '\n') {
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
	//临时参数栈基址设置为strMemSize
	tempParamSp = strMemSize;
	funcStackSp = tempParamSp + tempStackMax;
	//下面着重生成.text段
	out << ".text" << endl;
	generateText(out);
	
	out << "#accomplish generate mips code." << endl;
	out.close();
}
//生成汇编Data段指令，最终地址需要给出,用于知道整个函数运行栈的开始点在哪
void generateData(ofstream & out) {
	for (unsigned int i = 0; i < constStringSet.size(); i++) {
		string item = constStringSet.at(i);
		strMemSize += item.size() + 1;//'\0'占一个字节
		string label = generateStrLabel();
		out << "\t" << label << ":.asciiz \"" << item << "\"" << endl;
		stringWithLabel.insert(map<string, string>::value_type(item, label));
	}
}
//生成最终的Text段代码
void generateText(ofstream & out) {
	unsigned int address;
	for (unsigned int i = 0; i < globalTmpCodeArr.size(); i++) {
		FourYuanItem item = globalTmpCodeArr.at(i);
		switch (item.type) {
		case ValueParamDeliver:
			//push对应的全部都是变量,取地址
			//首先看push的符号表里面的还是临时生成的变量
			if (item.target.at(0) == 'G') {//符号表内
				int order = stringToInt(item.target.substr(1));
				address = globalSymbolTable.at(order).getAddress();//获取地址
			}
			else {//临时变量
				map<string, unsigned>::iterator iter = globalTempVarTable.find(item.target);
				if (iter != globalTempVarTable.end()) {
					address = iter->second;
				}
			}
			out << "lw $t0 " << address << "($0)" << endl;
			out << "sw $t0 " << tempParamSp << "($0)" << endl;
			tempParamSp += 4;
			break;
		case FunctionCall:
			//需要做的事:跳转，返回地址，参数取回，数据栈区分配,数据变量地址分配
			//做成一个函数处理
			break;
		case AssignState:
			
			break;
		case Label:
			
			break;
		case FunctionDef:
	
			break;
		case ParamDef:
			
			break;
		case Jump:
			
			break;
		case BEZ:
			
			break;
		case BNZ:
			
			break;
		case BLZ:
			
			break;
		case BLEZ:
			
			break;
		case BGZ:
			
			break;
		case BGEZ:
			
			break;
		case ReadChar:
			
			break;
		case ReadInt:
			
			break;
		case PrintStr:
			
			break;
		case PrintChar:
			
			break;
		case PrintInt:
			
			break;
		case PrintId:
			
			break;
		case ReturnInt:
			
			break;
		case ReturnChar:
			
			break;
		case ReturnId:
			
			break;
		case ReturnEmpty:
			
			break;
		default:break;
		}
	}
}