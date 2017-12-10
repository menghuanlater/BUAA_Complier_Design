/*
** @author:止水清潇menghuanlater
** @date:2017-12-10
** @location:BUAA
*/
#ifndef GLOBALFUNCTION_H
#define GLOBALFUNCTION_H
#include "ConstValue.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
using namespace std;

//函数声明
string generateLabel();
string generateVar();
bool isStringDigit(string);
int stringToInt(string);
//文件操作
//将中间代码写入到文件中
void writeTmpCodeToFile();
//将中间代码翻译成最终的mips32汇编语言代码
void generateMipsCode();

//表达式的相关计算处理
void turnToPostfixExp(vector<PostfixItem>, vector<PostfixItem> &);
string calculateExp(vector<PostfixItem> &,bool &,ValueType &,int &,int);

#endif // !GLOBALFUNCTION_H

