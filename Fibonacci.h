#pragma once
class Fibonacci{
private:
	int f, g;//f = fib(k - 1), g = fib(k)，均为int型，很快就会数值溢出
public:
	Fibonacci(int n);//初始化为不小于n的最小Fibbonaci项
	int get();//获取当前Fibonacci项
	int next();//转至下一Fibonacci项
	int prev();//转至上一Fibonacci项
};

