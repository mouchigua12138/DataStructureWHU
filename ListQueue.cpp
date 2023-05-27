#include "ListQueue.h"
template <typename Type> void ListQueue<Type>::enqueue(Type const& e) {
	this->insertAsLast(e);
}
template <typename Type> Type ListQueue<Type>::dequeue() {
	return this->remove(this->first());
}
template <typename Type> Type& ListQueue<Type>::front() {
	return this->first()->data;
}