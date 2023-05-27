#pragma once
#include "List.cpp"
template <typename Type> class ListQueue : public List<Type>{
public:
	void enqueue(Type const& e);//入队：尾部插入
	Type dequeue();//出队：首部删除
	Type& front();//队首
};