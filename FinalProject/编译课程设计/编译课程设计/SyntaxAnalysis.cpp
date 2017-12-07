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
    isMainVoid = false;
	return_integer = 0;
	return_declare_funcName = "GLOBAL";
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
    ZSQX_constDescription("GLOBAL");
    //是否有变量说明
    ZSQX_varDescription(true,"GLOBAL");
    //检查是否有函数定义
    ZSQX_functionDefinition();
    //正式分析void main(){...}
    //在函数定义部分一定会识别到void main再返回
    SymbolCode symbol;
    //先检查是否为main
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == MAINSY && isMainVoid)){
        myError.SyntaxAnalysisError(NoMainFunctionError,getLineNumber());
        return false;
    }
    //进行下面的读取
	nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main() lack (");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){//(
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack (");
        myLexicalAnalysis.setNextSym();
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack )");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){//)
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack )");
        myLexicalAnalysis.setNextSym();
    }

	//进入填表,main函数入符号表
	pushItem("main","GLOBAL",VoidType);

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack {");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){//{
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack {");
        myLexicalAnalysis.setNextSym();
    }      

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack componud statement");
        return false;
    }
    //复合语句
    ZSQX_compoundStatement("main");

    if(myLexicalAnalysis.isFinish()){//没有结尾的},文件读取结束,报错
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack }");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){//}
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"main lack }");
        myLexicalAnalysis.setNextSym();
    }
    //预读:
    myLexicalAnalysis.nextSym();
    //正常分析结束,procedure识别
    return true;
}

//＜常量说明＞ ::= const＜常量定义＞;{ const＜常量定义＞;}
bool SyntaxAnalysis::ZSQX_constDescription(string funcName){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    //分析const
    if(!(symbol == CONSTSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack definition after \"const\".");
        return false;
    }
    //分析<常量定义>
    ZSQX_constDefinition(funcName);
    
    if(myLexicalAnalysis.isFinish()){//未分析结束,已经到达文件结尾
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after const definition.");
        return false;
    }
    //分析;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SEMI)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after const definition.");
        myLexicalAnalysis.setNextSym();
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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack definition after \"const\".");
            break;
        }
        //<常量定义>
        ZSQX_constDefinition(funcName);

        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after const definition.");
            break;
        }
        //分析;
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == SEMI)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after const definition.");
            myLexicalAnalysis.setNextSym();
        }
    }
    return true;
}

/*＜常量定义＞ ::= int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
        | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞} */
bool SyntaxAnalysis::ZSQX_constDefinition(string funcName){
    bool nextSymFlag;
    SymbolCode symbol;
	string id;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY){//int
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier after int.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //标识符
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after int is not identifier.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
		id = myLexicalAnalysis.getGlobalString();

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack = after identifier.");
            return false;
        }
        //=
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after identifier is not =");
            myLexicalAnalysis.skipRead(';');
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack integer after =.");
            return false;
        }
        //整数
        ZSQX_integer();
		//填符号表
		pushItem(id,funcName,return_integer);
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
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack contents after comma.");
                break;
            }
            //标识符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == IDENTIFIER)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after comma is not identifier.");
                myLexicalAnalysis.skipRead(';');
                break;
            }
			id = myLexicalAnalysis.getGlobalString();
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack = after identifier.");
                break;
            }
            //=
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == ASSIGN)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after identifier is not =.");
                myLexicalAnalysis.skipRead(';');
                break;
            }
            
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack integer after =.");
                break;
            }
            //整数
            ZSQX_integer();
			pushItem(id,funcName,return_integer);
        }

    }else if(symbol == CHARSY){//char
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier after char.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //标识符
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after char is not identifier.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
		id = myLexicalAnalysis.getGlobalString();

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack = after identifier.");
            return false;
        }
        //=
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after identifier is not =.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!(nextSymFlag)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const character after =.");
            return false;
        }
        //字符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == CHAR)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after = is not const character.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
		pushItem(id,funcName,myLexicalAnalysis.getGlobalChar());
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
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack contents after comma.");
                break;
            }
            //标识符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == IDENTIFIER)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after comma is not identifier.");
                myLexicalAnalysis.skipRead(';');
                break;
            }
			id = myLexicalAnalysis.getGlobalString();

            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack = after identifier.");
                break;
            }
            //=
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == ASSIGN)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after identifier is not =.");
                myLexicalAnalysis.skipRead(';');
                break;
            }
            
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!(nextSymFlag)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const character after =.");
                break;
            }
            //字符
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == CHAR)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after = is not const character.");
                myLexicalAnalysis.skipRead(';');
                break;
            }
			pushItem(id,funcName,myLexicalAnalysis.getGlobalChar());
        }
    }else{
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"incomplete const definition.");
        myLexicalAnalysis.skipRead(';');
        return false;
    }

    return true;
}

