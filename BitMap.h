#pragma once
class BitMap {
private:
	char* M;//位图所存放的空间
	int N;//容量为N * sizeof(char) * 8比特
protected:
	void init(int n);//初始化
public:
	BitMap(int n = 8);//构造函数
	BitMap(char* file, int n);//按指定或默认规模，从指定文件中读取位图
	~BitMap();//析构函数
	void set(int k);
	void clear(int k);
	bool test(int k);
	void dump(char* file);//将位图整体导出至指定的文件，以便对此后的新位图批量初始化
	char* bits2string(int n);//将前n位转换为字符串
	void expand(int k);//若被访问的Bitmap[k]已出界，则需扩容
};

