/*
** @author:止水清潇menghuanlater
** @date:2017-11-22
** @location:BUAA
*/
#ifndef SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H
#define _CRT_SECURE_NO_WARNINGS
#include "LexicalAnalysis.h"
#include "error.h"
#include "ConstValue.h"
#include "SymbolTable.h"
#include "globalFunction.h"
#include <algorithm>
using namespace std;

extern vector<SymbolTableItem> globalSymbolTable; //使用全局的符号表
extern vector<FourYuanItem> globalTmpCodeArr;//使用全局中间代码表

//函数存在多返回值的结构体设计
//表达式返回值
struct ExpRet {
	string name;//表达式返回的名字--->统一规定,表达式都需要有一个返回变量名(临时变量)
	bool isSurable;//是否确定
	ValueType type;//值类型
	int number;
	char character;
	bool isEmpty;//是否是空的
};
//情况子语句返回
struct CaseRet {
	int constValue;
	bool recognize;
	string label;
};

class SyntaxAnalysis
{
private:
    Error & myError;//公用错误处理
    LexicalAnalysis & myLexicalAnalysis;//公用词法分析
    bool isMainVoid; //main函数分析的前缀是否是void
	//相关递归下降子程序需要返回的值
	int return_integer;//ZSQX_integer()需要返回的识别的整数值
	string return_declare_funcName;
	SymbolCode relation;//关系运算符
	vector<FourYuanItem> noUseCache;//无用的cache
	bool haveReturn;//有参函数是否有有效的return语句(必须有效)
	//
    int getLineNumber(){//获取词法分析当前行
        return myLexicalAnalysis.getLineCount();
    }
	//下面是填符号表,查符号表语义分析相关的操作函数
	//填符号表函数,采用函数重载
	void pushItem(string id, string functionName, int num);//常量 整数
	void pushItem(string id, string functionName, char character);//常量 char
	void pushItem(string id, string functionName, ValueType valueType, int size);//变量 数组
	void pushItem(string id, string functionName, FunctionType funcType);//函数
	void pushItem(string id, string functionName, ItemType itemType, ValueType valueType);//变量与参数
	//检查是否可以填表
	bool isAbleInsert(string id, string functionName);
	//引用变量函数等需要检查是否定义
	//bool isDefined(string id, string functionName);
	//标识符检查--->因子项中
	int idCheckInFactor(string identifier,string funcName);
	//标识符检查--->语句中
	void idCheckInState(string identifier);
	//＜标识符＞‘[’＜表达式＞‘]’检查--->因子项与赋值语句中
	int idArrExpCheck(string identifier,string funcName,bool expSurable,int index = 0);
	//＜标识符＞‘(’<值参数表>‘)’--->若是因子项中的(表达式中的,需要判断是否是有返回值)
	void funcCallCheck(string identifier,bool isInExp,vector<ValueType> paramType);
	//类型检查
	void checkTypeMatch(ValueType s_type, ValueType e_type) {
		if (s_type == CharType && e_type == IntType) {
			myError.SemanticAnalysisError(AssignIntToCharError,getLineNumber(),"");
		}
	}
	//对赋值语句单纯的标识符的检查
	int checkAssignId(string identifier,string funcName);
	//检查switch的case语句是否出现相同的值
	void checkCase(vector<int> cases);
	void checkSwitchType(ValueType s_type, ValueType e_type) {
		if (s_type != e_type) {
			myError.SemanticAnalysisError(CaseTypeNotMatchError,getLineNumber(),"");
		}
	}

