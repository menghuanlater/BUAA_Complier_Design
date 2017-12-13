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
	FourYuanItem four;
	four.type = FunctionDef;
	four.funcType = VoidType;
	four.target = "main";
	globalTmpCodeArr.push_back(four);

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
		symbol = myLexicalAnalysis.getGlobalSymbol();
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
	//在函数定义完成之时,最终都要加上一句return;
	FourYuanItem item;
	item.type = ReturnEmpty;
	globalTmpCodeArr.push_back(item);
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
	FourYuanItem insert;
	insert.type = TmpCodeType::FunctionDef;
	insert.funcType = VoidType;
	insert.target = funcName;
	globalTmpCodeArr.push_back(insert);

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
	FourYuanItem item;
	item.type = ReturnEmpty;
	globalTmpCodeArr.push_back(item);
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
	FourYuanItem item;
	item.type = ParamDef;
	item.target = id;
	item.valueType = valueType;
	globalTmpCodeArr.push_back(item);

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
		FourYuanItem item;
		item.type = ParamDef;
		item.target = id;
		item.valueType = valueType;
		globalTmpCodeArr.push_back(item);
    }

    return true;
}

//＜复合语句＞ ::= ［＜常量说明＞］［＜变量说明＞］｛＜语句＞｝
bool SyntaxAnalysis::ZSQX_compoundStatement(string funcName){
    ZSQX_constDescription(funcName);
    ZSQX_varDescription(false,funcName);

    while(true){
        if(!(ZSQX_statement(funcName,false,noUseCache)))
            break;
    }

    return true;
}

//＜表达式＞ ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
ExpRet SyntaxAnalysis::ZSQX_expression(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
    bool x_flag = false;//作为是否有前缀项的flag
	
	//生成代码有关
	bool isSure = false;
	int expResult = 0;
	ValueType type;
	vector<PostfixItem> tar, obj;
	ExpRet returnValue;
	
	//检查是否有[+|-]
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(symbol== ADD || symbol == SUB){
        x_flag = true;
		PostfixItem item;
		item.type = CharType;
		item.number = (symbol == ADD) ? '+' : '-';
		tar.push_back(item);
        //补足预读
        myLexicalAnalysis.nextSym();
    }
    //<项>
    ZSQX_item(tar,funcName,isCache,cache);
    //循环
    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == ADD || symbol == SUB)){
            break;
        }
		PostfixItem item;
		item.type = CharType;
		item.number = (symbol == ADD) ? '+' : '-';
		tar.push_back(item);

        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack item.");
            break;
        }
        //<项>
        ZSQX_item(tar,funcName,isCache,cache);
    }
	//表达式计算
	turnToPostfixExp(tar,obj);
	returnValue.name = calculateExp(obj, isSure,type,expResult,getLineNumber(),isCache,cache,funcName);
	returnValue.isSurable = isSure;
	returnValue.type = type;
	if (isSure) {
		if (type == IntType)
			returnValue.number = expResult;
		else
			returnValue.character = expResult;
	}
    return returnValue;
}

//＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
bool SyntaxAnalysis::ZSQX_item(vector<PostfixItem> & obj, string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
    ZSQX_factor(obj,funcName,isCache,cache);

    while(true){
        if(myLexicalAnalysis.isFinish()){
            break;
        }
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(!(symbol == MULT || symbol == DIV)){
            break;
        }
		PostfixItem item;
		item.type = CharType;
		item.number = (symbol == MULT) ? '*' : '/';
		obj.push_back(item);
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack factor.");
            break;
        }
        //<因子>
        ZSQX_factor(obj,funcName, isCache, cache);
    }
    return true;
}

