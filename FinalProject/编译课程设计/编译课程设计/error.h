/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
//错误处理程序
#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <string>

using namespace std;

//词法分析错误种类枚举
/*
*1.单字符char不合法
*2.字符串不合法
*3.整个程序出现非法字符
*/
enum LexicalErrorCode{
    SingleCharIllegal,
    StringIllegal,
    ContentIllegal,
    NotEqualSymIllegal
};
//语法分析错误种类枚举
/*
1.文件为空error
2.main函数后多余内容
3.没有void main函数
4.语法缺少部分结构,或者结构不匹配
5.数组声明中数组的长度不是无符号整数(>0)
6.0的前面不可以有正负号修饰
*/
enum SyntaxErrorCode{
    EmptyFileError,//文件为空
    AfterMainContentError,//main函数后多余的内容
    NoMainFunctionError,//无void main函数
    LackComposedPartError,//缺少相关组成部分
    NotUnsignedIntegerError,//不是无符号整数
    ZeroPrefixSignError,//0前不可以有正负号修饰
    GeneralError //
};

//语义分析的相关错误
/*
1.声明定义冲突(作用域问题)

2.引用变量，变量未定义

3.引用数组，数组越界
4.引用函数，函数未定义
5.单个语句只能是函数
6.调用函数,无参却传参数
7.调用函数，值参数个数不对
8.调用函数，值参数类型不对
9.赋值对象不是普通变量(包含了多种错误情况)
10.赋值类型不匹配(int 给 char赋值)
11.引用标识符,标识符对应类型不匹配
12.值参数表不可以为空
13.case出现相同的值
14.除数不可以为0
*/
enum SemanticErrorCode {
	DeclareConflictError,
	NotDefinitionError,
	FuncNotDefineError,
	ArrIndexOutOfRangeError,
	TypeNotMatchError,
	AssignIntToCharError,
	StateIdNotMatchError,
	NeedValueButVoidFuncError,
	NoneValueParamError,
	NoneParamButDeliverError,
	ParamNumNotMatchError,
	ParamTypeNotMatchError,
	AssignObjectNotVar,
	CaseSameValueError,
	CaseTypeNotMatchError
};
/*与return语句有关的error
1.无返回值存在有返回值的return
2.有返回值存在无返回值的return
3.有返回值不存在return
4.有返回值存在return类型不兼容
5.有返回值存在分支导致无返回值
*/
enum ReturnRelatedError {
	VoidButReturnValueError,
	CharButReturnIntError,
	ExistNoneReturnError,
	ExistReturnEmptyError
};

class Error
{
private:
    
public:
    //词法分析错误处理程序
    void LexicalAnalysisError(LexicalErrorCode errorCode,int lineNumber)const;
    //语法分析错误处理程序
    void SyntaxAnalysisError(SyntaxErrorCode errorCode,int lineNumber);
    void SyntaxAnalysisError(SyntaxErrorCode errorCode,int lineNumber,string info);
	//语义分析错误处理程序
	void SemanticAnalysisError(SemanticErrorCode errorCode,int lineNumber,string identifier);//带标识符
	//关于函数返回语句相关错误
	void ReturnStatementError(ReturnRelatedError errorCode,int lineNumber,string funcName);
};
#endif