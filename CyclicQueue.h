#pragma once
typedef int Rank;
template <typename Type> class CyclicQueue{
private:
	Rank _size;//规模
	int _capacity;//容量
	Type* _elem;//数据区
	Type* first;//头哨兵
	Type* rear;//尾哨兵
	void move(Type** p);//移动哨兵位置
	bool inElem(Type* p);//判断指针是否位于存储区
public:
	CyclicQueue(int _capacity);//构造函数
	CyclicQueue(CyclicQueue const& q);//拷贝构造函数
	~CyclicQueue();//析构函数
	Rank size() const;//规模
	bool empty() const;//判空
	bool full() const;//判满
	void enqueue(Type const& e);//入队：尾部插入
	Type dequeue();//出队：首部删除
	void traverse(void(*visit)(Type&));//遍历（使用函数指针，只读或局部性修改）
	template <typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};