//＜变量说明＞ ::= ＜变量定义＞;{＜变量定义＞;}
//特殊的分析函数---由于跟全局的函数申明存在冲突
bool SyntaxAnalysis::ZSQX_varDescription(bool isGlobal, string funcName){
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
    if(!ZSQX_varDefinition(funcName))
        return false;

    if(myLexicalAnalysis.isFinish()){
        return false;
    }
    //;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == SEMI)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after var definition.");
        myLexicalAnalysis.setNextSym();
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
        if(!ZSQX_varDefinition(funcName))
            break;
        //;
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == SEMI)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon after var definition.");
            myLexicalAnalysis.setNextSym();
        }
    }
    return true;
}

/*＜变量定义＞ ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’)
            {,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’ )}*/
bool SyntaxAnalysis::ZSQX_varDefinition(string funcName){
    bool nextSymFlag;
    SymbolCode symbol;
	ValueType valueType;
	string id;
	int length;
    //类型标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == INTSY || symbol == CHARSY)){
        return false;
    }
	
	valueType = (symbol == INTSY) ? IntType : CharType;

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier after type identifier.");
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after type identifier is not identifier.");
        myLexicalAnalysis.skipRead(';');
        return false;
    }

	id = myLexicalAnalysis.getGlobalString();

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        return true;
    }
    //识别是否是[
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == LMBRACKET){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack contents after [.");
            return false;
        }
        //无符号整数
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol==INTNUM){
            int number = myLexicalAnalysis.getGlobalNumber();
            if(number == 0){//必须不为0
                myError.SyntaxAnalysisError(NotUnsignedIntegerError,getLineNumber());
                myLexicalAnalysis.skipRead(';');
                return false;
            }
        }else{
            myError.SyntaxAnalysisError(NotUnsignedIntegerError,getLineNumber());
            myLexicalAnalysis.skipRead(';');
            return false;
        }
		length = myLexicalAnalysis.getGlobalNumber();
        
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ] after int number.");
            return false;
        }
        //]
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RMBRACKET)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after int number is not ].");
            myLexicalAnalysis.setNextSym();
        }
		pushItem(id,funcName,valueType,length);
        //补足预读
        myLexicalAnalysis.nextSym();
	}
	else {
		pushItem(id,funcName,Variable,valueType);
	}
    //loop
    while(true){
        //,
        if(!(symbol == COMMA))
            break;

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier after comma");
            break;
        }
        //标识符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after comma is not integer.");
            break;
        }
		id = myLexicalAnalysis.getGlobalString();

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            break;
        }
        //识别是否是[
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == LMBRACKET){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack contents after [.");
                break;
            }
            //无符号整数
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol==INTNUM){
                int number = myLexicalAnalysis.getGlobalNumber();
                if(number == 0){//必须不为0
                    myError.SyntaxAnalysisError(NotUnsignedIntegerError,getLineNumber());
                    myLexicalAnalysis.skipRead(';');
                    break;
                }
            }else{
                myError.SyntaxAnalysisError(NotUnsignedIntegerError,getLineNumber());
                myLexicalAnalysis.skipRead(';');
                break;
            }
			length = myLexicalAnalysis.getGlobalNumber();
                
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ]");
                break;
            }
            //]
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RMBRACKET)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ]");
                myLexicalAnalysis.setNextSym();
            }
			pushItem(id, funcName, valueType, length);
            //补足预读
            myLexicalAnalysis.nextSym();
		}
		else {
			pushItem(id,funcName,Variable,valueType);
		}
    }

    return true;
}