//＜因子＞ ::= ＜标识符＞[‘(’<值参数表>‘)’]｜＜标识符＞‘[’＜表达式＞‘]’|‘(’＜表达式＞‘)’｜＜整数＞|＜字符＞
bool SyntaxAnalysis::ZSQX_factor(vector<PostfixItem> & obj, string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
    bool preRead = true;
    symbol = myLexicalAnalysis.getGlobalSymbol();
	PostfixItem item;
	ExpRet item2;
	FourYuanItem item3;
	string id;

    switch(symbol){
        case IDENTIFIER:
			id = myLexicalAnalysis.getGlobalString();
            //最复杂的地方
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                preRead = false;
                break;
            }
            //标识符已经识别
            symbol = myLexicalAnalysis.getGlobalSymbol();
			if (symbol == LMBRACKET) {//[
				nextSymFlag = myLexicalAnalysis.nextSym();
				if (!nextSymFlag) {
					myError.SyntaxAnalysisError(LackComposedPartError, getLineNumber(), "lack expression after [.");
					return false;
				}
				//<表达式>
				item2 = ZSQX_expression(funcName, isCache, cache);
				string index2;
				int orderx;
				if (item2.isSurable) {
					item3.type = AssignState;
					item3.target = generateVar(funcName);
					item3.isLeftArr = false;
					item3.isTargetArr = false;
					if (item2.type == CharType) {
						orderx = idArrExpCheck(id, funcName, true, item2.character);
						char gv[10] = { '\0' };
						sprintf(gv, "%d", item2.character);
						item3.left = gv;
						item3.op = '+';
						item3.right = "0";
					}
					else {
						orderx = idArrExpCheck(id, funcName, true, item2.number);
						char gv[10] = { '\0' };
						sprintf(gv, "%d", item2.number);
						item3.left = gv;
						item3.op = '+';
						item3.right = "0";
					}
					if (isCache) {
						cache.push_back(item3);
					}
					else {
						globalTmpCodeArr.push_back(item3);
					}
					index2 = item3.target;
				}
				else {
					orderx = idArrExpCheck(id, funcName, false);
					index2 = item2.name;
				}
				if (orderx >= 0) {
					item3.type = AssignState;
					item3.target = generateVar(funcName);
					item3.isLeftArr = true;
					item3.isTargetArr = false;
					char ggg[10] = { '\0' };
					sprintf(ggg, "%d", orderx);
					item3.left = "G" + string(ggg) + id;
					item3.index2 = index2;
					if (isCache) {
						cache.push_back(item3);
					}
					else {
						globalTmpCodeArr.push_back(item3);
					}
					
					item.type = StringType;
					SymbolTableItem t = globalSymbolTable.at(orderx);
					item.isNotCharVar = true;
					if (t.getValueType() == CharType)
						item.isNotCharVar = false;
					item.str = item3.target;
					obj.push_back(item);
				}
				else {
					item.type = StringType;
					item.str = id;
				}

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
                ZSQX_valueParamTable(funcName, isCache, cache);
				item3.type = FunctionCall;
				item3.target = id;
				if (isCache) {
					cache.push_back(item3);
				}
				else {
					globalTmpCodeArr.push_back(item3);
				}
				item3.type = AssignState;
				item3.target = generateVar(funcName);
				item3.isTargetArr = item3.isLeftArr = false;
				item3.left = "Ret";
				item3.op = '+';
				item3.right = "0";
				if (isCache) {
					cache.push_back(item3);
				}
				else {
					globalTmpCodeArr.push_back(item3);
				}
				//待完善:检查函数是否存在,返回其所在符号表的order,根据其返回类型决定isChar的值
				item.type = StringType;
				item.str = item3.target;
				item.isNotCharVar = true;
				obj.push_back(item);

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
				int order = idCheckInFactor(id,funcName);
				if (order >= 0) {
					//需要检查是否是无参的函数
					SymbolTableItem y = globalSymbolTable.at(order);
					if (y.getItemType() == Constant) {
						item.type = y.getValueType();
						item.number = (item.type == IntType) ? (y.getConstInt()) : (y.getConstChar());
					}
					else if (y.getItemType() == Function) {//无参数的带返回值的函数调用
						item3.type = FunctionCall;
						item3.target = id;
						if (isCache) {
							cache.push_back(item3);
						}
						else {
							globalTmpCodeArr.push_back(item3);
						}
						item3.type = AssignState;
						item3.target = generateVar(funcName);
						item3.isTargetArr = item3.isLeftArr = false;
						item3.left = "Ret";
						item3.op = '+';
						item3.right = "0";
						if (isCache) {
							cache.push_back(item3);
						}
						else {
							globalTmpCodeArr.push_back(item3);
						}
						item.type = StringType;
						item.str = item3.target;
						item.isNotCharVar = (y.getFuncType() == ReturnCharType) ? false : true;
					}
					else {
						item.isNotCharVar = true;
						if (y.getItemType() == Variable && y.getValueType() == CharType)
							item.isNotCharVar = false;
						item.type = StringType;
						char ggg[10] = {'\0'};
						sprintf(ggg,"%d",order);
						item.str = "G" + string(ggg) + id;;//G12ppp类似
					}
				}
				else {
					item.type = StringType;
					item.isNotCharVar = true;
					item.str = id;
					if (isCache) {
						cache.push_back(item3);
					}
					else {
						globalTmpCodeArr.push_back(item3);
					}
				}
				obj.push_back(item);
            }
            break;
        case INTNUM:
        case ADD:
        case SUB:
            ZSQX_integer();
			item.type = IntType;
			item.number = return_integer;
			obj.push_back(item);
			preRead = false;
            break;
        case CHAR://直接正确
			item.type = CharType;
			item.number = myLexicalAnalysis.getGlobalChar();
			obj.push_back(item);
            break;
        case LSBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"only (.");
                return false;
            }
            //<表达式
            item2 = ZSQX_expression(funcName, isCache, cache);
			if (item2.isSurable) {
				item.type = IntType;
				item.number = (item2.type == IntType) ? item2.number : item2.character;
			}
			else {
				item.type = StringType;
				item.str = item2.name;
				item.isNotCharVar = (item2.type == IntType) ? true : false;
			}
			obj.push_back(item);
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
bool SyntaxAnalysis::ZSQX_statement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
    bool preRead = true;
	string id;
	FourYuanItem four;
	four.type = FunctionCall;
    
    switch(symbol){
        case IFSY:
            ZSQX_conditionStatement(funcName, isCache, cache);
            preRead = false;
            break;
        case WHILESY:
            ZSQX_loopStatement(funcName, isCache, cache);
            preRead = false;
            break;
        case LBBRACKET:
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                break;
            }
            while(true){
                //<语句>
                if(!ZSQX_statement(funcName, isCache, cache))
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
			id = myLexicalAnalysis.getGlobalString();
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){//单纯的标识符
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"not an illegal statement.");
                myLexicalAnalysis.skipRead('\n');
                break;
            }
            symbol = myLexicalAnalysis.getGlobalSymbol();
            if(symbol == SEMI){//无参调用
				four.target = id;
				if (isCache) {
					cache.push_back(four);
				}
				else {
					globalTmpCodeArr.push_back(four);
				}
                break;
            }else if(symbol == LSBRACKET){//有参调用
                nextSymFlag = myLexicalAnalysis.nextSym();
                if(!nextSymFlag){
                    myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack param table.");
                    return false;
                }
                //<值参数表>
                ZSQX_valueParamTable(funcName, isCache, cache);
				four.target = id;
				if (isCache) {
					cache.push_back(four);
				}
				else {
					globalTmpCodeArr.push_back(four);
				}

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
                ZSQX_assignStatement(funcName,id, isCache, cache);
                
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
            ZSQX_readStatement(funcName, isCache, cache);

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
            ZSQX_writeStatement(funcName, isCache, cache);

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
            ZSQX_situationStatement(funcName, isCache, cache);

            preRead = false;
            break;
        case RETURNSY:
            ZSQX_returnStatement(funcName, isCache, cache);

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
bool SyntaxAnalysis::ZSQX_assignStatement(string funcName,string id, bool isCache, vector<FourYuanItem> & cache){
    //无需分析标识符,已经在语句中分析得出
    bool nextSymFlag;
    SymbolCode symbol;
    symbol = myLexicalAnalysis.getGlobalSymbol();
	FourYuanItem fourItem;
	fourItem.type = AssignState;
	fourItem.isTargetArr = fourItem.isLeftArr = false;
	fourItem.op = '+';
	fourItem.right = "0";

    if(symbol == ASSIGN){//=
        nextSymFlag = myLexicalAnalysis.nextSym();
        if(!nextSymFlag){
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            return false;
        }
		int order = checkAssignId(id,funcName);
        //<表达式>
        ExpRet ret = ZSQX_expression(funcName, isCache, cache);
		if (order >= 0)
			checkTypeMatch(globalSymbolTable.at(order).getValueType(), ret.type);
		char ggg[10] = {'\0'};
		sprintf(ggg,"%d",order);
		fourItem.target = (order >= 0) ? ("G" + string(ggg) + id) : id;
		if (ret.isSurable) {
			char x[15] = {'\0'};
			sprintf(x,"%d",(ret.type == IntType)? ret.number:ret.character);
			fourItem.left = x;
		}
		else {
			fourItem.left = ret.name;
		}
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}

	}
	else if (symbol == LMBRACKET) {//[
		nextSymFlag = myLexicalAnalysis.nextSym();
		if (!nextSymFlag) {
			myError.SyntaxAnalysisError(LackComposedPartError, getLineNumber(), "lack expression.");
			return false;
		}
		//<表达式>
		fourItem.isTargetArr = true;
		ExpRet ret = ZSQX_expression(funcName, isCache, cache);
		int orderx;
		if (ret.isSurable) {
			if (ret.type == CharType) {
				orderx = idArrExpCheck(id, funcName, true, ret.character);
				char x[15] = {'\0'};
				sprintf(x,"%d",ret.character);
				fourItem.index1 = x;
			}
			else {
				orderx = idArrExpCheck(id, funcName, true, ret.number);
				char x[15] = { '\0' };
				sprintf(x, "%d", ret.number);
				fourItem.index1 = x;
			}
		}
		else {
			orderx = idArrExpCheck(id, funcName, false);
			fourItem.index1 = ret.name;
		}
		if (orderx >= 0) {
			char ggg[10] = { '\0' };
			sprintf(ggg,"%d",orderx);
			fourItem.target = "G" + string(ggg) + id;
		}

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
        ret = ZSQX_expression(funcName, isCache, cache);
		if (ret.isSurable) {
			char x[15] = {'\0'};
			sprintf(x,"%d",ret.type==IntType ? ret.number : ret.character);
			fourItem.left = x;
		}
		else {
			fourItem.left = ret.name;
		}
		checkTypeMatch(globalSymbolTable.at(orderx).getValueType(), ret.type);
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}
    }else{
        return false;
    }
    return true;
}

