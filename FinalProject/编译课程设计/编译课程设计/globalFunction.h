/*
** @author:止水清潇menghuanlater
** @date:2017-12-10
** @location:BUAA
*/
#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#define _CRT_SECURE_NO_WARNINGS
#include "ConstValue.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
using namespace std;

//函数声明
string generateLabel();
string generateVar(string);
bool isStringDigit(string);
int stringToInt(string);
//文件操作
//将中间代码写入到文件中
void writeTmpCodeToFile();
//将中间代码翻译成最终的mips32汇编语言代码
void generateMipsCode();
void generateData(ofstream &);
void generateText(ofstream &);
//表达式的相关计算处理
void turnToPostfixExp(vector<PostfixItem>, vector<PostfixItem> &);
string calculateExp(vector<PostfixItem> &,bool &,ValueType &,int &,int,bool,vector<FourYuanItem> &,string);

//取消字符串中的转义字符
void cancelEscapeChar(string & target);
#endif // !GLOBALFUNCTION_H

