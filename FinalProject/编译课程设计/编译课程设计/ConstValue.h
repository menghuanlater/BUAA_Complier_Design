/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
/*相关全局常量的定义
*%1:关键词(保留字)
*%2:标识符类别标识
*%3:可用字符的范围
*/
#ifndef CONSTVALUE_H
#define CONSTVALUE_H
#define KEY_NUM 14 //保留字数量定义
#define SYM_NUM 38 //记忆符数量
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstdio>//使用sprintf
using namespace std;
//枚举记忆符对应的类别编码
enum SymbolCode{
    CONSTSY,      INTSY,        CHARSY,       VOIDSY,
    MAINSY,       IFSY,         ELSESY,       SWITCHSY,
    CASESY,       DEFAULTSY,    WHILESY,      SCANFSY,
    PRINTFSY,     RETURNSY,     IDENTIFIER,   INTNUM,
    STRING,       CHAR,         ADD,          SUB,
    MULT,         DIV,          LESS,         LESSEQ,
    EQUAL,        MOREEQ,       NOTEQ,        MORE, 
    COMMA,        COLON,        SEMI,         LSBRACKET,    
    RSBRACKET,    LMBRACKET,    RMBRACKET,    LBBRACKET,    
    RBBRACKET,    ASSIGN
};

//枚举相关类型
enum ItemType {
	Constant,//常量
	Variable,//变量
	Function,//函数
	Parament//参数
};
//对于int char string
enum ValueType {
	IntType,
	CharType,
	StringType
};
//对于函数是否具有返回值
enum FunctionType {
	VoidType,
	ReturnIntType,
	ReturnCharType
};
/*四元式结构体总设计
1.值参传入push x,push y
2.调用函数 call add
3.赋值语句 i = ret  i = t1 + 1
4.条件判断 x == y  x<=y
5.纯标签Label1:
6.跳转语句 goto label1 bnz label1 ...
7.函数返回 ret x   ret
8.函数声明 int x
9.参数表 param x
10.print "xxxx"  print 'c' print 23 print a
11.read int a, read char c
*/
enum TmpCodeType {
	ValueParamDeliver,
	FunctionCall,
	AssignState,
	Label,
	FunctionDef,
	ParamDef,
	Jump,
	BEZ,
	BNZ,
	BLZ,
	BLEZ,
	BGZ,
	BGEZ,
	ReadChar,
	ReadInt,
	PrintStr,
	PrintChar,
	PrintInt,
	PrintId,
	ReturnInt,
	ReturnChar,
	ReturnId,
	ReturnEmpty
};
//四元式结构体
struct FourYuanItem {
	TmpCodeType type;
	ValueType valueType;//参数,print语句表达式输出
	FunctionType funcType;
	string target;
	string index1;
	bool isTargetArr;
	bool isLeftArr;
	string left;
	string index2;
	string right;
	char op;
};
//中缀表达式转逆波兰表达式栈的项结构体
struct PostfixItem {
	ValueType type;
	string str;
	int number;
};

/*
可用字符32,33 35-126
*/
#define CHAR1 32 
#define CHAR2 33
#define CHAR3 35
#define CHAR4 126

#endif