#include <fstream>
#include <iostream>
#include "HuffCode.h"
using namespace std;
int* statistics(char* sample_text_file) {//统计字符出现频率
	int* freq = new int[N_CHAR];
	memset(freq, 0, sizeof(int) * N_CHAR);//清零
	ifstream in;
	in.open(sample_text_file, ios::in | ios::binary);
	if (!in.is_open()) {
		cout << "文件未正常打开" << endl;
		exit(0);
	}
	for (char ch; in.read((char*)&ch, 1); in.peek() != EOF) {//逐个扫描样本文件中的每个字符
		if (ch >= 0x20)freq[ch - 0x20]++;//累计对应出现次数
	}
	in.close();
	return freq;
}
HuffForest* initForest(int* freq) {
	HuffForest* forest = new HuffForest;//以List实现的Huffman森林
	for (int i = 0; i < N_CHAR; i++) {//为每个字符
		forest->insertAsLast(new HuffTree);//生成一棵树，并将字符及其频率
		forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i]));//存入其中
	}
	return forest;
}
HuffTree* minHChar(HuffForest* forest) {
	ListNodePosi(HuffTree*) p = forest->first();//从首节点出发查找
	ListNodePosi(HuffTree*) minChar = p;//最小Huffman树所在的节点位置
	int minWeight = p->data->root()->data.weight;//目前的最小权重
	p = p->succ;
	while (forest->valid(p)) {//遍历所有节点
		if (minWeight > p->data->root()->data.weight) {//若当前节点所含树更小，则
			minWeight = p->data->root()->data.weight;
			minChar = p;
		}//更新记录
		p = p->succ;
	}
	return forest->remove(minChar);//将挑选出的Huffman树从森林中摘除，并返回
}
HuffTree* generateTree(HuffForest* forest) {
	while (1 < forest->size()) {
		HuffTree* T1 = minHChar(forest);
		HuffTree* T2 = minHChar(forest);
		HuffTree* S = new HuffTree();
		S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
		S->attachAsLC(S->root(), T1);
		S->attachAsRC(S->root(), T2);
		forest->insertAsLast(S);
	}//assert：循环结束时，森林中唯一（列表首节点中）那棵树即为Huffman编码树
	return forest->first()->data;
}
static void generateCT(BitMap* code, int length, HuffTable* table, BinNodePosi(HuffChar) v) {
	if (IsLeaf(*v)) {//若是叶节点
		table->insert(*(new Table(v->data.ch, code->bits2string(length))));
		return;
	}
	if (HasLChild(*v)) {//left = 0
		code->clear(length);
		generateCT(code, length + 1, table, v->lc);
	}
	if (HasRChild(*v)) {//right = 1 
		code->set(length);
		generateCT(code, length + 1, table, v->rc);
	}
}
HuffTable* generateTable(HuffTree* tree) {
	HuffTable* table = new HuffTable(0);
	BitMap* code = new BitMap;
	generateCT(code, 0, table, tree->root());
	delete code;
	return table;
}
char* getValue(HuffTable* table, char k) {
	char* pCharCode = NULL;
	for (int j = 0; j < table->size(); j++) {
		if ((*table)[j].key == k)pCharCode = (*table)[j].value;//取出其对应的编码串
	}
	return pCharCode;
}
int encode(HuffTable* table, BitMap* codeString, char* s) {
	int n = 0;
	for (size_t m = strlen(s), i = 0; i < m; i++) {//对于明文中的每个字符
		char* pCharCode = getValue(table, s[i]);
		if (!pCharCode)pCharCode = getValue(table, s[i] + 'A' - 'a');//小写字母转为大写
		if (!pCharCode)pCharCode = getValue(table, ' ');//无法识别的字符统一视作空格
		cout << pCharCode;//输出当前字符编码
		for (size_t m = strlen(pCharCode), j = 0; j < m; j++) {
			'1' == *(pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
		}
	}
	cout << endl;
	return n;
}
void decode(HuffTree* tree, BitMap* code, int n) {
	BinNodePosi(HuffChar) x = tree->root();
	for (int i = 0; i < n; i++) {
		x = code->test(i) ? x->rc : x->lc;
		if (IsLeaf(*x)) {
			cout << (x->data.ch);
			x = tree->root();
		}
	}
}