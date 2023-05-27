#include "Fibonacci.h"
Fibonacci::Fibonacci(int n) {
	f = 1;
	g = 0;
	while (g < n)this->next();
}
int Fibonacci::get() {
	return g;
}
int Fibonacci::next() {
	g += f;
	f = g - f;
	return g;
}
int Fibonacci::prev() {
	f = g - f;
	g -= f;
	return g;
}