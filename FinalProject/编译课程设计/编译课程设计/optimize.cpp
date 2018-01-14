/*
** @author:止水清潇menghuanlater
** @date:2018-1-12
** @location:BUAA
** @func:优化函数
*/
#include <iostream>
#include <string>
#include "optimize.h"
#include <map>
#include <algorithm>

using namespace std;

extern vector<FourYuanItem> globalTmpCodeArr;
extern vector<SymbolTableItem> globalSymbolTable;
extern map<string, unsigned> maxTempOrderMap;

map<string, vector<int>> functionVarIndexMap;
map<string, string> varToRegisterMap;

vector<string> funcNameTable;//函数名表
//删除公共子表达式后的四元式表
vector<FourYuanItem> optimizeTmpCodeArr;
//原四元式的基本块划分
map<string, vector<Block>> initBlockDivision;

string intToStr(int number) {
	char x[10] = { '\0' };
	sprintf_s(x,"%d",number);
	return string(x);
}
/*划分基本块函数
 *mode为true,表示对原始的进行划分,false对优化的进行
*/
void divideBlock() {
	map<string, vector<Block>> & objMap = initBlockDivision;
	vector<FourYuanItem> objVector = globalTmpCodeArr;
	/*
	划分规则:
	1.所有函数的第一条语句为开始语句
	2.所有跳转语句的下一条语句为开始语句
	3.所有的跳转语句的目标语句是开始语句
	4.scanf语句,print语句，返回语句，整体的函数调用均单独分块
	*/
	//遍历整个四元式数组
	string funcName = "GLOBAL";
	map<string, vector<Block>>::iterator iter;
	/*
	标志flag,用于划分基本块
	*/
	bool callFlag = false;
	bool expFlag = false;//连续的表达式块
	for (unsigned int i = 0; i < objVector.size(); i++) {
		FourYuanItem item = objVector.at(i);
		switch (item.type) {
		case FunctionDef: {
			expFlag = false;
			funcName = item.target;
			vector<Block> t;
			Block x; x.index = i; x.type = FuncBlock;
			t.push_back(x);
			objMap.insert(map<string, vector<Block>>::value_type(funcName, t));
			iter = objMap.find(funcName);
			funcNameTable.push_back(funcName);
			break;
		}
		case ValueParamDeliver: {
			expFlag = false;
			if (callFlag)
				break;
			callFlag = true;
			Block x; x.index = i; x.type = CallBlock;
			iter->second.push_back(x);
			break;
		}
		case AssignState: {
			//如果是获取返回值的ret型,则不用管,否则去新建一个块
			if (item.isTargetArr) {
				expFlag = false;
				Block x; x.index = i; x.type = ArrayBlock;
				iter->second.push_back(x);
				break;
			}
			if (item.left == "Ret") {
				break;
			}
			if (!expFlag) {
				expFlag = true;
				Block x; x.index = i; x.type = DAGBlock;
				iter->second.push_back(x);
			}
			break;
		}
		case Label: {
			expFlag = false;
			Block x;
			x.index = i;
			x.type = LabelBlock;
			iter->second.push_back(x);
			break;
		}
		case FunctionCall: {
			//将callFlag设置为false
			if (callFlag) {
				callFlag = false;
			}
			else {
				Block x; x.index = i; x.type = CallBlock;
				iter->second.push_back(x);
			}
			break;
		}
		case Jump:
		case BEZ:
		case BNZ:
		case BLZ:
		case BLEZ:
		case BGZ:
		case BGEZ: {
			expFlag = false;
			Block x; x.index = i; x.type = BranchBlock;
			iter->second.push_back(x);
			break;
		}
		case ReadChar:
		case ReadInt: {
			expFlag = false;
			Block x; x.index = i; x.type = ReadBlock;
			iter->second.push_back(x);
			break;
		}
		case PrintChar:
		case PrintStr:
		case PrintInt:
		case PrintId: {
			expFlag = false;
			Block x; x.index = i; x.type = WriteBlock;
			iter->second.push_back(x);
			break;
		}
		case ReturnChar:
		case ReturnEmpty:
		case ReturnInt:
		case ReturnId: {
			expFlag = false;
			Block x; x.index = i; x.type = RetBlock;
			iter->second.push_back(x);
			break;
		}
		}
	}

}