//＜条件语句＞::= if ‘(’＜条件＞‘)’＜语句＞else＜语句＞
bool SyntaxAnalysis::ZSQX_conditionStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	FourYuanItem four;
    symbol = myLexicalAnalysis.getGlobalSymbol();
	
	string label1 = generateLabel();
	string label2 = generateLabel();
    
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
    
	string judge = ZSQX_condition(funcName, isCache, cache);
	//设置跳转语句
	switch (relation) {
	case LESS:
		four.type = BGEZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case LESSEQ:
		four.type = BGZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case EQUAL:
		four.type = BNZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case MORE:
		four.type = BLEZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case MOREEQ:
		four.type = BLZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case NOTEQ:
		four.type = BEZ;
		four.target = label1;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	}

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
    
    ZSQX_statement(funcName, isCache, cache);
	//先设好无条件跳转
	four.type = Jump;
	four.target = label2;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
	}

	four.type = Label;
	four.target = label1;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
	}

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
    ZSQX_statement(funcName, isCache, cache);
	four.type = Label;
	four.target = label2;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
	}
    return true;
}

//＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ 
//＜关系运算符＞ ::= <｜<=｜>｜>=｜!=｜==
string SyntaxAnalysis::ZSQX_condition(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	FourYuanItem fourItem;
	string  left, right;
    //<表达式>
    ExpRet ret1 =  ZSQX_expression(funcName, isCache, cache);
	if (ret1.isSurable) {
		fourItem.type = AssignState;
		fourItem.isLeftArr = fourItem.isTargetArr = false;
		char x[15] = { '\0' };
		sprintf(x,"%d",ret1.type == IntType? ret1.number:ret1.character);
		fourItem.target = generateVar(funcName);
		fourItem.left = x;
		fourItem.op = '+';
		fourItem.right = "0";
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}
		left = fourItem.target;
	}
	else {
		left = ret1.name;
	}

    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol>=LESS && symbol<=MORE){
            //已识别关系运算符
			relation = symbol;
            nextSymFlag = myLexicalAnalysis.nextSym();
            if(!nextSymFlag){
                myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack statement.");
                return "";
            }
            //<表达式>
            ExpRet ret2 = ZSQX_expression(funcName, isCache, cache);
			if (ret2.isSurable) {
				fourItem.type = AssignState;
				fourItem.isLeftArr = fourItem.isTargetArr = false;
				char x[15] = { '\0' };
				sprintf(x, "%d", ret2.type == IntType ? ret2.number : ret2.character);
				fourItem.target = generateVar(funcName);
				fourItem.left = x;
				fourItem.op = '+';
				fourItem.right = "0";
				if (isCache) {
					cache.push_back(fourItem);
				}
				else {
					globalTmpCodeArr.push_back(fourItem);
				}
				right = fourItem.target;
			}
			else {
				right = ret2.name;
			}
			//
			fourItem.target = generateVar(funcName);
			fourItem.type = AssignState;
			fourItem.isLeftArr = fourItem.isTargetArr = false;
			fourItem.left = left;
			fourItem.right = right;
			fourItem.op = '-';
			if (isCache) {
				cache.push_back(fourItem);
			}
			else {
				globalTmpCodeArr.push_back(fourItem);
			}
			return fourItem.target;
        }
		
    }
	relation = NOTEQ;
	return fourItem.target;
}

