/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
#include "SyntaxAnalysis.h"
#include <iostream>

using namespace std;

//标准构造函数,采用初始化成员列表
SyntaxAnalysis::SyntaxAnalysis(Error & myError,LexicalAnalysis & myLexicalAnalysis):myError(myError),myLexicalAnalysis(myLexicalAnalysis){
}

//程序入口函数
void SyntaxAnalysis::startAnalysis(){
    bool nextSymFlag;
    nextSymFlag = myLexicalAnalysis.nextSym();//进入每一个递归下降分析子程序前都需要先进行预读
    if(nextSymFlag){        //进入<程序>分析
        if(!ZSQX_procedure())
            return;
    }else{
        myError.SyntaxAnalysisError(EmptyFileError,getLineNumber());
        return;
    }
    //检查文件后是否有多余的内容
    if(!myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(AfterMainContentError,getLineNumber());
    }
}
//＜程序＞ ::= ［＜常量说明＞］［＜变量说明＞］[<函数定义部分>]   ＜主函数＞
bool SyntaxAnalysis::ZSQX_procedure(){
    bool nextSymFlag;
    //看是否有常量说明
    ZSQX_constDescription();
    //是否有变量说明
    ZSQX_varDescription(true);
    //检查是否有函数定义
    ZSQX_functionDefinition();
    //正式分析void main(){...}
    //在函数定义部分一定会识别到void main再返回
    nextSymFlag = myLexicalAnalysis.nextSym();
    SymbolCode symbol;
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){//(
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){//)
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){//{
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }      

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //复合语句
    if(!ZSQX_compoundStatement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){//没有结尾的},文件读取结束,报错
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){//}
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //预读:
    myLexicalAnalysis.nextSym();
    //正常分析结束,procedure识别
    cout <<"*** This is procedure. ***"<<getLineNumber()<<endl;
    return true;
}

//＜常量说明＞ ::= const＜常量定义＞;{ const＜常量定义＞;}
bool SyntaxAnalysis::ZSQX_constDescription(){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    //分析const
    if(!(symbol == CONSTSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析<常量定义>
    if(!ZSQX_constDefinition()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    
    if(myLexicalAnalysis.isFinish()){//未分析结束,已经到达文件结尾
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SEMI)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    
    //分析{...}
    while(true){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            break;
        }
        //const
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == CONSTSY)){
            break;
        }
       
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //<常量定义>
        if(!ZSQX_constDefinition()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }

        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //分析;
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == SEMI)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }
    
    cout<<"*** This is const description. ***"<<getLineNumber()<<endl;
    return true;
}

/*＜常量定义＞ ::= int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
        | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞} */
bool SyntaxAnalysis::ZSQX_constDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY){//int
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //标识符
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //=
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //整数
        if(!ZSQX_integer()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        while(true){
            if(myLexicalAnalysis.isFinish()){
                break;
            }
            //,
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == COMMA)){
                break;
            }

            //光有逗号,后面却啥都没有
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //标识符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == IDENTIFIER)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }

            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //=
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == ASSIGN)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //整数
            if(!ZSQX_integer()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
        }

    }else if(symbol == CHARSY){//char
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //标识符
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //=
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //字符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == CHAR)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }

        while(true){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag)
                break;
            //,
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == COMMA)){
                break;
            }

            //光有逗号,后面却啥都没有
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //标识符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == IDENTIFIER)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }

            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //=
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == ASSIGN)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //字符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == CHAR)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
        }
    }else{
        return false;
    }

    cout<<"*** This is const definition. ***"<<getLineNumber()<<endl;
    return true;
}

