#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include "BitMap.h"
using namespace std;
void BitMap::init(int n) {
	this->N = (n + 7) / 8;
	M = new char[this->N];
	memset(M, 0, N);
}
BitMap::BitMap(int n) {
	this->init(n);
}
BitMap::BitMap(char* file, int n = 8) {
	this->init(n);
	ifstream in;
	in.open(file, ios::in | ios::binary);
	if (!in.is_open()) { 
		cout << "文件未正常打开" << endl;
		exit(0); 
	}
	in.read((char*)this->M, N);
	in.close();
}
BitMap::~BitMap() {
	delete[]M;//释放内存
}
void BitMap::set(int k) {
	this->expand(k);
	M[k >> 3] |= (0x80 >> (k & 0x07));
}
void BitMap::clear(int k) {
	this->expand(k);
	M[k >> 3] &= ~(0x80 >> (k & 0x07));
}
bool BitMap::test(int k) {
	this->expand(k);
	return M[k >> 3] & (0x80 >> (k & 0x07));
}
void BitMap::dump(char* file) {
	ofstream out;
	out.open(file, ios::out | ios::binary);
	if(!out.is_open()) {
		cout << "文件未正常打开" << endl;
		return;
	}
	out.write((char*)this->M, this->N);
	out.close();
}
char* BitMap::bits2string(int n) {
	this->expand(n - 1);
	char* s = new char[n + 1];
	s[n] = '\0';//字符串所占空间，由上层调用者负责释放
	for (int i = 0; i < n; i++)s[i] = this->test(i) ? '1' : '0';
	return s;//返回字符串位置
}
void BitMap::expand(int k) {
	if (k < 8 * this->N)return;//仍在界内，无序扩容
	int oldN = this->N;
	char* oldM = this->M;
	this->init(2 * k);//加倍策略
	memcpy(this->M, oldM, oldN);
	delete[]oldM;
}