//＜循环语句＞ ::= while ‘(’＜条件＞‘)’＜语句＞
bool SyntaxAnalysis::ZSQX_loopStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;

	FourYuanItem four;

	string label1 = generateLabel();
	string label2 = generateLabel();

    //while
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == WHILESY)){
        return false;
    }

	four.type = Label;
	four.target = label1;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
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
    string judge = ZSQX_condition(funcName, isCache, cache);
	//设置条件跳转
	switch (relation) {
	case LESS:
		four.type = BGEZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case LESSEQ:
		four.type = BGZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case EQUAL:
		four.type = BNZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case MORE:
		four.type = BLEZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case MOREEQ:
		four.type = BLZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	case NOTEQ:
		four.type = BEZ;
		four.target = label2;
		four.left = judge;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		break;
	}

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

    ZSQX_statement(funcName, isCache, cache);
	four.type = Jump;//无条件跳转到循环
	four.target = label1;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
	}
	//循环跳出点
	four.type = Label;
	four.target = label2;
	if (isCache) {
		cache.push_back(four);
	}
	else {
		globalTmpCodeArr.push_back(four);
	}
    return true;
}

//＜情况语句＞ ::= switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞[＜缺省＞] ‘}’
bool SyntaxAnalysis::ZSQX_situationStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	string endLabel = generateLabel();//switch结束点

	FourYuanItem fourItem;
	string left;
	vector<FourYuanItem> myCache;

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
    ExpRet ret = ZSQX_expression(funcName, isCache, cache);
	if (ret.isSurable) {
		left = generateVar(funcName);
		fourItem.type = AssignState;
		fourItem.isTargetArr = fourItem.isLeftArr = false;
		fourItem.target = left;
		char x[15] = {'\0'};
		sprintf(x,"%d",ret.type == IntType ? ret.number : ret.character);
		fourItem.left = x;
		fourItem.op = '+';
		fourItem.right = "0";
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}
	}
	else {
		left = ret.name;
	}
	//left为比较case的关键变量
	
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
	//跳转label的各种中间指令
    vector<CaseRet> caseTable = ZSQX_situationTable(funcName,endLabel,myCache);
	for (unsigned int i = 0; i < caseTable.size(); i++) {
		CaseRet t = caseTable.at(i);
		fourItem.type = AssignState;
		fourItem.isLeftArr = fourItem.isTargetArr = false;
		fourItem.target = generateVar(funcName);
		fourItem.op = '-';
		fourItem.left = left;
		char x[15] = { '\0' };
		sprintf(x,"%d",t.constValue);
		fourItem.right = x;
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}// judge - const
		fourItem.type = BEZ;
		fourItem.left = fourItem.target;
		fourItem.target = t.label;
		if (isCache) {
			cache.push_back(fourItem);
		}
		else {
			globalTmpCodeArr.push_back(fourItem);
		}
	}
    //分析是否有缺省
    if(!myLexicalAnalysis.isFinish()){
        symbol = myLexicalAnalysis.getGlobalSymbol();
        if(symbol == DEFAULTSY){
            ZSQX_default(funcName, isCache, cache);
        }
    }
	//最后跳转到endLabel的指令
	fourItem.type = Jump;
	fourItem.target = endLabel;
	if (isCache) {
		cache.push_back(fourItem);
	}
	else {
		globalTmpCodeArr.push_back(fourItem);
	}
	//case部分缓冲中间语句写入
	for (unsigned int i = 0; i < myCache.size(); i++) {
		if (isCache) {
			cache.push_back(myCache.at(i));
		}
		else {
			globalTmpCodeArr.push_back(myCache.at(i));
		}
	}
	//endLabel生成
	fourItem.type = Label;
	fourItem.target = endLabel;
	if (isCache) {
		cache.push_back(fourItem);
	}
	else {
		globalTmpCodeArr.push_back(fourItem);
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
vector<CaseRet> SyntaxAnalysis::ZSQX_situationTable(string funcName,string endLabel,vector<FourYuanItem> & cache){
    //分析情况子语句
	CaseRet ret = ZSQX_situationSonStatement(funcName,endLabel,cache);
	vector<CaseRet> caseTable;
	caseTable.push_back(ret);
	
    while(true){
        if(myLexicalAnalysis.isFinish())
            break;
		CaseRet ret = ZSQX_situationSonStatement(funcName,endLabel,cache);
		if (!ret.recognize) {
			break;
		}
		caseTable.push_back(ret);
    }

    return caseTable;
}

//＜情况子语句＞ ::= case＜常量＞：＜语句＞
CaseRet SyntaxAnalysis::ZSQX_situationSonStatement(string funcName,string endLabel, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	CaseRet ret;
	FourYuanItem fourItem;

	ret.constValue = 0;
	ret.label = generateLabel();
	ret.recognize = false;
    //分析case
    symbol = myLexicalAnalysis.getGlobalSymbol();
    if(!(symbol == CASESY)){
        return ret;
    }

    //分析<常量>--> <整数>|<字符>
    nextSymFlag = myLexicalAnalysis.nextSym();
    if(!nextSymFlag){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const.");
        return ret;
    }
    symbol = myLexicalAnalysis.getGlobalSymbol();
    switch(symbol){
        case INTNUM:
        case ADD:
        case SUB:
            ZSQX_integer();
			ret.constValue = return_integer;
            break;
        case CHAR:
            //补读
			ret.constValue = myLexicalAnalysis.getGlobalChar();
            myLexicalAnalysis.nextSym();
            break;
        default:
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack const.");
            myLexicalAnalysis.skipRead('\n');
            return ret;
            break;
    }

    //分析:
    if(myLexicalAnalysis.isFinish()){
        myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack colon.");
        return ret;
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
        return ret;
    }
	//在语句前生成label
	fourItem.type = Label;
	fourItem.target = ret.label;
	cache.push_back(fourItem);

    ZSQX_statement(funcName, true, cache);
	//生成jump到endLabel的代码
	fourItem.type = Jump;
	fourItem.target = endLabel;
	cache.push_back(fourItem);
	ret.recognize = true;
    return ret;
}

//＜缺省＞ ::= default : ＜语句＞
bool SyntaxAnalysis::ZSQX_default(string funcName, bool isCache, vector<FourYuanItem> & cache){
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
    
    ZSQX_statement(funcName, isCache, cache);
    return true;

}

//＜值参数表＞ ::= ＜表达式＞{,＜表达式＞}
bool SyntaxAnalysis::ZSQX_valueParamTable(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
	SymbolCode symbol;
	ExpRet ret;
	FourYuanItem four;
    
	vector<string> paramTable;
	//分析<表达式>
	ret = ZSQX_expression(funcName, isCache, cache);
	if (ret.isSurable) {
		char x[15] = {'\0'};
		sprintf(x,"%d",ret.type == IntType ? ret.number : ret.character);
		four.type = AssignState;
		four.isLeftArr = four.isTargetArr = false;
		four.target = generateVar(funcName);
		four.op = '+';
		four.right = "0";
		four.left = x;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		paramTable.push_back(four.target);
	}
	else {
		paramTable.push_back(ret.name);
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
            myError.SyntaxAnalysisError(LackComposedPartError,getLineNumber(),"lack expression.");
            break;
        }

		ret = ZSQX_expression(funcName, isCache, cache);
		if (ret.isSurable) {
			char x[15] = { '\0' };
			sprintf(x, "%d", ret.type == IntType ? ret.number : ret.character);
			four.type = AssignState;
			four.isLeftArr = four.isTargetArr = false;
			four.target = generateVar(funcName);
			four.op = '+';
			four.right = "0";
			four.left = x;
			if (isCache) {
				cache.push_back(four);
			}
			else {
				globalTmpCodeArr.push_back(four);
			}
			paramTable.push_back(four.target);
		}
		else {
			paramTable.push_back(ret.name);
		}
    }
	for (unsigned int i = 0; i < paramTable.size(); i++) {
		four.type = ValueParamDeliver;
		four.target = paramTable.at(i);
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
	}

    return true;
}

