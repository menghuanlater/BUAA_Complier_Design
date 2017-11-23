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
/*
可用字符32,33 35-126
*/
#define CHAR1 32 
#define CHAR2 33
#define CHAR3 35
#define CHAR4 126

#endif