bool isIn(vector<int> &obj,int target) {
	for (unsigned int i = 0; i < obj.size(); i++) {
		if (target == obj.at(i))
			return true;
	}
	return false;
}

void doFillCalSequ(vector<int> & calSequ,vector<DAGNode> & myDAG,vector<int>& interNodes,int code) {
	//检查code是否加入队列
	if (isIn(calSequ, code))
		return;
	//检查该节点的所有父节点是否全部在calSequ里面
	bool flag = true;
	for (unsigned int j = 0; j < myDAG.at(code).parent.size(); j++) {
		if (!isIn(calSequ, myDAG.at(code).parent.at(j))) {
			flag = false;
			break;
		}
	}
	if (!flag)
		return;
	//将该节点加入队列
	calSequ.push_back(code);
	//下面检查该节点的左右子节点(都要检查)
	DAGNode node = myDAG.at(code);
	DAGNode left = myDAG.at(node.left);
	DAGNode right = myDAG.at(node.right);
	if (!node.isLeftLeaf) {
		if (isIn(interNodes, left.code))
			doFillCalSequ(calSequ,myDAG,interNodes,left.code);
	}
	if (!node.isRightLeaf) {
		if (isIn(interNodes, right.code))
			doFillCalSequ(calSequ,myDAG,interNodes,right.code);
	}
}

//搜索DAG图
int searchDAG(vector<DAGNode> & myDAG,int v1,int v2,char op) {
	for (unsigned int i = 0; i < myDAG.size(); i++) {
		DAGNode node = myDAG.at(i);
		if (node.isLeftLeaf && node.isRightLeaf)
			continue;
		if (!((myDAG.at(node.left).code == v1 && myDAG.at(node.right).code == v2) || 
			(myDAG.at(node.left).code == v2 && myDAG.at(node.right).code == v1 && (op == '+' || op == '*'))))
			continue;
		if (node.op == op)
			return i;
	}
	return myDAG.size();
}

