/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
#include <iostream>
#include "error.h"
using namespace std;

void Error::LexicalAnalysisError(LexicalErrorCode errorCode,int lineNumber)const{
    switch(errorCode){
        case SingleCharIllegal:
            cout<<"At line: "<<lineNumber<<" exists single character illegal error."<<endl;
            break;
        case StringIllegal:
            cout<<"At line: "<<lineNumber<<" exists string illegal error."<<endl;
            break;
        case ContentIllegal:
            cout<<"At line: "<<lineNumber<<" exists contents illegal error."<<endl;
            break;
        case NotEqualSymIllegal:
        cout<<"At line: "<<lineNumber<<" exists symbol \'!=\' not match error."<<endl;
            break;
        default:break;
    }
}