//＜变量说明＞ ::= ＜变量定义＞;{＜变量定义＞;}
//特殊的分析函数---由于跟全局的函数申明存在冲突
bool SyntaxAnalysis::ZSQX_varDescription(bool isGlobal){
    bool nextSymFlag;
    SymbolCode symbol;
    int point = myLexicalAnalysis.getPoint();
    SymbolCode symbolCode = myLexicalAnalysis.getGlobalSymbol();
    //检查是否是定义的全局函数而不是变量定义
    if(isGlobal){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == CHARSY || symbol == INTSY){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(nextSymFlag){
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(symbol == IDENTIFIER){
                    nextSymFlag = myLexicalAnalysis.nextSym();
                    if(nextSymFlag){
                        symbol = myLexicalAnalysis.getGlobalSymbol();
                        if(symbol == LSBRACKET || symbol == LBBRACKET){//( or {
                            myLexicalAnalysis.resetPoint(point);
                            myLexicalAnalysis.resetSymbol(symbolCode);
                            return false;
                        }
                    }
                }
            }
            //如果不是函数定义,则回退,进行下面的分析
            myLexicalAnalysis.resetPoint(point);
            myLexicalAnalysis.resetSymbol(symbolCode);
        }else{
            return false;
        }
    }
    //如果不是全局的,则正常分析
    if(!ZSQX_varDefinition()){
        return false;
    }

    if(myLexicalAnalysis.isFinish()){
        return false;
    }
    //;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SEMI)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    while(true){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag)
            break;
        //再次检查是否出现函数定义混杂在其中
        if(isGlobal){
            point = myLexicalAnalysis.getPoint();
            symbol = symbolCode = myLexicalAnalysis.getGlobalSymbol();
            if(symbol == CHARSY || symbol == INTSY){    
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(nextSymFlag){
                    symbol = myLexicalAnalysis.getGlobalSymbol();
                    if(symbol == IDENTIFIER){
                        nextSymFlag = myLexicalAnalysis.nextSym();
                        if(nextSymFlag){
                            symbol = myLexicalAnalysis.getGlobalSymbol();
                            if(symbol == LSBRACKET || symbol == LBBRACKET){//( or {
                                myLexicalAnalysis.resetPoint(point);
                                myLexicalAnalysis.resetSymbol(symbolCode);
                                break;
                            }
                        }
                    }
                }
                //如果不是函数定义,则回退,进行下面的分析
                myLexicalAnalysis.resetPoint(point);
                myLexicalAnalysis.resetSymbol(symbolCode);
            }    
        }
        if(!ZSQX_varDefinition())
            break;
        //;
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == SEMI)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }

    cout<<"*** This is var description.***"<<getLineNumber()<<endl;
    return true;
}

/*＜变量定义＞ ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’)
            {,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’ )}*/
bool SyntaxAnalysis::ZSQX_varDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
    //类型标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == INTSY || symbol == CHARSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //识别是否是[
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == LMBRACKET){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //无符号整数
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol==INTNUM){
            int number = myLexicalAnalysis.getGlobalNumber();
            if(number == 0){//必须不为0
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }else{
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //]
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RMBRACKET)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //补足预读
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }
    //loop
    while(true){
        //,
        if(!(symbol == COMMA))
            break;

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //标识符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //识别是否是[
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == LMBRACKET){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //无符号整数
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol==INTNUM){
                int number = myLexicalAnalysis.getGlobalNumber();
                if(number == 0){//必须不为0
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    break;
                }
            }else{
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
                
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //]
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RMBRACKET)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                break;
            }
            //补足预读
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }
    }

    cout<<"*** This is var definition. ***"<<getLineNumber()<<endl;
    return true;
}

//<函数定义部分> ::= {＜有返回值函数定义＞|＜无返回值函数定义＞}
bool SyntaxAnalysis::ZSQX_functionDefinition(){
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY || symbol == CHARSY){
        if(!ZSQX_haveReturnValueFunctionDefinition()){
            return false;
        }
    }else if(symbol == VOIDSY){
        if(!ZSQX_noReturnValueFunctionDefinition()){
            return false;
        }
    }else{
        return false;
    }

    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        
        if(symbol == INTSY || symbol == CHARSY){
            if(!ZSQX_haveReturnValueFunctionDefinition()){
                break;
            }
        }else if(symbol == VOIDSY){
            if(!ZSQX_noReturnValueFunctionDefinition()){
                break;
            }
        }else{
            break;
        }
    }

    cout<<"*** This is function definiton. ***"<<getLineNumber()<<endl;
    return true;
}

/*＜有返回值函数定义＞ ::= ＜声明头部＞‘(’＜参数表＞‘)’ ‘{’＜复合语句＞‘}’|＜声明头部＞‘{’＜复合语句＞‘}’*/
bool SyntaxAnalysis::ZSQX_haveReturnValueFunctionDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
    //声明头部
    if(!ZSQX_declareHead()){
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        return false;
    }
    //检查是否为带参数
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == LSBRACKET){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //参数表
        if(!ZSQX_paramTable()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //)
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RSBRACKET)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //补足预读
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }
    //{
	symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //复合语句
    if(!ZSQX_compoundStatement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //}
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //预读
    myLexicalAnalysis.nextSym();

    cout<<"*** This is have return value function definition. ***"<<getLineNumber()<<endl;
    return true;
}

