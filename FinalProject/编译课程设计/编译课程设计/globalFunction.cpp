/*
** @author:止水清潇menghuanlater
** @date:2017-12-10
** @location:BUAA
*/
#include "globalFunction.h"
#include <fstream>
#include <cstring>
#include "error.h"
static int lableCount = 0;//全局标签计数器
static int tmpVarCount = 0;//全局临时变量计数器

const string tmpCodeToFileName = "tmpCode.txt";//中间代码输出文件
const string mipsCodeToFileName = "mips.txt";//最终汇编代码输出文件

extern vector<FourYuanItem> globalTmpCodeArr;
extern vector<SymbolTableItem> globalSymbolTable;

vector<FourYuanItem> globalTmpCodeArr;//中间代码生成集合

string generateLabel() {
	lableCount++;
	return ("Lable" + lableCount);
}

string generateVar() {
	tmpVarCount++;
	return ("Temp" + tmpVarCount);
}

bool isStringDigit(string target) {
	for (unsigned i = 0; i < target.size(); i++) {
		if (target.at(i) > '9' || target.at(i) < '0') {
			return false;
		}
	}
	return true;
}
//确保在使用过isStringDigit判断过后使用
int stringToInt(string target) {
	int outcome = 0;
	for (unsigned i = 0; i < target.size(); i++) {
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
		PostfixItem item;
		char x;
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
string calculateExp(vector<PostfixItem> & tar, bool & isSure,ValueType & t,int & ret,int line) {
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
								item2.left = tmp.at(tmp.size()-1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x,"%d",tmp.at(tmp.size()-1).number);
								item2.left = x;
								tmp.pop_back();
							}
							memset(x,0,15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.right = x;
								tmp.pop_back();
							}
							item2.op = item.number;
							globalTmpCodeArr.push_back(item2);
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
								item2.left = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.left = x;
								tmp.pop_back();
							}
							memset(x, 0, 15);
							if (tmp.at(tmp.size() - 1).type == StringType) {
								item2.right = tmp.at(tmp.size() - 1).str;
								tmp.pop_back();
							}
							else {
								sprintf(x, "%d", tmp.at(tmp.size() - 1).number);
								item2.right = x;
								tmp.pop_back();
								if (item.number == '/' && item2.right == "0") {
									cout << "Error(at line " << line << " surround): exist div 0 situation." << endl;
								}
							}
							item2.op = item.number;
							globalTmpCodeArr.push_back(item2);
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
			break;
		case FunctionCall:
			break;
		case AssignState:
			break;
		case ConditionJudge:
			break;
		case Label:
			break;
		case Jump:
			break;
		case Return:
			break;
		default:break;
		}
	}
	out.close();
}

void generateMipsCode() {
	ofstream out(mipsCodeToFileName, ios::out);

	out.close();
}