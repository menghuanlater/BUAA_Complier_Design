/*
** @author:止水清潇menghuanlater
** @date:2018-1-12
** @location:BUAA
** @func:优化定义头文件
*/
#ifndef OPTIMIZE_H
#define OPTIMIZE_H
#define _CRT_SECURE_NO_WARNINGS
#include "ConstValue.h"
#include "globalFunction.h"
#include "SymbolTable.h"
#include <vector>
#include <map>

using namespace std;

//块的类型
enum BlockType {
	FuncBlock,
	DAGBlock,
	CallBlock,
	ReadBlock,
	WriteBlock,
	RetBlock,
	LabelBlock,
	BranchBlock,
	ArrayBlock
};

//定义优化需要的相关结构体
struct Block {
	int index;//开始的索引
	BlockType type;//基本块类型
};

//节点表
struct NodeTable {
	map<string, int> table;
	map<int, vector<string>> final;//对应中间节点,最终选择的
};

//DAG图中的每个节点
struct DAGNode {
	int code;
	int left;
	int right;
	char op;//+ - * / = [ 
	string value;//针对叶子结点
	//记录其所有的父节点
	vector<int> parent;
	//针对叶节点引用不在结点表中的变量(只针对变量)
	string target;//当中间节点啥都没有了的时候,保存最新的
	bool isInitial;
	bool isLeftLeaf;
	bool isRightLeaf;
};

//唯一的暴露给外部的函数
void toDoOptimize();

#endif