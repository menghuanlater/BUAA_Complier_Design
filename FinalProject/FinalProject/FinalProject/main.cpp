/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
/*相关说明:
#1编译程序的整体入口
#2标识符不区分大小写
#3对于词法分析:当遇到error,报错处理后跳过当前行,分析下一行
*/
#include <iostream>
#include <string>
#include "error.h"
#include "ConstValue.h"
#include "LexicalAnalysis.h"
using namespace std;

string compilerFilePath;

extern const char * keyWordsArr[KEY_NUM];
extern const char * SymbolArr[SYM_NUM];

int main(void){
    //欢迎界面
    cout<<"WelCome to use my compiler."<<endl;
    //提示输入需要编译的文件的绝对路径
    cout<<"Please enter the absolute file path to compiler:";
    //终端读入输入的文件名
    getline(cin,compilerFilePath);

    //全局共用的错误处理类对象
    Error error;

    //语法分析类对象
	LexicalAnalysis myLexical(error);
    myLexical.readFile(compilerFilePath);
    
    //模拟语法分析程序向词法分析类请求读取单词
    int count = 1;//输出的行号计数器
    enum SymbolCode mySym;
    while(myLexical.nextSym()){
        mySym = myLexical.getGlobalSymbol();
        if(mySym>=CONSTSY && mySym<=RETURNSY){//保留字
            cout<<count<<". "<<SymbolArr[mySym]<<" : "<<keyWordsArr[mySym]<<endl;
        }else if( (mySym>=CHAR && mySym<=LESS ) || (mySym>=MORE && mySym<=ASSIGN) ){//单字符
            cout<<count<<". "<<SymbolArr[mySym]<<" : "<<myLexical.getGlobalChar()<<endl;
        }else if(mySym == INTNUM){//无符号整数
            cout<<count<<". "<<SymbolArr[mySym]<<" : "<<myLexical.getGlobalNumber()<<endl;
        }else{//字符串
            cout<<count<<". "<<SymbolArr[mySym]<<" : "<<myLexical.getGlobalString()<<endl;
        }
        count++;//计数器自增
    }
    cout<<"Analysis accomplish. Thanks for using!"<<endl;
    return 0;
}