//<函数定义部分> ::= {＜有返回值函数定义＞|＜无返回值函数定义＞}
bool SyntaxAnalysis::ZSQX_functionDefinition(){
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY || symbol == CHARSY){
        ZSQX_haveReturnValueFunctionDefinition();
    }else if(symbol == VOIDSY){
        ZSQX_noReturnValueFunctionDefinition();
    }else{
        return false;
    }

    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        
        if(symbol == INTSY || symbol == CHARSY){
            ZSQX_haveReturnValueFunctionDefinition();
        }else if(symbol == VOIDSY){
            ZSQX_noReturnValueFunctionDefinition();
        }else{
            break;
        }
    }
    return true;
}

/*＜有返回值函数定义＞ ::= ＜声明头部＞‘(’＜参数表＞‘)’ ‘{’＜复合语句＞‘}’|＜声明头部＞‘{’＜复合语句＞‘}’*/
bool SyntaxAnalysis::ZSQX_haveReturnValueFunctionDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
	string funcName;
    //声明头部
    ZSQX_declareHead();
	funcName = return_declare_funcName;

    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ( or {.");
        return false;
    }
    //检查是否为带参数
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == LSBRACKET){
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack param table.");
            return false;
        }
        //参数表
        ZSQX_paramTable(funcName);

        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
            return false;
        }
        //)
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RSBRACKET)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after param table need ).");
            myLexicalAnalysis.setNextSym();
        }
        //补足预读
        myLexicalAnalysis.nextSym();
    }
    //{
	symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack {.");
        myLexicalAnalysis.setNextSym();
    }
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack compound statement.");
        return false;
    }
    //复合语句
    ZSQX_compoundStatement(funcName);

    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
        return false;
    }
    //}
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(GeneralError,getLineNumber(),"is not } to end");
        myLexicalAnalysis.setNextSym();
    }
    //预读
    myLexicalAnalysis.nextSym();

    return true;
}

//＜无返回值函数定义＞ ::= void＜标识符＞(’＜参数表＞‘)’‘{’＜复合语句＞‘}’| void＜标识符＞{’＜复合语句＞‘}’
bool SyntaxAnalysis::ZSQX_noReturnValueFunctionDefinition(){
    bool nextSymFlag;
    SymbolCode symbol;
	string funcName;
    //void
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == VOIDSY)){
        return false;
    }

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack function name.");
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        if(symbol == MAINSY){
            isMainVoid = true;
            return true;
        }
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack function name.");
        myLexicalAnalysis.skipRead(';');
        return false;
    }

	funcName = myLexicalAnalysis.getGlobalString();
	pushItem(funcName,"GLOBAL",VoidType);

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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after ( lack contents.");
            return false;
        }
        //参数表
        ZSQX_paramTable(funcName);

        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
            return false;
        }
        //)
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RSBRACKET)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
            myLexicalAnalysis.setNextSym();
        }
        //补足预读
        myLexicalAnalysis.nextSym();
    }
    //{
	symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack {.");
        myLexicalAnalysis.setNextSym();
    }
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack compound statement.");
        return false;
    }
    //复合语句
    ZSQX_compoundStatement(funcName);

    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
        return false;
    }
    //}
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
        myLexicalAnalysis.setNextSym();
    }
    //预读
    myLexicalAnalysis.nextSym();

    return true;
}

