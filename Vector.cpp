#include <iostream>
#include "Search.h"
#include "Tools.h"
#include "Vector.h"
using namespace std;
template <typename Type> void Vector<Type>::copyForm(Type const* A, Rank lo, Rank hi) {
	this->_capacity = 2 * (hi - lo);
	this->_elem = new Type[this->_capacity];//分配空间
	this->_size = 0;//规模清零
	while (lo < hi) {//A[lo, hi)内的元素逐一
		_elem[this->_size] = A[lo];//复制至_elem[lo, hi)
		this->_size++;
		lo++;
	}
}
template <typename Type> void Vector<Type>::expand() {
	if (this->_size < _capacity)return;//尚未满员时不必扩容
	if (this->_capacity < DEFAULT_CAPACITY)this->_capacity = DEFAULT_CAPACITY;//不低于最小容量
	Type* oldElem = this->_elem;
	this->_capacity <<= 1;
	this->_elem = new Type[this->_capacity];//容量加倍
	for (int i = 0; i < this->_size; i++)this->_elem[i] = oldElem[i];//复制原向量内容
	delete[]oldElem;//释放原空间
}
template <typename Type> void Vector<Type>::shrink() {//装填因子过小时压缩向量所占空间
	if (this->_capacity < DEFAULT_CAPACITY << 1)return;//不致收缩到DEFAULT_CAPACITY以下
	if (this->_size << 2 > this->_capacity)return;//以25%为界
	Type* oldElem = this->_elem;
	this->_capacity >>= 1;
	this->_elem = new Type[this->_capacity];//容量减半
	for (int i = 0; i < this->_size; i++)this->_elem[i] = oldElem[i];//复制原向量内容
	delete[]oldElem;//释放原空间
}
template <typename Type> bool Vector<Type>::bubble(Rank lo, Rank hi) {
	bool sorted = true;//整体有序标志
	lo++;
	while (lo < hi) {//自左向右，逐一检查各对相邻元素
		if (this->_elem[lo - 1] > this->_elem[lo]) {//若逆序，则
			sorted = false;//意味着尚未整体有序，并需要
			swap(this->_elem[lo - 1], this->_elem[lo]);//通过交换使整体有序
		}
		lo++;
	}
	return sorted;
}
template <typename Type> void Vector<Type>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi))hi--;//逐趟做扫描交换，直至全序
}
template <typename Type> Rank Vector<Type>::max(Rank lo, Rank hi) {
	Type max = this->_elem[lo];
	Rank pos = lo;//以_elem[lo]为基准
	while (lo < hi) {//自左向右，逐一检查个元素
		if (max < this->_elem[lo]) {
			max = this->_elem[lo];//选取最大值
			pos = lo;//定位最大值
		}
		lo++;
	}
	return pos;
}
template <typename Type> void Vector<Type>::selectionSort(Rank lo, Rank hi) {
	int i ;
	for (i = 0; i < hi - lo; i++) {
		Rank pos = max(lo, hi - i);//寻找[lo, hi - i)上的最大值
		swap(this->_elem[pos], this->_elem[hi - i - 1]);//将最大值置于区间[lo, hi - i)的最右边
	}
}
template <typename Type> void Vector<Type>::merge(Rank lo, Rank mi, Rank hi) {//各自有序的子向量[lo, mi)和[mi, hi)
	Type* A = this->_elem + lo;//合并后的向量A[0, hi - lo) = _elem[lo, hi)
	int lb = mi - lo;
	Type* B = new Type[lb];//前子向量B[0, lb) = _elem[lo, mi)
	for (Rank i = 0; i < lb; i++)B[i] = A[i];//复制前子向量
	int lc = hi - mi;
	Type* C = this->_elem + mi;//后子向量C[0, lc) = _elem[mi, hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {//B[j]和C[k]中的小者续至A末尾
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) {
			A[i] = B[j];
			i++;
			j++;
		}
		if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) {
			A[i] = C[k];
			i++;
			k++;
		}
	}
	delete[]B;//释放临时空间B
}
template <typename Type> void Vector<Type>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2)return;//单元素区间自然有序
	int mi = (lo + hi) >> 1;//以中点为界
	mergeSort(lo, mi);
	mergeSort(mi, hi);//分别排序
	merge(lo, mi, hi);//归并
}
template <typename Type> Rank Vector<Type>::partition(Rank lo, Rank hi) {
	swap(this->_elem[lo], this->_elem[lo + rand() % (hi - lo + 1)]);//任选一个元素与首元素交换
	Type pivot = this->_elem[lo];//以首元素为候选轴点——经以上交换，等效于随机选取
	while (lo < hi) {//从向量两端交替向中间扫描
		while (lo < hi) {
			if (pivot < this->_elem[hi]) {//在大于pivot的前提下
				hi--;//向左拓展右端子向量
			}
			else {//直至遇到不大于pivot者
				this->_elem[lo] = this->_elem[hi];
				lo++;//将其归入左端子向量
				break;
			}
		}
		while (lo < hi) {
			if (this->_elem[lo] < pivot) {//在小于pivot的前提下
				lo++;//向右拓展左端子向量
			}
			else {//直至遇到不小于pivot者
				this->_elem[hi] = this->_elem[lo];
				hi--;//将其归入右端子向量
				break;
			}
		}
	}//assert: lo == hi
	this->_elem[lo] = pivot;//将备份的轴点记录置于前、后子向量之间
	return lo;//返回轴点的秩
}
template <typename Type> void Vector<Type>::quickSort(Rank lo, Rank hi) {
	if (hi - lo < 2)return;//单元素区间自然有序
	Rank mi = partition(lo, hi - 1);//在[lo, hi - 1]内构造轴点
	quickSort(lo, mi);//对前缀递归排序
	quickSort(mi + 1, hi);//对后缀递归排序
}
template <typename Type> Vector<Type>::Vector() {
	this->_elem = new Type[DEFAULT_CAPACITY];
	this->_capacity = DEFAULT_CAPACITY;
	for (this->_size = 0; this->_size < 0; this->_size++){
		//this->_elem[this->_size] = NULL;
	}
}
template <typename Type> Vector<Type>::Vector(int s) {
	this->_capacity = 2 * s;
	this->_size = s;
	if (s > 0)this->_elem = new Type[this->_capacity];
}
template <typename Type> Vector<Type>::Vector(int c, int s, Type v) {
	this->_elem = new Type[c];
	this->_capacity = c;
	for (this->_size = 0; this->_size < s; this->_elem[_size] = v, this->_size++);
}//s <= c
template <typename Type> Vector<Type>::Vector(Type const* A, Rank n) {
	this->copyForm(A, 0, n);
}
template <typename Type> Vector<Type>::Vector(Type const* A, Rank lo, Rank hi) {
	this->copyForm(A, lo, hi);
}
template <typename Type> Vector<Type>::Vector(Vector<Type> const& V) {
	copyForm(V._elem, 0, V._size);
}
template <typename Type> Vector<Type>::Vector(Vector<Type> const& V, Rank lo, Rank hi) {
	copyForm(V._elem, lo, hi);
}
template <typename Type> Vector<Type>::~Vector() {
	delete[]this->_elem;//释放内存
}
template <typename Type> Rank Vector<Type>::size() const {
	return this->_size;
}
template <typename Type> bool Vector<Type>::empty() const {
	return !this->_size;
}
template <typename Type> int Vector<Type>::disordered() const {
	int n = 0;//计数器
	for (int i = 1; i < this->_size; i++) {//逐一检查_size - 1对相邻元素
		if (this->_elem[i - 1] > this->_elem[i])n++;//逆序则计数
	}
	return 0;//向量有序当且仅当n = 0
}
template <typename Type> Rank Vector<Type>::find(Type const& e) const {
	return find(e, 0, this->_size);
}
template <typename Type> Rank Vector<Type>::find(Type const& e, Rank lo, Rank hi) const{//返回最后一个元素e的位置，失败时返回-1
	hi--;//确定区间为[lo, hi)
	while ((lo <= hi) && (e != this->_elem[hi])){//从后向前，顺序查找
		hi--;
	}
	return hi;//若hi < lo，则意味着失败，否则hi即命中元素的秩
}
template <typename Type> Rank Vector<Type>::search(Type const& e) const {
	return (0 >= this->_size) ? -1 : search(e, 0, this->_size);
}
template <typename Type> Rank Vector<Type>::search(Type const& e, Rank lo, Rank hi) const {
	return (rand() % 2) ? binSearch(this->_elem, e, lo, hi) : fibSearch(this->_elem, e, lo, hi);
	//按50%的概率随机使用二分查找或Fibonacci查找
}
template <typename Type> Type& Vector<Type>::operator [] (Rank r) const {
	return this->_elem[r];
}
template <typename Type> Vector<Type>& Vector<Type>::operator = (Vector<Type> const& V) {
	if (this->_elem)delete[]this->_elem;//释放原有内容
	copyForm(V._elem, 0, V.size());
	return *this;
}
template <typename Type> Type Vector<Type>::remove(Rank r) {
	Type e = this->_elem[r];//备份被删除元素
	remove(r, r + 1);//调用区间删除算法，等效于对区间[r, r + 1)的删除
	return e;//返回被删除元素
}
template <typename Type> int Vector<Type>::remove(Rank lo, Rank hi) {
	if (lo == hi)return 0;//出于效率考虑，单独处理退化情况，比如remove(0, 0)
	while (hi < this->_size) {//[hi, _size)顺次前移hi - lo个单元
		this->_elem[lo] = this->_elem[hi];
		lo++;
		hi++;
	}
	this->_size = lo;//更新规模，之间丢弃尾部[lo, _size = hi)区间
	this->shrink();//如有必要，则缩容
	return hi - lo;//返回被删除元素数目
}
template <typename Type> Rank Vector<Type>::insert(Rank r, Type const& e) {
	this->expand();//如有必要，扩容
	for (int i = this->_size; i > r; i--)this->_elem[i] = this->_elem[i - 1];//自后向前，后继元素顺次后移一个单元
	this->_elem[r] = e;//置入新元素
	this->_size++;//更新容量
	return r;//返回秩
}
template <typename Type> Rank Vector<Type>::insert(Type const& e) {
	return insert(this->_size, e);
}
template <typename Type> void Vector<Type>::sort(Rank lo, Rank hi) {
	switch (rand() % 5) {
	case 1:
		this->bubbleSort(lo, hi); 
		break;//冒泡排序
	case 2:
		this->selectionSort(lo, hi);
		break;//选择排序
	case 3:
		this->mergeSort(lo, hi);
		break;//归并排序
	case 4:
		this->heapSort(lo, hi);
		break;//堆排序
	default:
		this->quickSort(lo, hi);
		break;//快速排序
	}
}
template <typename Type> void Vector<Type>::sort() {
	sort(0, this->_size);
}
template <typename Type> void Vector<Type>::unsort(Rank lo, Rank hi) {
	Type* V = this->_elem + lo;//将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
	for (Rank i = hi - lo; i > 0; i--)swap(V[i - 1], V[rand() % i]);//自后向前将V[i - 1]与V[0, i)中某一元素随机交换
}
template <typename Type> void Vector<Type>::unsort() {
	unsort(0, this->_size);
}
template <typename Type> int Vector<Type>::deduplicate() {
	int oldSize = _size;//记录原规模
	Rank i = 1;//从_elem[1]开始
	while (i < this->_size) {//自前向后考察各元素_elem[i]
		if (this->find(this->_elem[i], 0, i) == -1)i++;//在其前缀中寻找与之雷同者（至多一个），若无雷同继续考察其后继
		else remove(i);//否则删除雷同者
	}
	return oldSize - this->_size;//向量规模变化量，即被删除元素总数
}
template <typename Type> int Vector<Type>::uniquify() {
	Rank i = 0, j = 1;//各对互异“相邻”元素的秩
	while (j < this->_size) {//逐个扫描，直至末元素
		if (this->_elem[i] != this->_elem[j]) {//跳过雷同者
			i++;
			this->_elem[i] = this->_elem[j];//发现不同元素时，向前移至紧邻于前者右侧
		}
		j++;
	}
	i++;
	this->_size = i;//直接截除尾部多余元素
	this->shrink();
	return j - i;//向量规模变化量，即被删除元素总数
}
template <typename Type> void Vector<Type>::traverse(void(*visit)(Type&)) {
	for (int i = 0; i < this->_size; i++)visit(this->_elem[i]);//遍历向量
}
template <typename Type> template <typename VST> void Vector<Type>::traverse(VST& visit) {//元素类型，操作器
	for (int i = 0; i < this->_size; i++)visit(this->_elem[i]);//遍历向量
}