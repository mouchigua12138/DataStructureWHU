#pragma once
#include "Vector.cpp"
template <typename Type> class Stack : public Vector<Type> {
public:
	void push(Type const& e);//入栈
	Type pop();//出栈
	Type& top();//取项
};