//＜读语句＞ ::= scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
bool SyntaxAnalysis::ZSQX_readStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	FourYuanItem four;
	int order;
	string id;
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
	
	id = myLexicalAnalysis.getGlobalString();
	order = checkAssignId(id,funcName);
	if (order >= 0) {
		four.type = (globalSymbolTable.at(order).getValueType() == IntType) ? ReadInt : ReadChar;
		char ggg[10] = {'\0'};
		sprintf(ggg,"%d",order);
		four.target = "G" + string(ggg) + id;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
	}//没找到,不管了

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
		
		id = myLexicalAnalysis.getGlobalString();
		order = checkAssignId(id, funcName);
		if (order >= 0) {
			four.type = (globalSymbolTable.at(order).getValueType() == IntType) ? ReadInt : ReadChar;
			char ggg[10] = {'\0'};
			sprintf(ggg,"%d",order);
			four.target = "G" + string(ggg) + id;
			if (isCache) {
				cache.push_back(four);
			}
			else {
				globalTmpCodeArr.push_back(four);
			}
		}//没找到,不管了
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
bool SyntaxAnalysis::ZSQX_writeStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
	FourYuanItem four;

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
		
		string str = myLexicalAnalysis.getGlobalString();//需要原样打印的字符串
		four.type = PrintStr;
		four.target = str;
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}

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
            ExpRet ret = ZSQX_expression(funcName, isCache, cache);
			if (ret.isSurable) {
				four.type = (ret.type == IntType) ? PrintInt : PrintChar;
				char x[15] = {'\0'};
				if (ret.type == IntType)
					sprintf(x, "%d", ret.number);
				else
					x[0] = ret.character;
				four.target = x;
			}
			else {
				four.isNotPrintCharId = (ret.type == CharType) ? false : true;
				four.type = PrintId;
				four.target = ret.name;
			}
			if (isCache) {
				cache.push_back(four);
			}
			else {
				globalTmpCodeArr.push_back(four);
			}
        }
		four.type = PrintChar;
		four.target = "10";
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
    }else{
        //单纯表达式?
		ExpRet ret = ZSQX_expression(funcName, isCache, cache);
		if (ret.isSurable) {
			four.type = (ret.type == IntType) ? PrintInt : PrintChar;
			char x[15] = { '\0' };
			if (ret.type == IntType)
				sprintf(x, "%d", ret.number);
			else
				x[0] = ret.character;
			four.target = x;
		}
		else {
			four.isNotPrintCharId = (ret.type == CharType) ? false : true;
			four.type = PrintId;
			four.target = ret.name;
		}
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
		four.type = PrintChar;
		four.target = "10";
		if (isCache) {
			cache.push_back(four);
		}
		else {
			globalTmpCodeArr.push_back(four);
		}
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
bool SyntaxAnalysis::ZSQX_returnStatement(string funcName, bool isCache, vector<FourYuanItem> & cache){
    bool nextSymFlag;
    SymbolCode symbol;
    bool preRead = true;

	FourYuanItem item;

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
            ExpRet ret = ZSQX_expression(funcName, isCache, cache);
			if (ret.isSurable) {
				if (ret.type == IntType) {
					item.type = ReturnInt;
					char x[15] = {'\0'};
					sprintf(x,"%d",ret.number);
					item.target = x;
					if (isCache) {
						cache.push_back(item);
					}
					else {
						globalTmpCodeArr.push_back(item);
					}
				}
				else {
					item.type = ReturnChar;
					char x[2] = {ret.character,0};
					item.target = x;
					if (isCache) {
						cache.push_back(item);
					}
					else {
						globalTmpCodeArr.push_back(item);
					}
				}
			}
			else {
				item.type = ReturnId;
				item.target = ret.name;
				if (isCache) {
					cache.push_back(item);
				}
				else {
					globalTmpCodeArr.push_back(item);
				}
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
        }else{
			if (funcName == "main")
				item.type = OverProcedure;
			else
				item.type = ReturnEmpty;
			if (isCache) {
				cache.push_back(item);
			}
			else {
				globalTmpCodeArr.push_back(item);
			}
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
		FourYuanItem insert;
		insert.type = TmpCodeType::FunctionDef;
		insert.target = return_declare_funcName;
		insert.funcType = type;
		globalTmpCodeArr.push_back(insert);
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
}
//数组变量
void SyntaxAnalysis::pushItem(string id, string functionName, ValueType valueType, int size) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(Variable);
	newItem.setValueType(valueType);
	newItem.setArrSize(size);
	globalSymbolTable.push_back(newItem);
}
//变量+参数
void SyntaxAnalysis::pushItem(string id, string functionName, ItemType itemType, ValueType valueType) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(itemType);
	newItem.setValueType(valueType);
	globalSymbolTable.push_back(newItem);
}
//函数
void SyntaxAnalysis::pushItem(string id, string functionName, FunctionType funcType) {
	if (!isAbleInsert(id, functionName))
		return;
	SymbolTableItem newItem(id, functionName);
	newItem.setItemType(Function);
	newItem.setFuncType(funcType);
	globalSymbolTable.push_back(newItem);
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

/*检查是否定义(类型是否匹配)
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
}*/
/*＜标识符＞‘[’＜表达式＞‘]’需要检查:标识符存不存在，标识符对应的是不是数组，如果是数组,表达式对应的下标值是否越界*/   
int SyntaxAnalysis::idArrExpCheck(string identifier,string funcName, bool expSurable, int index) {
	bool globalIndexOut = false;//在全局中发现此为数组且但越界
	bool globalNotArray = false;//全局中发现不是数组
	bool isDefined = false;
	int order = -1;
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {//作用域全局
			if (item.getId() == identifier) {//标识符名相同
				isDefined = true;
				if (item.getArrSize() > 0) {//是数组
					if (expSurable) {//数组下标值确定
						if (index >= item.getArrSize() || index <0) {//越界
							globalIndexOut = true;
						}
						else {
							order = item.getOrder();
						}
					}
					else {
						order = item.getOrder();
					}
				}
				else {//不是数组
					globalNotArray = true;
				}
			}
		}
		else if(item.getFuncName() == funcName){//在函数作用域内发现
			if (item.getId() == identifier) {
				isDefined = true;
				if (item.getArrSize() > 0) {
					if (expSurable) {
						if (index >= item.getArrSize() || index <0) {//越界
							myError.SemanticAnalysisError(ArrIndexOutOfRangeError, getLineNumber(), identifier);
							return -1;
						}
						else {
							return item.getOrder();
						}
					}
					else {
						return item.getOrder();
					}
				}
				else {//不是数组
					if (globalIndexOut) {
						break;
					}
					else {
						myError.SemanticAnalysisError(TypeNotMatchError, getLineNumber(), identifier);
						return -1;
					}
				}
			}
		}
	}

	if (globalIndexOut) {
		myError.SemanticAnalysisError(ArrIndexOutOfRangeError, getLineNumber(), identifier);
		return -1;
	}
	if (globalNotArray) {
		myError.SemanticAnalysisError(TypeNotMatchError, getLineNumber(), identifier);
		return -1;
	}
	//标识符未定义
	if (!isDefined) {
		myError.SemanticAnalysisError(NotDefinitionError, getLineNumber(), identifier);
		return -1;
	}
	return order;
}

