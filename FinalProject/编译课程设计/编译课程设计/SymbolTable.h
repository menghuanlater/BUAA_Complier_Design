/*
** @author:止水清潇menghuanlater
** @date:2017-12-04
** @location:BUAA
*/
//符号表类
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "ConstValue.h"
#include <string>
#include <vector>

using namespace std;
//全局作用域名统一规定为GLOBAL
class SymbolTableItem
{
private:
	
	static int numberCount;

	string identifier;//标识符
	int order; // 符号表所在的项号,从0开始
    string functionName;//符号表所属函数作用域
    ItemType itemType;//符号表项类型
	ValueType valueType;//值类型
	FunctionType functionType;//函数类型

	int constIntValue;//常量整数
	char constCharValue;//字符常量

	int length;//数组的长度,变量设置为0

	int weight;//只针对函数内部的简单变量以及参数有效

public:
	SymbolTableItem(string id,string funcName);
	int getOrder() {
		return order;
	}
	string getId() {
		return identifier;
	}
	string getFuncName() {
		return functionName;
	}
	ItemType getItemType() {
		return itemType;
	}
	ValueType getValueType() {
		return valueType;
	}
	FunctionType getFuncType() {
		return functionType;
	}
	int getArrSize() {
		return length;
	}
	int getConstInt() {
		return constIntValue;
	}
	char getConstChar() {
		return constCharValue;
	}
	//set
	void setItemType(ItemType type) {
		itemType = type;
	}
	void setValueType(ValueType type) {
		valueType = type;
	}
	void setArrSize(int size) {
		length = size;
	}
	void setConstInt(int value) {
		constIntValue = value;
	}
	void setConstChar(char value) {
		constCharValue = value;
	}
	void setFuncType(FunctionType type) {
		functionType = type;
	}
	void addWeight(int num) {
		weight += num;
	}
	int getWeight() {
		return weight;
	}
};

#endif