//＜无返回值函数定义＞ ::= void＜标识符＞(’＜参数表＞‘)’‘{’＜复合语句＞‘}’| void＜标识符＞{’＜复合语句＞‘}’
bool SyntaxAnalysis::ZSQX_noReturnValueFunctionDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
    //void
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == VOIDSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //检查是否带参数
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == LSBRACKET){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //参数表
        if(!ZSQX_paramTable()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //)
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RSBRACKET)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //补足预读
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }
    //{
	symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //复合语句
    if(!ZSQX_compoundStatement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //}
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //预读
    myLexicalAnalysis.nextSym();

    cout<<"*** This is no return value function definition. ***"<<getLineNumber()<<endl;
    return true;
}

//＜参数表＞ ::= ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}
bool SyntaxAnalysis::ZSQX_paramTable(){
    bool nextSymFlag;
    SymbolCode symbol;
    //类型标识符 int|char
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == INTSY || symbol == CHARSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    while(true){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            break;
        }
        //,
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == COMMA)){
            break;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //类型标识符 int|char
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == INTSY || symbol == CHARSY)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //标识符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }

    cout<<"*** This is parameter table. ***"<<getLineNumber()<<endl;
    return true;
}

//＜复合语句＞ ::= ［＜常量说明＞］［＜变量说明＞］｛＜语句＞｝
bool SyntaxAnalysis::ZSQX_compoundStatement(){
    ZSQX_constDescription();
    ZSQX_varDescription(false);

    while(true){
        if(!(ZSQX_statement()))
            break;
    }

    cout<<"*** This is compound statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜表达式＞ ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
bool SyntaxAnalysis::ZSQX_expression(){
    bool nextSymFlag;
    SymbolCode symbol;
    bool x_flag = false;//作为是否有前缀项的flag
    //检查是否有[+|-]
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol== ADD || symbol == SUB){
        x_flag = true;
        //补足预读
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }
    //<项>
    if(!ZSQX_item()){
        if(x_flag)
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //循环
    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ADD || symbol == SUB)){
            break;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //<项>
        if(!ZSQX_item()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }

    cout<<"*** This is expression. ***"<<getLineNumber()<<endl;
    return true;
}

//＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
bool SyntaxAnalysis::ZSQX_item(){
    bool nextSymFlag;
    SymbolCode symbol;
    if(!ZSQX_factor()){
        return false;
    }

    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == MULT || symbol == DIV)){
            break;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        //<项>
        if(!ZSQX_factor()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }

    cout<<"*** This is item. ***"<<getLineNumber()<<endl;
    return true;
}

//＜因子＞ ::= ＜标识符＞[‘(’<值参数表>‘)’]｜＜标识符＞‘[’＜表达式＞‘]’|‘(’＜表达式＞‘)’｜＜整数＞|＜字符＞
bool SyntaxAnalysis::ZSQX_factor(){
    bool nextSymFlag;
    SymbolCode symbol;
    bool preRead = true;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    
    switch(symbol){
        case IDENTIFIER:
            //最复杂的地方
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                preRead = false;
                break;
            }
            //标识符已经识别
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol == LMBRACKET){//[
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                //<表达式>
                if(!ZSQX_expression()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RMBRACKET)){//]
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
            }else if(symbol == LSBRACKET){//(
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                //<值参数表>
                if(!ZSQX_valueParamTable()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RSBRACKET)){//)
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
            }else{//仅仅是标识符,无需预读
                preRead = false;
            }
            break;
        case INTNUM:
        case ADD:
        case SUB:
            if(!ZSQX_integer()){
                return false;
            }
			preRead = false;
            break;
        case CHAR://直接正确
            break;
        case LSBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            //<表达式
            if(!ZSQX_expression()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            //)
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RSBRACKET)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        default:
            return false;
            break;
    }

    //预读
    if(preRead)
        myLexicalAnalysis.nextSym();
    cout<<"*** This is factor. ***"<<getLineNumber()<<endl;
    return true;
}

/*＜语句＞ ::= ＜条件语句＞｜＜循环语句＞| ‘{’｛＜语句＞｝‘}’｜＜标识符＞[‘(’<值参数表>‘)’]; 
        ｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜;|＜情况语句＞｜＜返回语句＞;*/
