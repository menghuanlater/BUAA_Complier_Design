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

	unsigned int address;

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
	unsigned int getAddress() {
		return address;
	}
	//set
	void setAddress(unsigned int addr) {
		address = addr;
	}
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
};

#endif