//＜参数表＞ ::= ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}
bool SyntaxAnalysis::ZSQX_paramTable(string funcName){
    bool nextSymFlag;
    SymbolCode symbol;
	ValueType valueType;
	string id;
    //类型标识符 int|char
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == INTSY || symbol == CHARSY)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"param table can\'t be empty.");
        myLexicalAnalysis.skipRead(')');
        return false;
    }

	valueType = (symbol == INTSY) ? IntType : CharType;

    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
        return false;
    }
    //标识符
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
        myLexicalAnalysis.skipRead(')');
        return false;
    }
	id = myLexicalAnalysis.getGlobalString();
	pushItem(id,funcName,Parament,valueType);

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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack type identifier.");
            break;
        }
        //类型标识符 int|char
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == INTSY || symbol == CHARSY)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack type identifier.");
            myLexicalAnalysis.skipRead(')');
            break;
        }
		valueType = (symbol == INTSY) ? IntType : CharType;

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            break;
        }
        //标识符
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            myLexicalAnalysis.skipRead(')');
            break;
        }
		id = myLexicalAnalysis.getGlobalString();
		pushItem(id,funcName,Parament,valueType);
    }

    return true;
}

//＜复合语句＞ ::= ［＜常量说明＞］［＜变量说明＞］｛＜语句＞｝
bool SyntaxAnalysis::ZSQX_compoundStatement(string funcName){
    ZSQX_constDescription(funcName);
    ZSQX_varDescription(false,funcName);

    while(true){
        if(!(ZSQX_statement()))
            break;
    }

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
        myLexicalAnalysis.nextSym();
    }
    //<项>
    ZSQX_item();
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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack item.");
            break;
        }
        //<项>
        ZSQX_item();
    }

    return true;
}

//＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
bool SyntaxAnalysis::ZSQX_item(){
    bool nextSymFlag;
    SymbolCode symbol;
    ZSQX_factor();

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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack factor.");
            break;
        }
        //<因子>
        ZSQX_factor();
    }
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
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression after [.");
                    return false;
                }
                //<表达式>
                ZSQX_expression();

                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ].");
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RMBRACKET)){//]
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ].");
                    myLexicalAnalysis.setNextSym();
                }
            }else if(symbol == LSBRACKET){//(
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack param table.");
                    return false;
                }
                //<值参数表>
                ZSQX_valueParamTable();

                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RSBRACKET)){//)
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                    myLexicalAnalysis.setNextSym();
                }
            }else{//仅仅是标识符,无需预读
                preRead = false;
            }
            break;
        case INTNUM:
        case ADD:
        case SUB:
            ZSQX_integer();
			preRead = false;
            break;
        case CHAR://直接正确
            break;
        case LSBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"only (.");
                return false;
            }
            //<表达式
            ZSQX_expression();
            //)
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RSBRACKET)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                myLexicalAnalysis.setNextSym();
            }
            break;
        default:
            return false;
            break;
    }

    //预读
    if(preRead)
        myLexicalAnalysis.nextSym();
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
            ZSQX_conditionStatement();
            preRead = false;
            break;
        case WHILESY:
            ZSQX_loopStatement();
            preRead = false;
            break;
        case LBBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                break;
            }
            while(true){
                //<语句>
                if(!ZSQX_statement())
					break;
                if(myLexicalAnalysis.isFinish()){
                    break;
                }
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RBBRACKET)){//}
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
                myLexicalAnalysis.setNextSym();
            }
            break;
        case IDENTIFIER://赋值语句与调用语句
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){//单纯的标识符
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"not an illegal statement.");
                myLexicalAnalysis.skipRead('\n');
                break;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol == SEMI){//无参调用
                break;
            }else if(symbol == LSBRACKET){//有参调用
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack param table.");
                    return false;
                }
                //<值参数表>
                ZSQX_valueParamTable();

                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == RSBRACKET)){//)
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                    myLexicalAnalysis.setNextSym();
                }

                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                    return false;
                }
                //;
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == SEMI)){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                    myLexicalAnalysis.setNextSym();
                }
            }else if(symbol == ASSIGN || symbol == LMBRACKET){//赋值语句识别前缀(去除标识符)
                ZSQX_assignStatement();
                
                if(myLexicalAnalysis.isFinish()){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                    return false;
                }
                symbol = myLexicalAnalysis.getGlobalSymbol();
                if(!(symbol == SEMI)){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                    myLexicalAnalysis.setNextSym();
                }
            }else{
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"illegal content after statement identifier.");
                myLexicalAnalysis.skipRead('\n');
                return false;
            }
            break;
        case SCANFSY:
            ZSQX_readStatement();

            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                myLexicalAnalysis.setNextSym();
            }
            break;
        case PRINTFSY:
            ZSQX_writeStatement();

            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                myLexicalAnalysis.setNextSym();
            }
            break;
        case SEMI://空语句
            break;
        case SWITCHSY:
            ZSQX_situationStatement();

            preRead = false;
            break;
        case RETURNSY:
            ZSQX_returnStatement();

            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == SEMI)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack semicolon.");
                myLexicalAnalysis.setNextSym();
            }
            break;
        default:
            return false;
            break;
    }
    //预读
    if(preRead)
        myLexicalAnalysis.nextSym();
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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            return false;
        }
        //<表达式>
        ZSQX_expression();

    }else if(symbol == LMBRACKET){//[
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            return false;
        }
        //<表达式>
        ZSQX_expression();
        //]
        if(myLexicalAnalysis.isFinish()){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ].");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == RMBRACKET)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ].");
            myLexicalAnalysis.setNextSym();
        }
        //assign =
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack =.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ASSIGN)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack =.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
        //下面分析 = <表达式>
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            return false;
        }
        //<表达式>
        ZSQX_expression();

    }else{
        return false;
    }
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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        myLexicalAnalysis.setNextSym();
    }
    //识别<条件>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack condition.");
        return false;
    }
    ZSQX_condition();

    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        return false;
    }
    //)
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        myLexicalAnalysis.setNextSym();
    }

    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
        return false;
    }
    
    ZSQX_statement();

    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack else.");
        return false;
    }
    //else
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == ELSESY)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack else.");
        myLexicalAnalysis.skipRead('\n');
        return false;
    }

    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
        return false;
    }
    ZSQX_statement();
    return true;
}

//＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ 
//＜关系运算符＞ ::= <｜<=｜>｜>=｜!=｜==
bool SyntaxAnalysis::ZSQX_condition(){
    bool nextSymFlag;
    SymbolCode symbol;
    //<表达式>
    ZSQX_expression();

    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol>=LESS && symbol<=MORE){
            //已识别关系运算符
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
                return false;
            }
            //<表达式>
            ZSQX_expression();
        }
    }
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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        myLexicalAnalysis.setNextSym();
    }
    //识别<条件>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack condition.");
        return false;
    }
    ZSQX_condition();
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        return false;
    }
    //)
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        myLexicalAnalysis.setNextSym();
    }

    //<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
        return false;
    }

    ZSQX_statement();
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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        myLexicalAnalysis.setNextSym();
    }
    //分析<表达式>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
        return false;
    }
    ZSQX_expression();
    //分析')'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        myLexicalAnalysis.setNextSym();
    }
    //分析'{'
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack {.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LBBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack {.");
        myLexicalAnalysis.setNextSym();
    }
    //分析＜情况表＞[＜缺省＞]
	nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack situation table.");
        return false;
    }
    ZSQX_situationTable();
    //分析是否有缺省
    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == DEFAULTSY){
            ZSQX_default();
        }
    }
    //分析'}'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RBBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack }.");
        myLexicalAnalysis.setNextSym();
    }
    //预读
    myLexicalAnalysis.nextSym();
    return true;
}