//标识符检查-->因子中(不可以为数组和void函数)
int SyntaxAnalysis::idCheckInFactor(string identifier, string funcName) {
	bool foundInGlobal = false; // 表示在global中发现此结构存在问题
	bool isDefined = false;
	int orderInGlobal = -1;
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {//全局作用域
			if (item.getId() == identifier) {//标识符名字相同
				isDefined = true;
				if (item.getArrSize() > 0) {//为数组,否决
					foundInGlobal = true;
				}
				else if (item.getItemType() == Function && item.getFuncType() == VOIDSY) {
					foundInGlobal = true;
				}
				else {
					orderInGlobal = item.getOrder();
				}
			}
		}
		else if (item.getFuncName() == funcName) {//作用域相同(局部作用域)
			if (item.getId() == identifier) {
				isDefined = true;
				if (item.getArrSize() > 0) {//为数组,报错
					myError.SemanticAnalysisError(TypeNotMatchError,getLineNumber(),identifier);
					return -1;
				}
				else {//正确的
					return item.getOrder();
				}
			}
		}
	}
	if (foundInGlobal) {
		myError.SemanticAnalysisError(TypeNotMatchError, getLineNumber(), identifier);
		return -1;
	}
	//未定义标识符
	if (!isDefined) {
		myError.SemanticAnalysisError(NotDefinitionError, getLineNumber(), identifier);
		return -1;
	}
	return orderInGlobal;
}

