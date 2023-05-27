#include "Comparer.h"
template <typename Type> static bool lt(Type* a, Type* b) {
	return lt(*a, *b);
}
template <typename Type> static bool lt(Type& a, Type& b) {
	return a < b;
}
template <typename Type> static bool eq(Type* a, Type* b) {
	return eq(*a, *b);
}
template <typename Type> static bool eq(Type& a, Type& b) {
	return a == b;
}
template <typename Type> static bool mt(Type* a, Type* b) {
	return mt(*a, *b);
}
template <typename Type> static bool mt(Type& a, Type& b) {
	return a > b;
}