//＜情况表＞ ::= ＜情况子语句＞{＜情况子语句＞}
bool SyntaxAnalysis::ZSQX_situationTable(){
    //分析情况子语句
    ZSQX_situationSonStatement();

    while(true){
        if(myLexicalAnalysis.isFinish())
            break;
        if(!ZSQX_situationSonStatement())
            break;
    }

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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    switch(symbol){
        case INTNUM:
        case ADD:
        case SUB:
            ZSQX_integer();
            break;
        case CHAR:
            //补读
            myLexicalAnalysis.nextSym();
            break;
        default:
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const.");
            myLexicalAnalysis.skipRead('\n');
            return false;
            break;
    }

    //分析:
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack colon.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == COLON)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack colon.");
        myLexicalAnalysis.setNextSym();
    }
    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
        return false;
    }
    ZSQX_statement();
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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack :.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == COLON)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack :.");
        myLexicalAnalysis.setNextSym();
    }
    //分析<语句>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
        return false;
    }
    
    ZSQX_statement();
    return true;

}

//＜值参数表＞ ::= ＜表达式＞{,＜表达式＞}
bool SyntaxAnalysis::ZSQX_valueParamTable(){
    bool nextSymFlag;
	SymbolCode symbol;
    //分析<表达式
    ZSQX_expression();

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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            break;
        }
        ZSQX_expression();
    }

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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        myLexicalAnalysis.setNextSym();
    }
    //分析<标识符>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == IDENTIFIER)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
        myLexicalAnalysis.skipRead(';');
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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            myLexicalAnalysis.skipRead(';');
            break;
        }
    }
    
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        myLexicalAnalysis.setNextSym();
    }
	//预读
	myLexicalAnalysis.nextSym();
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
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == LSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack (.");
        myLexicalAnalysis.setNextSym();
    }
    //复杂多变的部分
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"after ( lack contents.");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == STRING){
        //分析是否为,
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack comma.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        //只有为,才继续分析,否则跳出
        if(symbol == COMMA){
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
                return false;
            }
            ZSQX_expression();
        }
    }else{
        //既不是字符串,也不是表达式
        ZSQX_expression();
    }
    //分析')'
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        return false;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == RSBRACKET)){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
        myLexicalAnalysis.setNextSym();
    }

    //预读
    myLexicalAnalysis.nextSym();
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
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
                return false;
            }
            //分析<表达式>
            ZSQX_expression();
            //分析')'
            if(myLexicalAnalysis.isFinish()){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                return false;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(!(symbol == RSBRACKET)){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack ).");
                myLexicalAnalysis.setNextSym();
            }
        }else{
            preRead = false;
        }
    }else{
        preRead = false;
    }

    if(preRead)
        myLexicalAnalysis.nextSym();
    return true;
}

//＜整数＞ ::= ［＋｜－］＜无符号整数＞｜0
//注意,0前面不允许有任何的正负号
bool SyntaxAnalysis::ZSQX_integer(){
    bool nextSymFlag;
    SymbolCode symbol;
	int value = 0;
	bool isMinus = false;//是否是取反
    //分析是否有+或-
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == ADD || symbol == SUB){
		
		isMinus = (symbol == ADD) ? false : true;
        
		nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack int num after +|-.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == INTNUM){
			value = myLexicalAnalysis.getGlobalNumber();
            if(value==0){ // 不可以为0
                myError.SyntaxAnalysisError(ZeroPrefixSignError,getLineNumber());
                return false;
            }
        }else{//不是无符号整数
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack unsigned integer.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
    }else if(symbol != INTNUM){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"vital part is not integer.");
        myLexicalAnalysis.skipRead(';');
        return false;
	}
	else {
		value = myLexicalAnalysis.getGlobalNumber();
	}
	if (isMinus)
		value = -value;
	return_integer = value;//设置返回值
    myLexicalAnalysis.nextSym();
    return true;
}