//标识符检查--->语句中(只能是函数)
void SyntaxAnalysis::idCheckInState(string identifier) {
	//由于只能是函数,所以只需要分析全局的即可
	bool isDefined = false;
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {
			if (item.getId() == identifier) {
				isDefined = true;
				if(item.getItemType() == Function)
					return;
			}
		}
	}
	if (!isDefined) {
		myError.SemanticAnalysisError(FuncNotDefineError,getLineNumber(),identifier);
		return;
	}
	myError.SemanticAnalysisError(StateIdNotMatchError,getLineNumber(),identifier);
}

//＜标识符＞‘(’<值参数表>‘)’--->若是因子项中的(表达式中的,需要判断是否是有返回值)
void SyntaxAnalysis::funcCallCheck(string identifier, bool isInExp, vector<ValueType> paramType) {
	bool isDefined = false;
	bool flag = false;//是否需要进行参数检查(不需要说明函数本身存在了问题)
	vector<ValueType> actualParam;

	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {
			if (item.getId() == identifier) {
				isDefined = true;
				if (item.getItemType() == Function) {//是函数
					flag = true;
					if (isInExp && item.getFuncType() == VoidType) {
						myError.SemanticAnalysisError(NeedValueButVoidFuncError,getLineNumber(),identifier);
						return;
					}
					for (unsigned int j = i + 1; j < globalSymbolTable.size(); j++) {
						item = globalSymbolTable.at(j);
						if (item.getFuncName() == identifier && item.getItemType() == Parament) {
							actualParam.push_back(item.getValueType());
						}
						else {
							break;
						}
					}
					break;
				}
			}	
		}
	}
	//进行参数表考察
	if (flag) {
		if (paramType.size() == 0) {
			myError.SemanticAnalysisError(NoneValueParamError,getLineNumber(),identifier);
			return;
		}
		if (actualParam.size() == 0) {//无参函数却传参
			myError.SemanticAnalysisError(NoneParamButDeliverError,getLineNumber(),identifier);
			return;
		}
		if (paramType.size() != actualParam.size()) {//参数个数不匹配
			myError.SemanticAnalysisError(ParamNumNotMatchError,getLineNumber(),identifier);
			return;
		}
		for (unsigned int i = 0; i < paramType.size(); i++) {
			ValueType first = actualParam.at(i);
			ValueType second = paramType.at(i);
			if (first != second) {//参数类型不匹配
				myError.SemanticAnalysisError(ParamTypeNotMatchError,getLineNumber(),identifier);
				return;
			}
		}
	}

	if (!isDefined) {
		myError.SemanticAnalysisError(FuncNotDefineError, getLineNumber(), identifier);
		return;
	}
}