//删除公共子表达式
void deletePubExp(int startIndex,int loopEnd,string funcName) {
	NodeTable myTable;
	vector<DAGNode> myDAG;
	vector<FourYuanItem> cache;
	//Step1:建立DAG图以及结点表
	for (unsigned int i = startIndex; i < (unsigned)loopEnd; i++) {
		FourYuanItem item = globalTmpCodeArr.at(i);
		if (item.type == AssignState) {
			//如果实Ret
			int v1, v2, v3;
			map<string, int>::iterator iter;
			//复杂在数组问题
			//检查左节点,如果左节点是数组
			if (item.isLeftArr) {
				iter = myTable.table.find(item.left);
				if (iter == myTable.table.end()) {
					DAGNode newNode1;
					v1 = myDAG.size();
					newNode1.code = v1;
					newNode1.isLeftLeaf = newNode1.isRightLeaf = true;
					newNode1.value = item.left;
					newNode1.isInitial = false;
					myDAG.push_back(newNode1);
					myTable.table.insert(map<string,int>::value_type(item.left,v1));
				}
				else {
					v1 = iter->second;
				}
				//寻找v2
				iter = myTable.table.find(item.index2);
				if (iter == myTable.table.end()) {
					DAGNode newNode2;
					v2 = myDAG.size();
					newNode2.code = v2;
					newNode2.isLeftLeaf = newNode2.isRightLeaf = true;
					newNode2.value = item.index2;
					if (item.index2.at(0) == 'G')
						newNode2.isInitial = true;
					else
						newNode2.isInitial = false;
					myDAG.push_back(newNode2);
					myTable.table.insert(map<string,int>::value_type(item.index2,v2));
				}
				else {
					v2 = iter->second;
				}
				//针对target,查询DAG图
				v3 = searchDAG(myDAG,v1,v2,'[');
				if (v3 == myDAG.size()) {
					DAGNode newNode3;
					newNode3.code = v3;
					newNode3.op = '[';
					newNode3.left = v1;
					newNode3.right = v2;
					newNode3.isLeftLeaf = newNode3.isRightLeaf = false;
					newNode3.isInitial = false;
					newNode3.target = item.target;
					myDAG.at(v1).parent.push_back(v3);
					myDAG.at(v2).parent.push_back(v3);
					myDAG.push_back(newNode3);
				}
				else {
					myDAG.at(v3).target = item.target;
				}
				iter = myTable.table.find(item.target);
				if (iter == myTable.table.end()) {
					myTable.table.insert(map<string,int>::value_type(item.target,v3));
				}
				else {
					iter->second = v3;
				}
			}
			else {
				iter = myTable.table.find(item.left);
				if (iter == myTable.table.end()) {
					v1 = myDAG.size();
					DAGNode newNode1;
					newNode1.code = v1;
					newNode1.isLeftLeaf = newNode1.isRightLeaf = true;
					newNode1.value = item.left;
					if (item.left.at(0) == 'G')
						newNode1.isInitial = true;
					else
						newNode1.isInitial = false;
					myDAG.push_back(newNode1);
					myTable.table.insert(map<string, int>::value_type(item.left, v1));
				}
				else {
					v1 = iter->second;
				}
				iter = myTable.table.find(item.right);
				if (iter == myTable.table.end()) {
					v2 = myDAG.size();
					DAGNode newNode2;
					newNode2.code = v2;
					newNode2.isLeftLeaf = newNode2.isRightLeaf = true;
					newNode2.value = item.right;
					if (item.right.at(0) == 'G')
						newNode2.isInitial = true;
					else
						newNode2.isInitial = false;
					myDAG.push_back(newNode2);
					myTable.table.insert(map<string, int>::value_type(item.right, v2));
				}
				else {
					v2 = iter->second;
				}
				v3 = searchDAG(myDAG,v1,v2,item.op);
				if (v3 == myDAG.size()) {
					DAGNode newNode3;
					newNode3.code = v3;
					newNode3.op = item.op;
					newNode3.left = v1;
					newNode3.right = v2;
					newNode3.isInitial = false;
					newNode3.isLeftLeaf = newNode3.isRightLeaf = false;
					newNode3.target = item.target;
					myDAG.push_back(newNode3);
					myDAG.at(v1).parent.push_back(v3);
					myDAG.at(v2).parent.push_back(v3);
				}
				else {
					myDAG.at(v3).target = item.target;
				}
				iter = myTable.table.find(item.target);
				if (iter == myTable.table.end()) {
					myTable.table.insert(map<string, int>::value_type(item.target, v3));
				}
				else {
					iter->second = v3;
				}
			}
		}
	}
	//Step2:遍历DAG图生成逆序的计算顺序
	/*Step2.1:遍历所有可能需要保存初始值的变量,观察它们所对应的变量在节点表中的位置是否发生变化,
	* 如果未发生变化,则不需要先生成保存的四元式代码
	*/
	//Step2.2:找出所有的中间节点
	vector<int> interNodes;
	map<string, unsigned>::iterator itr = maxTempOrderMap.find(funcName);
	int tmpCount = itr->second+1;//保存的临时变量从当前函数最大临时变量计数器加一开始
	for (unsigned int i = 0; i < myDAG.size(); i++) {
		DAGNode node = myDAG.at(i);
		if (node.isLeftLeaf && node.isRightLeaf && node.isInitial) {//叶子结点
			map<string, int>::iterator iter = myTable.table.find(node.value);
			if (iter->second != node.code) {//需要保存
				FourYuanItem fourItem;
				fourItem.isTargetArr = fourItem.isLeftArr = false;
				fourItem.type = AssignState;
				fourItem.target = "T" + intToStr(tmpCount++);
				fourItem.left = node.value;
				fourItem.right = "0";
				fourItem.op = '+';
				cache.push_back(fourItem);
				myDAG.at(i).value = fourItem.target;
			}
		}
		if (!node.isLeftLeaf && !node.isRightLeaf)
			interNodes.push_back(node.code);
	}
	//检查中间节点数，如果是跟优化前一样的化,不优化
	if ((loopEnd - startIndex) == interNodes.size()) {
		for (unsigned int p = startIndex; p < loopEnd; p++) {
			optimizeTmpCodeArr.push_back(globalTmpCodeArr.at(p));
		}
		return;
	}
	else {
		for (unsigned int p = 0; p < cache.size(); p++) {
			optimizeTmpCodeArr.push_back(cache.at(p));
		}
	}
	
	//Step2.3:针对所有的中间节点,访问节点表,找出最终选择生成的变量名(变量/临时,变量必生成)
	for (unsigned int i = 0; i < interNodes.size(); i++) {
		vector<string> vars;
		bool isVarIn = false;
		map<string, int>::iterator iter = myTable.table.begin();
		while (iter != myTable.table.end()) {
			if (iter->second == interNodes.at(i)) {
				if (iter->first.at(0) == 'G')
					isVarIn = true;
				vars.push_back(iter->first);
			}
			iter++;
		}
		if (isVarIn) {//删除所有的临时变量
			for (unsigned int j = 0; j < vars.size(); j++) {
				if (vars.at(j).at(0) == 'T') {
					vars.erase(vars.begin() + j);
					j--;//弥补删除
				}
			}
		}
		else {
			if (vars.size() > 1) {
				vars.erase(vars.begin() + 1, vars.end());
			}
			else if (vars.size() == 0)
				vars.push_back(myDAG.at(interNodes.at(i)).target);
		}
		//将DAG中对应节点的value设置为vars的第一个
		myDAG.at(interNodes.at(i)).value = vars.at(0);
		//加入final
		myTable.final.insert(map<int,vector<string>>::value_type(interNodes.at(i),vars));
	}
	//Step2.4:遍历所有的中间节点,生成实质逆序的计算顺序
	vector<int> calSequ;
	while (calSequ.size() != interNodes.size()) {//只要不等于,就继续扫描
		for (unsigned int i = 0; i < interNodes.size();i++) {
			int code = interNodes.at(i);
			doFillCalSequ(calSequ,myDAG,interNodes,code);
		}
	}
	//Step3:逆转计算序列
	reverse(calSequ.begin(),calSequ.end());
	//Step4:生成新的四元式
	FourYuanItem four;
	for (unsigned int i = 0; i < calSequ.size(); i++) {
		int code = calSequ.at(i);
		map<int, vector<string>>::iterator iter = myTable.final.find(code);
		vector<string> myVars; myVars.assign(iter->second.begin(),iter->second.end());
		DAGNode curr = myDAG.at(code);
		DAGNode left = myDAG.at(curr.left);
		DAGNode right = myDAG.at(curr.right);
		char op = myDAG.at(code).op;
		
		four.type = AssignState;
		switch (op) {
		case '+':
		case '-':
		case '*':
		case '/':
			four.target = curr.value;
			four.isTargetArr = four.isLeftArr = false;
			four.left = left.value;
			four.right = right.value;
			four.op = op;
			optimizeTmpCodeArr.push_back(four);
			break;
		case '[':
			four.target = curr.value;
			four.isTargetArr = false;
			four.isLeftArr = true;
			four.left = left.value;
			four.index2 = right.value;
			optimizeTmpCodeArr.push_back(four);
			break;
		}
	}
}