bool SyntaxAnalysis::ZSQX_statement(){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    bool preRead = true;
    
    switch(symbol){
        case IFSY:
            if(!ZSQX_conditionStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            preRead = false;
            break;
        case WHILESY:
            if(!ZSQX_loopStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            preRead = false;
            break;
        case LBBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                break;
            }
            while(true){
                //<语句>
                if(!ZSQX_statement()){
                    break;
                }
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    break;
                }
            }
            //先检查是否结束
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RBBRACKET)){//}
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        case IDENTIFIER://赋值语句与调用语句
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){//单纯的标识符
                break;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol == SEMI){//无参调用
                break;
            }else if(symbol == LSBRACKET){//有参调用
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                //<值参数表>
                if(!ZSQX_valueParamTable()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RSBRACKET)){//)
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }

                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                //;
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == SEMI)){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
            }else if(symbol == ASSIGN || symbol == LMBRACKET){//赋值语句识别前缀(去除标识符)
                if(!ZSQX_assignStatement()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == SEMI)){
                    myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                    return false;
                }
            }else{
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        case SCANFSY:
            if(!ZSQX_readStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        case PRINTFSY:
            if(!ZSQX_writeStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        case SEMI://空语句
            break;
        case SWITCHSY:
            if(!ZSQX_situationStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            preRead = false;
            break;
        case RETURNSY:
            if(!ZSQX_returnStatement()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        default:
            return false;
            break;
    }
    //预读
    if(preRead)
        myLexicalAnalysis.nextSym();
    cout<<"*** This is statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
//实际分析的是  ＝＜表达式＞|‘[’＜表达式＞‘]’=＜表达式＞
bool SyntaxAnalysis::ZSQX_assignStatement(){
    //无需分析标识符,已经在语句中分析得出
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();

    if(symbol == ASSIGN){//=
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //<表达式>
        if(!ZSQX_expression()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }else if(symbol == LMBRACKET){//[
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //<表达式>
        if(!ZSQX_expression()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //]
        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RMBRACKET)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //assign =
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //下面分析 = <表达式>
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        //<表达式>
        if(!ZSQX_expression()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }else{
        return false;
    }

    cout<<"*** This is asssign stateent. ***"<<getLineNumber()<<endl;
    return true;
}

//＜条件语句＞::= if ‘(’＜条件＞‘)’＜语句＞else＜语句＞
bool SyntaxAnalysis::ZSQX_conditionStatement(){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();

    //if
    if(!(symbol == IFSY)){
        return false;
    }
    //识别(
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //识别<条件>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_condition()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //)
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_statement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //else
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == ELSESY)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_statement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    cout<<"*** This is condition statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ 
//＜关系运算符＞ ::= <｜<=｜>｜>=｜!=｜==
bool SyntaxAnalysis::ZSQX_condition(){
    bool nextSymFlag;
    SymbolCode symbol;
    //<表达式>
    if(!ZSQX_expression()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol>=LESS && symbol<=MORE){
            //已识别关系运算符
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            //<表达式>
            if(!ZSQX_expression()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }
    }
    cout<<"*** This is condition. ***"<<getLineNumber()<<endl;
    return true;
}

//＜循环语句＞ ::= while ‘(’＜条件＞‘)’＜语句＞
bool SyntaxAnalysis::ZSQX_loopStatement(){
    bool nextSymFlag;
    SymbolCode symbol;

    //while
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == WHILESY)){
        return false;
    }

    //分析'('
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //识别<条件>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_condition()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //)
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    //<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_statement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    cout<<"*** This is loop statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜情况语句＞ ::= switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞[＜缺省＞] ‘}’
bool SyntaxAnalysis::ZSQX_situationStatement(){
    bool nextSymFlag;
    SymbolCode symbol;

    //switch
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SWITCHSY)){
        return false;
    }

    //分析'('
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析<表达式>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_expression()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析')'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析'{'
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析＜情况表＞[＜缺省＞]
	nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_situationTable()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析是否有缺省
    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == DEFAULTSY){
            if(!ZSQX_default()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }
    }
    //分析'}'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //预读
    myLexicalAnalysis.nextSym();
    cout<<"*** This is situation statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜情况表＞ ::= ＜情况子语句＞{＜情况子语句＞}
bool SyntaxAnalysis::ZSQX_situationTable(){
    bool nextSymFlag;
    //分析情况子语句
    if(!ZSQX_situationSonStatement()){
        return false;
    }

    while(true){
        if(myLexicalAnalysis.isFinish())
            break;
        if(!ZSQX_situationSonStatement())
            break;
    }

    cout<<"*** This is situation table. ***"<<getLineNumber()<<endl;
    return true;
}

//＜情况子语句＞ ::= case＜常量＞：＜语句＞
bool SyntaxAnalysis::ZSQX_situationSonStatement(){
    bool nextSymFlag;
    SymbolCode symbol;

    //分析case
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == CASESY)){
        return false;
    }

    //分析<常量>--> <整数>|<字符>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    switch(symbol){
        case INTNUM:
        case ADD:
        case SUB:
            if(!ZSQX_integer()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            break;
        case CHAR:
            //补读
            myLexicalAnalysis.nextSym();
            break;
        default:
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
            break;
    }

    //分析:
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == COLON)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_statement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    cout<<"*** This is situation son statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜缺省＞ ::= default : ＜语句＞
bool SyntaxAnalysis::ZSQX_default(){
    bool nextSymFlag;
    SymbolCode symbol;

    //分析default
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == DEFAULTSY)){
        return false;
    }

    //分析:
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == COLON)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    if(!ZSQX_statement()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    cout<<"*** This is default. ***"<<getLineNumber()<<endl;
    return true;

}