//对赋值语句以及scanf中单纯的标识符的检查(scanf实际就是对变量的赋值操作)
int SyntaxAnalysis::checkAssignId(string identifier, string funcName) {
	bool isDefined = false;
	int order = -1;
	bool global = false;
	for (unsigned int i = 0; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getFuncName() == "GLOBAL") {
			if (item.getId() == identifier) {
				isDefined = true;
				if (item.getItemType() == Variable && item.getArrSize() == 0) {//是全局变量
					order = item.getOrder();
				}
				else {
					global = true;
				}
			}
		}
		else if (item.getFuncName() == funcName) {
			if (item.getId() == identifier) {
				isDefined = true;
				if ((item.getItemType() == Variable && item.getArrSize() == 0)
					|| (item.getItemType() == Parament)) {//是变量或者参数
					return item.getOrder();
				}
				else {
					myError.SemanticAnalysisError(AssignObjectNotVar, getLineNumber(), identifier);
					return -1;
				}
			}
		}
	}
	if (!isDefined) {
		myError.SemanticAnalysisError(NotDefinitionError,getLineNumber(),identifier);
		return -1;
	}
	else if(global){
		myError.SemanticAnalysisError(AssignObjectNotVar,getLineNumber(),identifier);
		return -1;
	}
	return order;
}

//检查switch的case语句是否出现相同的值
void SyntaxAnalysis::checkCase(vector<int> cases) {
	if (cases.size() == 0)
		return;
	sort(cases.begin(),cases.end());
	int prev = cases.at(0);
	for (unsigned int i = 1; i < cases.size(); i++) {
		int x = cases.at(i);
		if (x == prev) {
			myError.SemanticAnalysisError(CaseSameValueError,getLineNumber(),"");
			return;
		}
		prev = x;
	}
}