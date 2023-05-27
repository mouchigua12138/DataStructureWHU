#include "Stack.h"
template <typename Type> void Stack<Type>::push(Type const& e) {
	this->insert(this->size(), e);
}
template <typename Type> Type Stack<Type>::pop() {
	return this->remove(this->size() - 1);
}
template <typename Type> Type& Stack<Type>::top() {
	return (*this)[this->size() - 1];
}