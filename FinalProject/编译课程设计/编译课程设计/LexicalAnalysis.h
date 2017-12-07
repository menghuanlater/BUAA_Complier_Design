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
    static const  int maxWordLength = 1024;//一个单词最大长度
    int    lineCount;//行计数器,目的在于发现非法字符提示所在文件的行数
    const Error & myError;//错误处理类引用,全局公用
    bool finish;//是否已经读完
    bool isNextSym;//需不需要调用nextSym的时候不实际调用(语法分析错误处理,自动补足缺失的括号冒号逗号分号等情况)
    /*关于isFinish的解释:
        由于每个递归下降子程序结束前必然会预读,isFinish设置的是
        所有预读全部处理完的结束标志
    */
    void retract(){//回退一个字符
        index--;
    }
    //读取字符
    char getChar(){
		if(index >= fileLength){
            return EOF;
        }
        return fileContents[index++]; 
    }
    //小写化字符串
    void toLow(char* target);
    //查找保留字表
    int reserver(char* target);
public:
    //有参构造函数
    LexicalAnalysis(const Error & error);
    //读取文件的全部内容到fileContents中
    void readFile(string FilePath);
    //语法分析程序调用,读取一个单词
    bool nextSym();
    //检查是否读到文件的末尾,对于连续的symbolCode相同判断文件是否分析完的标志
    bool isFinish(){
        return finish;
    }
    //设置下次读取不是实际读取单词
    void setNextSym(){
        isNextSym = true;
    }
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
    int getLineCount(){
        return lineCount;
    }
    int getPoint(){
        return index;
    }
    //重新设置index的值
    void resetPoint(int value){
        index = value;
    }
    //重新设置symbol ---实际只涉及INTSY CHARSY
    void resetSymbol(SymbolCode symbol){
        globalSymbol = symbol;
    }
    //设置跳读的函数
    void skipRead(char end);
};

#endif