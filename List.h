#pragma once
#include "ListNode.cpp"
template <typename Type> class List{
private:
	int _size;//规模
	ListNodePosi(Type) header;//头哨兵
	ListNodePosi(Type) trailer;//尾哨兵
protected:
	void init();//列表创建时初始化
	int clear();//清除所有节点
	void copyNodes(ListNodePosi(Type) p, int n);//复制列表中自位置p起的n项
	void merge(ListNodePosi(Type)& p, int n, List<Type>& L, ListNodePosi(Type)& q, int m);//归并
	void mergeSort(ListNodePosi(Type)& p, int n);//对从p开始连续的n个节点归并排序
	void selectionSort(ListNodePosi(Type)& p, int n);//对从p开始连续的n个节点选择排序
	void insertionSort(ListNodePosi(Type)& p, int n);//对从p开始连续的n个节点插入排序
public:
	List();//默认
	List(ListNodePosi(Type) p, int n);//复制列表中自位置p起的n项
	List(List<Type> const& L);//整体复制列表L
	List(List<Type> const& L, Rank r, int n);//复制列表中自第r项起的n项
	~List();//释放（包含头、尾哨兵在内的）所有节点
	Rank size() const;//规模
	bool empty() const;//判空
	Type& operator [] (Rank r) const;//重载，支持循秩访问（效率低）
	ListNodePosi(Type) first() const;//首节点位置
	ListNodePosi(Type) last() const;//末节点位置
	bool valid(ListNodePosi(Type) p);//判断位置p是否对外合法
	int disordered() const;//判断列表是否已排序
	ListNodePosi(Type) find(Type const& e) const;//无序列表查找
	ListNodePosi(Type) find(Type const& e, int n, ListNodePosi(Type) p) const;//无序区间查找
	ListNodePosi(Type) search(Type const& e) const;//有序列表查找
	ListNodePosi(Type) search(Type const& e, int n, ListNodePosi(Type) p) const;//有序区间查找
	ListNodePosi(Type) selectMax(ListNodePosi(Type) p, int n);//在p及其n - 1个后继中选出最大者
	ListNodePosi(Type) selectMax();//整体最大者
	ListNodePosi(Type) insertAsFirst(Type const& e);//将e当作首节点插入
	ListNodePosi(Type) insertAsLast(Type const& e);//将e当作末节点插入
	ListNodePosi(Type) insertA(ListNodePosi(Type) p, Type const& e);//将e当作p的后继插入
	ListNodePosi(Type) insertB(ListNodePosi(Type) p, Type const& e);//将e当作p的前驱插入
	Type remove(ListNodePosi(Type) p);//删除合法位置p处的节点，返回被删除节点
	void merge(List<Type>& L);//全列表归并
	void sort(ListNodePosi(Type) p, int n);//列表区间排序
	void sort();//列表整体排序
	int deduplicate();//无序去重
	int uniquify();//有序去重
	void reverse();//前后倒置
	void traverse(void(*visit)(Type&));//遍历（使用函数指针，只读或局部性修改）
	template <typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};
template <typename Type> void List<Type>::init() {
	this->header = new ListNode<Type>;//创建头哨兵节点
	this->trailer = new ListNode<Type>;//创建尾哨兵节点
	this->header->succ = this->trailer;
	this->header->pred = NULL;
	this->trailer->pred = this->header;
	this->trailer->succ = NULL;
	this->_size = 0;//记录规模
}
template <typename Type> int List<Type>::clear() {
	int oldSize = this->_size;
	while (0 < this->_size) this->remove(this->header->succ);//反复删除首节点直至列表变空
	return oldSize;
}
template <typename Type> void List<Type>::copyNodes(ListNodePosi(Type) p, int n) {
	this->init();//创建头、尾哨兵节点并做初始化
	while (n--) {
		this->insertAsLast(p->data);
		p = p->succ;
	}//将起自p的n项依次作为末节点插入
}
template <typename Type> void List<Type>::merge(ListNodePosi(Type)& p, int n, List<Type>& L, ListNodePosi(Type)& q, int m) {
	ListNodePosi(Type) pp = p->pred;//借助前驱，以便返回
	while (0 < m) {//在q尚未移出区间之前
		if ((0 < n) && (p->data < q->data)) {//若p仍在区间内且v(p) <= v(q),则
			p = p->succ;
			if (q == p)break;
			n--;
		}//p归入合并的列表，并替换为其直接后继
		else {//若p已超出右界或v(q) < v(p)，则
			q = q->succ;
			this->insertB(p, L.remove(q->pred));
			m--;
		}//讲q转移至p之前
	}
	p = pp->succ;//确定归并后区间的（新）起点
}
template <typename Type> void List<Type>::mergeSort(ListNodePosi(Type)& p, int n) {
	if (n < 2)return;//若待排序范围已足够小，则之间返回，否则
	int m = n >> 1;//以中点为界
	ListNodePosi(Type) q = p;
	for (int i = 0; i < m; i++)q = q->succ;//均分列表
	mergeSort(p, m);//对前子列表排序
	mergeSort(q, n - m);//对后子列表排序
	merge(p, m, *this, q, n - m);//归并
}//注意：排序后，p依然指向归并后区间的（新）起点
template <typename Type> void List<Type>::selectionSort(ListNodePosi(Type)& p, int n) {
	ListNodePosi(Type) head = p->pred;
	ListNodePosi(Type) tail = p;
	for (int i = 0; i < n; i++)tail = tail->succ;//待排区间为(head, tail)
	while (1 < n) {//在至少还剩两个节点之前，在待排区间内
		ListNodePosi(Type) max = this->selectMax(head->succ, n);//找出最大者（歧义时后者优先）
		this->insertB(tail, this->remove(max));//讲其移至无序区间末尾（作为有序区间的首元素）
		tail = tail->pred;
		n--;
	}
}
