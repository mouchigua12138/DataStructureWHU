#pragma once
#define DEFAULT_CAPACITY 10
#include <iostream>
typedef int Rank;//向量的秩
template <typename Type> class Vector{
protected:
	Rank _size;//规模
	int _capacity;//容量
	Type* _elem;//数据区
	void copyForm(Type const* A, Rank lo, Rank hi);//复制数组区间A[lo, hi)
	void expand();//空间不足时扩容
	void shrink();//装填因子过小时压缩
	bool bubble(Rank lo, Rank hi);//扫描交换
	void bubbleSort(Rank lo, Rank hi);//冒泡排序算法
	Rank max(Rank lo, Rank hi);//选取最大元素
	void selectionSort(Rank lo, Rank hi);//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergeSort(Rank lo, Rank hi);//归并排序算法
	Rank partition(Rank lo, Rank hi);//轴点构造算法
	void quickSort(Rank lo, Rank hi);//快速排序算法
	void heapSort(Rank lo, Rank hi);//堆排序
public:
	Vector();//使用默认参数容量为DEFAULT_CAPACITY，规模为0，所有元素初始为0
	Vector(int s);//默认规模
	Vector(int c, int s, Type v);//容量为c，规模为s，所有元素初始为v
	Vector(Type const* A, Rank n);//数组整体复制
	Vector(Type const* A, Rank lo, Rank hi);//区间
	Vector(Vector<Type> const& V);//向量整体复制
	Vector(Vector<Type> const& V, Rank lo, Rank hi);//区间
	~Vector();//析构函数
	Rank size() const;//规模
	bool empty() const;//判空
	int disordered() const;//判断向量是否已排序
	Rank find(Type const& e) const;//无序向量整体查找
	Rank find(Type const& e, Rank lo, Rank hi) const;//无序向量区间查找
	Rank search(Type const& e) const;//有序向量整体查找
	Rank search(Type const& e, Rank lo, Rank hi) const;//有序向量区间查找
	Type& operator [] (Rank r) const;//重载下标运算符，可以类似于数组形式引用各元素
	Vector<Type>& operator = (Vector<Type> const&);//重载赋值运算符，以便直接克隆向量
	Type remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除秩在区间[lo, hi)之间的元素
	Rank insert(Rank r, Type const& e);//插入元素
	Rank insert(Type const& e);//默认作为末元素插入
	void sort(Rank lo, Rank hi);//对[lo, hi)排序
	void sort();//整体排序
	void unsort(Rank lo, Rank hi);//对[lo, hi)置乱
	void unsort();//整体置乱
	int deduplicate();//无序去重
	int uniquify();//有序去重
	void traverse(void(*visit)(Type&));//遍历（使用函数指针，只读或局部性修改）
	template <typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};