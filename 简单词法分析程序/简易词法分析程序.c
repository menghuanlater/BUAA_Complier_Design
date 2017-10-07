#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 4096 //设置输入字符串长度最大为4096
#define MAX_WORD 66 //设置最大单词长度
#define REMAIN 36 //设置保留字的个数
//枚举类型,设置所有的类别编码
enum Sym {
	NOTHING,
	PROGRAM, FUNCTION, PROCEDURE, ARRAY, CONST,
	_FILE, LABLE, PACKED, VAR, RECORD,
	SET, TYPE, OF, CASE, DO,
	DOWNTO, ELSE, FOR, GOTO, IF,
	REPEAT, THEN, TO, UNNTIL, WHILE,
	WITH, FORWARD, AND, NOT, OR,
	IN, DIV, MOD, BEGIN, END,
	NIL, ID, INT, ADD, MINUS,
	STAR, DIVI, LPAR, RPAR, COMMA,
	SEMI, COLON, ASSIGN, EQUAL
};

const char * remainSym[REMAIN] = {
	"program","function","procedure","array","const",
	"file"   ,"lable"   ,"packed"   ,"var"  ,"record",
	"set"    ,"type"    ,"of"       ,"case" ,"do",
	"downto" ,"else"    ,"for"      ,"goto" ,"if",
	"repeat" ,"then"    ,"to"       ,"until","while",
	"with"   ,"forward" ,"and"      ,"not"  ,"or",
	"in"     ,"div"     ,"mod"      ,"begin","end","nil"
};
char g_char; //字符型全局变量
char g_token[MAX_WORD];//字符数组
int  g_num;//读入的整型数值
enum Sym g_symbol;//当前识别的单词类型
char coding[MAX];//输入的源代码
int index;//coding数组的游标

		  /*functions*/
void getSym(); //识别组合单词符号
void initial();//初始化全局变量,作为每一次调用getSym的先行函数
int reserve();//查找是否保留字
void error() {//程序分析出错处理-->代表源程序词法不合法
	printf("抱歉,词法分析发现存在不合法内容,程序终止\n");
	exit(EXIT_SUCCESS);
}
char getNextChar() {//获取一个char
	return coding[index++];
}
void retract() {//回退
	index--;
}
/*functions*/

int main(void) {
	printf("Hello,欢迎使用简易词法分析程序,请输入你所要分析的源代码(输入终止符表示结束ctrl-D/ctrl-Z)\n");
	int ch;
	while ((ch = getchar()) != EOF) {
		coding[index++] = ch;
	}
	index = 0;
	while (getNextChar() != '\0') {
		retract();
		getSym();
		if (g_symbol == NOTHING)
			continue;
		else if (g_symbol > NOTHING && g_symbol <= NIL)
			printf("识别出保留字:%s\n", remainSym[g_symbol - 1]);
		else if (g_symbol == ID)
			printf("识别出标识符:%s\n", g_token);
		else if (g_symbol == INT)
			printf("识别出整常数:%d\n", g_num);
		else if (g_symbol == ADD)
			printf("识别出+\n");
		else if (g_symbol == MINUS)
			printf("识别出-\n");
		else if (g_symbol == STAR)
			printf("识别出*\n");
		else if (g_symbol == DIVI)
			printf("识别出/\n");
		else if (g_symbol == LPAR)
			printf("识别出(\n");
		else if (g_symbol == RPAR)
			printf("识别出)\n");
		else if (g_symbol == COMMA)
			printf("识别出,\n");
		else if (g_symbol == SEMI)
			printf("识别出;\n");
		else if (g_symbol == COLON)
			printf("识别出:\n");
		else if (g_symbol == ASSIGN)
			printf("识别出赋值符号:=\n");
		else if (g_symbol == EQUAL)
			printf("识别出相等符号=\n");
	}
	printf("分析结束,谢谢使用\n");
	return 0;
}

void getSym() {
	initial(); //初始化
	g_char = getNextChar();
	while (isspace(g_char))
		g_char = getNextChar();
	if (isalpha(g_char)) {
		while (isalnum(g_char)) {
			strcat(g_token, &g_char);
			g_char = getNextChar();
		}
		retract();
		int resultValue = reserve();

		if (resultValue == 0) g_symbol = ID;
		else g_symbol = resultValue;
	}
	else if (isdigit(g_char)) {
		while (isdigit(g_char)) {
			strcat(g_token, &g_char);
			g_char = getNextChar();
		}
		retract();
		g_num = atoi(g_token);
		g_symbol = INT;
	}
	else if (g_char == ':') {
		g_char = getNextChar();
		if (g_char == '=') g_symbol = ASSIGN;
		else {
			retract();
			g_symbol = COLON;
		}
	}
	else if (g_char == '=') g_symbol = EQUAL;
	else if (g_char == '+') g_symbol = ADD;
	else if (g_char == '-') g_symbol = MINUS;
	else if (g_char == '*') g_symbol = STAR;
	else if (g_char == '(') g_symbol = LPAR;
	else if (g_char == ')') g_symbol = RPAR;
	else if (g_char == ',') g_symbol = COMMA;
	else if (g_char == ';') g_symbol = SEMI;
	else if (g_char == '/') {
		g_char = getNextChar();
		if (g_char == '*') {
			while (1) {
				g_char = getNextChar();
				if (g_char == '*') {
					g_char = getNextChar();
					if (g_char == '/')
						break;
					else
						continue;
				}
			}
		}
		else {
			retract();
			g_symbol = DIVI;
		}
	}
	else error();
}

void initial() {
	g_char = '\0';
	memset(g_token, 0, MAX_WORD * sizeof(char));
	g_num = -1;
	g_symbol = NOTHING; //设置为0,不在单词类别编码表内
}

int reserve() {
	int i;
	for (i = 0; i < REMAIN; i++) {
		if (_stricmp(remainSym[i], g_token) == 0)
			return (i + 1);
	}
	return 0;
}
