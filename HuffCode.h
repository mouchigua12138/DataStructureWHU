#pragma once
#define HuffTree BinTree<HuffChar>
#define N_CHAR (0x80 - 0x20)//只考虑可打印字符
#include "BinTree.cpp"
#include "BitMap.h"
#include "HuffChar.h"
#include "Vector.cpp"
typedef List<HuffTree*> HuffForest;
typedef BitMap HuffCode;
struct Table{
	char key;
	char* value;
	Table(){}
	Table(char k, char* v) : key(k), value(v){}
};
typedef Vector<Table> HuffTable;
int* statistics(char* sample_text_file);//统计字符出现频率
HuffForest* initForest(int* freq);//根据频率统计表，为每个字符创建一棵树
HuffTree* minHChar(HuffForest* forest);//在Huffman森林中找出权重最小的字符
HuffTree* generateTree(HuffForest* forest);//Huffman编码算法
static void generateCT(BitMap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v);
HuffTable* generateTable(HuffTree* tree);//将各字符编码统一存入以散列表实现的编码表中
char* getValue(HuffTable* table, char k);
int encode(HuffTable* table, BitMap* codeString, char* s);//按照编码表对BitMap串编码
void decode(HuffTree* tree, BitMap* code, int n);//根据编码树对长为n的BitMap串解码