//生成新的四元式集合
void generateNewTmpCode() {
	for (unsigned int i = 0; i < funcNameTable.size(); i++) {
		string funcName = funcNameTable.at(i);
		map<string, vector<Block>>::iterator iter = initBlockDivision.find(funcName);
		vector<Block> obj = iter->second;
		for (unsigned int j = 0; j < obj.size(); j++) {
			Block block = obj.at(j);
			if (block.type == DAGBlock) {
				int end;
				if (j + 1 == obj.size()) {
					for (unsigned k = block.index;; k++) {
						FourYuanItem item;
						if (k != block.index) {
							if (k == globalTmpCodeArr.size()) {
								end = k;
								break;
							}
							else {
								item = globalTmpCodeArr.at(k);
								if (item.type == FunctionDef) {
									end = k;
									break;
								}
							}
						}
					}
				}
				else {
					end = obj.at(j + 1).index;
				}
				deletePubExp(block.index,end,funcName);
			}
			else {
				//全部原样写入
				unsigned begin = block.index;
				unsigned end;
				if (j + 1 == obj.size()) {
					for (unsigned int k = begin;; k++) {
						FourYuanItem item;
						if (k != begin) {//防止是空函数
							if (k == globalTmpCodeArr.size()) {//跑到文件结尾
								break;
							}
							else {
								item = globalTmpCodeArr.at(k);
								if (item.type == FunctionDef) {
									break;
								}
							}
						}
						optimizeTmpCodeArr.push_back(globalTmpCodeArr.at(k));
					}
				}
				else {
					end = obj.at(j + 1).index;
					for (unsigned int k = begin; k < end; k++) {
						optimizeTmpCodeArr.push_back(globalTmpCodeArr.at(k));
					}
				}
			}
		}
	}
}

