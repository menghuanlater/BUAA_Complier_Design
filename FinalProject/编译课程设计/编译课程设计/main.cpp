/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
/*相关说明:
#1编译程序的整体入口
#2标识符不区分大小写
*/
#include <iostream>
#include <string>
#include "error.h"
#include "ConstValue.h"
#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "globalFunction.h"
#include "optimize.h"
#include <algorithm>

using namespace std;

string compilerFilePath;

extern const char * keyWordsArr[KEY_NUM];
extern const char * SymbolArr[SYM_NUM];
extern bool ErrorFlag;

int main(void){
    //欢迎界面
    cout<<"WelCome to use my compiler."<<endl;
    //提示输入需要编译的文件的绝对路径
    cout<<"Please enter the absolute file path to compiler:";
    //终端读入输入的文件名
    getline(cin,compilerFilePath);

    //全局共用的错误处理类对象
    Error error;

    //词法分析类对象
	LexicalAnalysis myLexical(error);
    myLexical.readFile(compilerFilePath);
    
    //语法语义分析类对象
    SyntaxAnalysis mySyntax(error,myLexical);
    mySyntax.startAnalysis();//语法语义分析入口函数

	//中间代码写入
	if (!ErrorFlag) {
		cout << "Correct compilation of source program.Next will generator temporary code to tmpCode.txt" << endl;
		writeTmpCodeToFile();
		cout << "Temporary Code have been writen to tmpCode.txt,then we will generator final mips32 code to mips.asm" << endl;
		generateMipsCode();
		cout << "Mips code have been writen into mips.asm" << endl;
		toDoOptimize();
		cout << "Accomplish Optimization." << endl;
		op_writeTmpCodeToFile();
		cout << "Ok,temporary optimize code have been writen to op_tmpCode.txt" << endl;
		op_generateMipsCode();
		cout << "Ok,optimize mips code have been writen to op_mips.asm" << endl;
	}

    cout<<"Analysis accomplish. Thanks for using!"<<endl;

    return 0;
}
