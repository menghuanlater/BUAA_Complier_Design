/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
/*LexicalAnalysis是词法分析程序,主要任务是分析单词类别,将识别出的内容
 * 传递给语法分析程序
*/
#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H
#include <string>
#include "ConstValue.h"
#include "error.h"
using namespace std;

extern const char * keyWordsArr[KEY_NUM];
extern const char * SymbolArr[SYM_NUM];

class LexicalAnalysis
{
private:
    string fileContents;//编译文件的全部内容
	long   fileLength;//编译文件的大小
    int    index; //索引
    char   globalChar;//存放当前读进的字符
    string globalString;//存放当前读进的字符串
    int    globalNumber;//存放当前读进的整数
    enum   SymbolCode globalSymbol;//当前所识别单词的类型
    static const  int maxWordLength = 100;//一个单词最大长度
    //int    lineCount;//行计数器,目的在于发现非法字符提示所在文件的行数
    const Error & myError;//错误处理类引用,全局公用
    void retract(){//回退一个字符
        index--;
    }
    //读取字符
    char getChar(){
        return fileContents[index++]; 
    }
    //小写化字符串
    void toLow(char* target);
    //查找保留字表
    int reserver(char* target);
public:
    //无参构造函数
    LexicalAnalysis(const Error & error);
    //读取文件的全部内容到fileContents中
    void readFile(string FilePath);
    //语法分析程序调用,读取一个单词
    bool nextSym();
    //返回相关的值
    //class的属性get集
    char getGlobalChar(){
        return globalChar;
    }
    string getGlobalString(){
        return globalString;
    }
    int getGlobalNumber(){
        return globalNumber;
    }
    enum SymbolCode getGlobalSymbol(){
        return globalSymbol;
    }
};

#endif