	//返回语句检查
	void checkReturn(string funcName);//无返回值的return
	void checkReturn(string funcName,ValueType retType);

public:
    //标准构造函数
    SyntaxAnalysis(Error & myError,LexicalAnalysis & myAnalysis);
    //程序入口函数
    void startAnalysis();
    //下面是所有的递归下降子程序法定义的分析过程
    //＜程序＞ ::= ［＜常量说明＞］［＜变量说明＞］[<函数定义部分>]   ＜主函数＞
    bool ZSQX_procedure();
    //＜常量说明＞ ::= const＜常量定义＞;{ const＜常量定义＞;}
    bool ZSQX_constDescription(string funcName);
    /*＜常量定义＞ ::= int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
        | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞} */
    bool ZSQX_constDefinition(string funcName);
    //＜变量说明＞ ::= ＜变量定义＞;{＜变量定义＞;}
    bool ZSQX_varDescription(bool isGlobal, string funcName);
    /*＜变量定义＞ ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’)
            {,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’ )}*/
    bool ZSQX_varDefinition(string funcName);
    //<函数定义部分> ::= {＜有返回值函数定义＞|＜无返回值函数定义＞}
    bool ZSQX_functionDefinition();
    /*＜有返回值函数定义＞ ::= ＜声明头部＞‘(’＜参数表＞‘)’ ‘{’＜复合语句＞‘}’|＜声明头部＞‘{’＜复合语句＞‘}’*/
    bool ZSQX_haveReturnValueFunctionDefinition();
    //＜无返回值函数定义＞ ::= bool＜标识符＞(’＜参数表＞‘)’‘{’＜复合语句＞‘}’| bool＜标识符＞{’＜复合语句＞‘}’
    bool ZSQX_noReturnValueFunctionDefinition();
    //＜参数表＞ ::= ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}
    bool ZSQX_paramTable(string funcName);
    //＜复合语句＞ ::= ［＜常量说明＞］［＜变量说明＞］｛＜语句＞｝
    bool ZSQX_compoundStatement(string funcName);
    //＜表达式＞ ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
    ExpRet ZSQX_expression(string funcName,bool isCache,vector<FourYuanItem> & cache);
    //＜项＞ ::= ＜因子＞{＜乘法运算符＞＜因子＞}
    bool ZSQX_item(vector<PostfixItem> &, string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜因子＞ ::= ＜标识符＞[‘(’<值参数表>‘)’]｜＜标识符＞‘[’＜表达式＞‘]’|‘(’＜表达式＞‘)’｜＜整数＞|＜字符＞
    bool ZSQX_factor(vector<PostfixItem> &, string funcName, bool isCache, vector<FourYuanItem> & cache);
    /*＜语句＞ ::= ＜条件语句＞｜＜循环语句＞| ‘{’｛＜语句＞｝‘}’｜＜标识符＞[‘(’<值参数表>‘)’]; 
        ｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;|＜情况语句＞｜＜返回语句＞;*/
    bool ZSQX_statement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜赋值语句＞ ::= ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
    bool ZSQX_assignStatement(string funcName,string, bool isCache, vector<FourYuanItem> & cache);
    //＜条件语句＞::= if ‘(’＜条件＞‘)’＜语句＞else＜语句＞
    bool ZSQX_conditionStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜条件＞ ::= ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ 
    string ZSQX_condition(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜循环语句＞ ::= while ‘(’＜条件＞‘)’＜语句＞
    bool ZSQX_loopStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜情况语句＞ ::= switch ‘(’＜表达式＞‘)’ ‘{’＜情况表＞[＜缺省＞] ‘}’
    bool ZSQX_situationStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜情况表＞ ::= ＜情况子语句＞{＜情况子语句＞}
    vector<CaseRet> ZSQX_situationTable(string funcName,string endLabel,ValueType type,vector<FourYuanItem> &);
    //＜情况子语句＞ ::= case＜常量＞：＜语句＞
    CaseRet ZSQX_situationSonStatement(string funcName,string endLabel, ValueType type,vector<FourYuanItem> &);
    //＜缺省＞ ::= default : ＜语句＞
    bool ZSQX_default(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜值参数表＞ ::= ＜表达式＞{,＜表达式＞}
    vector<ValueType> ZSQX_valueParamTable(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜读语句＞ ::= scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
    bool ZSQX_readStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜写语句＞ ::= printf ‘(’ ＜字符串＞,＜表达式＞ ‘)’| printf ‘(’＜字符串＞ ‘)’| printf ‘(’＜表达式＞‘)’
    bool ZSQX_writeStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜返回语句＞ ::= return[‘(’＜表达式＞‘)’]
    bool ZSQX_returnStatement(string funcName, bool isCache, vector<FourYuanItem> & cache);
    //＜整数＞ ::= ［＋｜－］＜无符号整数＞｜0
    bool ZSQX_integer();
    //＜声明头部＞ ::= int ＜标识符＞ |char ＜标识符＞
    bool ZSQX_declareHead();

};

#endif