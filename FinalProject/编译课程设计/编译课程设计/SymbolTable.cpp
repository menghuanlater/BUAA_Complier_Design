/*
** @author:止水清潇menghuanlater
** @date:2017-12-04
** @location:BUAA
*/
#include "SymbolTable.h"
#include <vector>

using namespace std;

int SymbolTableItem::numberCount = 0;

//全局符号表
vector<SymbolTableItem> globalSymbolTable;

SymbolTableItem::SymbolTableItem(string id,string funcName){
	order = numberCount++;
	functionName = funcName;
	identifier = id;
	length = 0;//默认为0
}