void allocateRegister() {
	string funcName = "GLOBAL";
	unsigned int i = 0;
	//先读完所有的global
	for (; i < globalSymbolTable.size(); i++) {
		if (globalSymbolTable.at(i).getItemType() != Function)
			continue;
		else
			break;
	}
	for (; i < globalSymbolTable.size(); i++) {
		SymbolTableItem item = globalSymbolTable.at(i);
		if (item.getItemType() == Function) {
			funcName = item.getId();
			vector<int>x;
			functionVarIndexMap.insert(map < string, vector<int>>::value_type(funcName,x));
		}
		else if ((item.getItemType() == Parament) || (item.getItemType() == Variable 
			&& item.getArrSize() == 0)) {
			map<string, vector<int>>::iterator iter = functionVarIndexMap.find(funcName);
			iter->second.push_back(i);
		}
	}
	//遍历函数集
	for (unsigned int j = 0; j < funcNameTable.size(); j++) {
		map<string, vector<int>>::iterator iter = functionVarIndexMap.find(funcNameTable.at(j));
		//排序
		if (iter->second.size() == 0)//无需排序,过
			continue;
		if (iter->second.size() == 1) {
			varToRegisterMap.insert(map<string, string>::value_type(
				"G" + intToStr(iter->second.at(0)) + globalSymbolTable.at(iter->second.at(0)).getId(),
				"$s" + intToStr(0)));
		}
		for (unsigned int k = 0; k < iter->second.size()-1; k++) {
			for (unsigned int l = k + 1; l < iter->second.size(); l++) {
				int w1 = globalSymbolTable.at(iter->second.at(k)).getWeight();
				int w2 = globalSymbolTable.at(iter->second.at(l)).getWeight();
				if (w1 < w2) {
					int t = iter->second.at(k);
					iter->second.at(k) = iter->second.at(l);
					iter->second.at(l) = t;
				}
			}
		}
		//排序完成
		//依据排序好的map,为全局的变量分配寄存器
		for (unsigned int k = 0; k < iter->second.size() && k<8; k++) {
			varToRegisterMap.insert(map<string,string>::value_type(
			"G"+intToStr(iter->second.at(k))+globalSymbolTable.at(iter->second.at(k)).getId(),
				"$s"+intToStr(k)));
		}
	}
}

//暴露给外部的优化启动函数
void toDoOptimize() {
	//基于原始的四元式数组,划分基本块
	divideBlock();
	//基于DAG图的新四元式集合生成
	generateNewTmpCode();
	//遍历整个符号表,为每个函数的参与临时寄存器分配的变量分配寄存器$s0~$s7
	allocateRegister();
}

