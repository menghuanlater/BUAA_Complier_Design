/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
//错误处理程序
#ifndef ERROR_H
#define ERROR_H
#include <iostream>

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
enum SyntaxErrorCode{
    EmptyFileError,//文件为空
    AfterMainContentError,//main函数后多余的内容
    GeneralError //
};

class Error
{
private:

public:
    //词法分析错误处理程序
    void LexicalAnalysisError(LexicalErrorCode errorCode,int lineNumber)const;
    //语法分析错误处理程序
    void SyntaxAnalysisError(SyntaxErrorCode errorCode,int lineNumber);
};
#endif