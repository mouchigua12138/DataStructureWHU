#include "Fibonacci.h"
#include "Search.h"
template <typename Type> static int binSearch(Type* A, Type const& e, int lo, int hi) {
	while (hi - lo > 1) {//每步迭代可能要做两次比较判断，有三个分支
		int mi = (lo + hi) >> 1;//以中点为轴点
		if (e < A[mi])hi = mi;//深入前半段[lo, mi)继续查找
		else if (e > A[mi])lo = mi + 1;//深入后半段(mi, hi)继续查找
		else return mi;//在mi处命中
	}//成功查找可以提前终止
	return -1;//查找失败
}//有多个命中元素时，不能保证返回秩最大者，查找失败时返回-1
template <typename Type> static int fibSearch(Type* A, Type const& e, int lo, int hi) {
	Fibonacci fib(hi - lo);//创建Fibonacci数列
	while (lo < hi) {//每步迭代可能要做两次比较判断，有三个分支
		while (hi - lo < fib.get())fib.prev;//通过向前顺序查找
		int mi = lo + fib.get() - 1;//确定形如fib(k) - 1的点
		if (e < A[mi])hi = mi;//深入前半段[lo, mi)继续查找
		else if (e > A[mi])lo = mi + 1;//深入后半段(mi, hi)继续查找
		else return mi;//在mi处命中
	}
	return -1;//查找失败
}