//＜值参数表＞ ::= ＜表达式＞{,＜表达式＞}
bool SyntaxAnalysis::ZSQX_valueParamTable(){
    bool nextSymFlag;
	SymbolCode symbol;
    //分析<表达式
    if(!ZSQX_expression()){
        return false;
    }

    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        //分析,
		symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == COMMA)){
            break;
        }
        //分析<表达式>
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        if(!ZSQX_expression()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }

    cout<<"*** This is value table. ***"<<getLineNumber()<<endl;
    return true;
}

//＜读语句＞ ::= scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
bool SyntaxAnalysis::ZSQX_readStatement(){
    bool nextSymFlag;
    SymbolCode symbol;

    //分析scanf
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SCANFSY)){
        return false;
    }
    //分析'('
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //分析<标识符>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    while(true){
        //分析,
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == COMMA)){
            break;
        }
        //分析<标识符>
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            break;
        }
    }
    
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
	//预读
	myLexicalAnalysis.nextSym();
    cout<<"*** This is read statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜写语句＞ ::= printf ‘(’ ＜字符串＞,＜表达式＞ ‘)’| printf ‘(’＜字符串＞ ‘)’| printf ‘(’＜表达式＞‘)’
bool SyntaxAnalysis::ZSQX_writeStatement(){
    bool nextSymFlag;
    SymbolCode symbol;

    //分析printf
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == PRINTFSY)){
        return false;
    }
    //分析'('
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    //复杂多变的部分
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == STRING){
        //分析是否为,
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //只有为,才继续分析,否则跳出
        if(symbol == COMMA){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            if(!ZSQX_expression()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }
    }else{
        //既不是字符串,也不是表达式
        if(!ZSQX_expression()){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }
    //分析')'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber());
        return false;
    }

    //预读
    myLexicalAnalysis.nextSym();
    cout<<"*** This is write statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜返回语句＞ ::= return[‘(’＜表达式＞‘)’]
bool SyntaxAnalysis::ZSQX_returnStatement(){
    bool nextSymFlag;
    SymbolCode symbol;
    bool preRead = true;

    //分析return
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RETURNSY)){
        return false;
    }
    //检查是否有[...]部分
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(nextSymFlag){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //如果是'('
        if(symbol == LSBRACKET){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            //分析<表达式>
            if(!ZSQX_expression()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            //分析')'
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RSBRACKET)){
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }else{
            preRead = false;
        }
    }else{
        preRead = false;
    }

    if(preRead)
        myLexicalAnalysis.nextSym();
    cout<<"*** This is return statement. ***"<<getLineNumber()<<endl;
    return true;
}

//＜整数＞ ::= ［＋｜－］＜无符号整数＞｜0
//注意,0前面不允许有任何的正负号
bool SyntaxAnalysis::ZSQX_integer(){
    bool nextSymFlag;
    SymbolCode symbol;
    //分析是否有+或-
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == ADD || symbol == SUB){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == INTNUM){
            if(myLexicalAnalysis.getGlobalNumber()==0){ // 不可以为0
                myError.SyntaxAnalysisError(GeneralError,getLineNumber());
                return false;
            }
        }else{//不是无符号整数
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }else if(symbol != INTNUM){
        return false;
    }

    myLexicalAnalysis.nextSym();
    cout<<"*** This is integer. ***"<<getLineNumber()<<endl;
    return true;
}

//＜声明头部＞ ::= int ＜标识符＞ |char ＜标识符＞
bool SyntaxAnalysis::ZSQX_declareHead(){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY || symbol == CHARSY){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(GeneralError,getLineNumber());
            return false;
        }
    }else{
        return false;
    }
    //预读
    myLexicalAnalysis.nextSym();
    cout<<"*** This is declare head. ***"<<getLineNumber()<<endl;
    return true;
}