//＜声明头部＞ ::= int ＜标识符＞ |char ＜标识符＞
bool SyntaxAnalysis::ZSQX_declareHead(){
    bool nextSymFlag;
    SymbolCode symbol;
	FunctionType type;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol == INTSY || symbol == CHARSY){
		
		type = (symbol == INTSY) ? ReturnIntType : ReturnCharType;

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            return false;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == IDENTIFIER)){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack identifier.");
            myLexicalAnalysis.skipRead(';');
            return false;
        }
		return_declare_funcName = myLexicalAnalysis.getGlobalString();
		pushItem(return_declare_funcName,"GLOBAL",type);
    }else{
        return false;
    }
    //预读
    myLexicalAnalysis.nextSym();
    return true;
}

//整数常量
void SyntaxAnalysis::pushItem(string id, string functionName, int num) {
	if (!isAbleInsert(id,functionName))
		return;
	SymbolTableItem newItem(id,functionName);
	newItem.setItemType(Constant);
	newItem.setValueType(IntType);
	newItem.setConstInt(num);
	globalSymbolTable.push_back(newItem);
	cout << "Push in: " << id << " " << functionName << " const int " << num << endl;
}
//字符常量
void SyntaxAnalysis::pushItem(string id, string functionName, char character) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(Constant);
	newItem.setValueType(CharType);
	newItem.setConstChar(character);
	globalSymbolTable.push_back(newItem);
	cout << "Push in: " << id << " " << functionName << " const char " << character << endl;
}
//数组变量
void SyntaxAnalysis::pushItem(string id, string functionName,ValueType valueType, int size) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(Variable);
	newItem.setValueType(valueType);
	newItem.setArrSize(size);
	globalSymbolTable.push_back(newItem);
	cout << "Push in: " << id << "[" << size << "] " << functionName;
	if (valueType == IntType) {
		cout << " int arr" << endl;
	}
	else {
		cout << " char arr" << endl;
	}
}
//变量+参数
void SyntaxAnalysis::pushItem(string id, string functionName, ItemType itemType, ValueType valueType) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(itemType);
	newItem.setValueType(valueType);
	globalSymbolTable.push_back(newItem);
	if (itemType == Variable) {
		if (valueType == IntType) {
			cout << "Push in: " << id << " " << functionName << " var int." << endl;
		}
		else {
			cout << "Push in: " << id << " " << functionName << " var char." << endl;
		}
	}
	else {
		if (valueType == IntType) {
			cout << "Push in: " << id << " " << functionName << " param int." << endl;
		}
		else {
			cout << "Push in: " << id << " " << functionName << " param char." << endl;
		}
	}
}
//函数
void SyntaxAnalysis::pushItem(string id, string functionName, FunctionType funcType) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(Function);
	newItem.setFuncType(funcType);
	globalSymbolTable.push_back(newItem);
	if (funcType == VoidType) {
		cout << "Push in:" << id << " " << functionName << " void function" << endl;
	}
	else if (funcType == ReturnIntType) {
		cout << "Push in:" << id << " " << functionName << " int function" << endl;
	}
	else {
		cout << "Push in:" << id << " " << functionName << " char function" << endl;
	}
}

//检查是否可填表
bool SyntaxAnalysis::isAbleInsert(string id, string functionName) {
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		//作用域相同,名字也相同
		if (functionName == item.getFuncName() && id == item.getId()) {
			myError.SemanticAnalysisError(DeclareConflictError,getLineNumber(),id);
			return false;
		}
	}
	return true;
}

//检查是否定义
bool SyntaxAnalysis::isDefined(string id, string functionName) {
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {
			if (id == item.getId())
				return true;
		}
		else if (item.getFuncName() == functionName) {
			if (id == item.getId()) {
				return true;
			}
		}
	}
	myError.SemanticAnalysisError(NotDefinitionError,getLineNumber(),id);
	return false;
}