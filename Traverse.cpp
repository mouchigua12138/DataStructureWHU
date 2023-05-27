#include <iostream>
#include "Traverse.h"
template <typename Type> void print(Type e) {
	std::cout << e << " ";
}
template <typename Type> void increase(Type& e) {
	e++;
}
template <typename Type> void decrease(Type& e) {
	e--;
}
template <typename Type> void redouble(Type& e) {
	e *= 2;
}
template <typename Type> void half(Type& e) {
	e >>= 1;
}