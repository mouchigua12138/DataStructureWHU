#include <iostream>
#include "CyclicQueue.h"
using namespace std;
template <typename Type> void CyclicQueue<Type>::move(Type** p) {
	if (this->inElem(*p + 1))(*p)++;
	else *p = this->_elem;
}
template <typename Type> bool CyclicQueue<Type>::inElem(Type* p) {
	if (p >= this->_elem && p <= this->_elem + this->_capacity - 1)return true;
	else return false;
}
template <typename Type> CyclicQueue<Type>::CyclicQueue(int _capacity) {
	this->_elem = new Type[_capacity];
	this->_capacity = _capacity;
	this->_size = 0;
	this->first = this->_elem;
	this->rear = this->_elem;
}
template <typename Type> CyclicQueue<Type>::CyclicQueue(CyclicQueue<Type> const& q) {
	this->_capacity = q._capacity;
	this->_size = q._size;
	this->_elem = new Type[this->_capacity];
	for (int i = 0; i < this->_capacity; i++)this->_elem[i] = q._elem[i];
	int nFirst = q.first - q._elem;
	this->first = this->_elem + nFirst;//定位头哨兵
	int nRear = q.rear - q._elem;
	this->rear = this->_elem + nRear;//定位尾哨兵
}
template <typename Type> CyclicQueue<Type>::~CyclicQueue() {
	delete[]this->_elem;//释放内存
}
template <typename Type> Rank CyclicQueue<Type>::size() const {
	return this->_size;
}
template <typename Type> bool CyclicQueue<Type>::empty() const {
	if (this->size() == 0)return true;
	else return false;
}
template <typename Type> bool CyclicQueue<Type>::full() const {
	if (this-> _size == this->_capacity)return true;
	else return false;
}
template <typename Type> void CyclicQueue<Type>::enqueue(Type const& e) {
	if (this->full()) {//如果循环队列已满
		cout << "此循环队列已满，无法入队" << endl;
		return;//拒绝入队
	}
	*this->rear = e;//插入元素至队尾
	this->move(&this->rear);//移动尾哨兵
	this->_size++;//修改规模
}
template <typename Type> Type CyclicQueue<Type>::dequeue() {
	if (this->empty()) {//如果循环队列为空
		cout << "此循环队列为空，无法出队" << endl;
		exit(0);//拒绝出队
	}
	Type temp = *this->first;//备份队头值
	this->move(&this->first);//移动头哨兵
	this->_size--;//修改规模
	return temp;//返回弹出值
}
template <typename Type> void CyclicQueue<Type>::traverse(void(*visit)(Type&)) {
	Type* p = this->first;//定位头节点
	int nCount = 0;//计数
	for (; nCount < this->size(); nCount++, this->move(&p))visit(*p);//遍历循环链表
}
template <typename Type> template <typename VST> void CyclicQueue<Type>::traverse(VST&) {
	Type* p = this->first;//定位头节点
	int nCount = 0;//计数
	for (; nCount < this->size(); nCount++, this->move(&p))VST(*p);//遍历循环链表
}