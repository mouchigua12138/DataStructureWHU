#pragma once
struct HuffChar {//Huffman字符
	char ch;//字符
	int weight;//频率
	HuffChar(char c = '^', int w = 0) : ch(c), weight(w) {}
	bool operator < (HuffChar const& hc);
	bool operator > (HuffChar const& hc);
	bool operator == (HuffChar const& hc);
};