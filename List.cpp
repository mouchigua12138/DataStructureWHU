#include "List.h"
template <typename Type> void List<Type>::insertionSort(ListNodePosi(Type)& p, int n) {
	for (int r = 0; r < n; r++) {//逐一为各节点
		this->insertA(this->search(p->data, r, p), p->data);//查找适当的位置并插入
		p = p->succ;
		if (p->pred != NULL)this->remove(p->pred);//转向下一节点
	}
}
template <typename Type> List<Type>::List() {
	this->init();
}
template <typename Type> List<Type>::List(ListNodePosi(Type) p, int n) {
	this->copyNodes(p, n);
}
template <typename Type> List<Type>::List(List<Type> const& L) {
	this->copyNodes(L.first(), L.size());
}
template <typename Type> List<Type>::List(List<Type> const& L, Rank r, int n) {
	this->copyNodes(L[r], n);
}
template <typename Type> List<Type>::~List() {
	this->clear();//清空列表
	delete header;//释放头节点
	delete trailer;//释放尾节点
}
template <typename Type> Rank List<Type>::size() const {
	return this->_size;
}
template <typename Type> bool List<Type>::empty() const {
	return this->_size <= 0;
}
template <typename Type> Type& List<Type>::operator [] (Rank r) const {
	ListNodePosi(Type) p = this->first();//从首节点出发
	while (0 < r) {
		p = p->succ;
		r--;
	}//顺数第r个节点
	return p->data;//目标节点，返回其中所存元素
}
template <typename Type> ListNodePosi(Type) List<Type>::first() const {
	return this->header->succ;
}
template <typename Type> ListNodePosi(Type) List<Type>::last() const {
	return this->trailer->pred;
}
template <typename Type> bool List<Type>::valid(ListNodePosi(Type) p) {
	return p && (trailer != p) && (header != p);//将头，尾节点等同于NULL
}
template <typename Type> int List<Type>::disordered() const {
	int count = 0;//逆序数
	if (this->_size < 2) return count;//平凡列表自然有序
	ListNodePosi(Type) p = this->first();//从首节点遍历
	while (p->succ != this->trailer) {//从左向右遍历
		if (p->data > p->succ->data)count++;//如发现逆序，则逆序数count自加一
		p = p->succ;
	}
	return count;//返回逆序数
}
template <typename Type> ListNodePosi(Type)	List<Type>::find(Type const& e) const {
	return this->find(e, this->_size, this->trailer);
}
template <typename Type> ListNodePosi(Type) List<Type>::find(Type const& e, int n, ListNodePosi(Type) p) const {
	while (0 < n) {//(0 <= n <= rank(p) < _size)对于p的最近n个前驱，从右向左
		p = p->pred;
		if (e == p->data)return p;//逐个比对，直至命中或范围越界
		n--;
	}
	return NULL;//p越出左边界意味着区间内不含e,查找失败
}//失败时，返回NULL
template <typename Type> ListNodePosi(Type) List<Type>::search(Type const& e) const {
	return this->search(e, this->_size, this->trailer);
}
template <typename Type> ListNodePosi(Type) List<Type>::search(Type const& e, int n, ListNodePosi(Type) p) const {
	while (0 <= n) {//对于p的最近的n个前驱，从右向左逐个比较
		p = p->pred;
		if (p->data <= e)break;//直至命中、数值越界或范围越界
		n--;
	}
	return p;//返回查找终止时的位置
}
template <typename Type> ListNodePosi(Type) List<Type>::selectMax(ListNodePosi(Type) p, int n) {
	Type max = p->data;
	ListNodePosi(Type) q = p;
	ListNodePosi(Type) qMax = p;//以p节点作为基准
	for (int i = 0; i < n; i++, q = q->succ) {////对于p及其最近的(n - 1)个后驱，从左向右逐个比较
		if (q->data > max) {//如果发现新的最大值
			max = q->data;//更新最大值
			qMax = q;//更新最大位置
		}
	}
	return qMax;
}
template <typename Type> ListNodePosi(Type) List<Type>::selectMax() {
	return this->selectMax(this->header->succ, this->_size);
}
template <typename Type> ListNodePosi(Type) List<Type>::insertAsFirst(Type const& e) {
	this->_size++;
	return this->header->insertAsSucc(e);
}
template <typename Type> ListNodePosi(Type) List<Type>::insertAsLast(Type const& e) {
	this->_size++;
	return this->trailer->insertAsPred(e);
}
template <typename Type> ListNodePosi(Type) List<Type>::insertA(ListNodePosi(Type) p, Type const& e) {
	this->_size++;
	return p->insertAsSucc(e);
}
template <typename Type> ListNodePosi(Type) List<Type>::insertB(ListNodePosi(Type) p, Type const& e) {
	this->_size++;
	return p->insertAsPred(e);
}
template <typename Type> Type List<Type>::remove(ListNodePosi(Type) p) {
	Type e = p->data;//备份待删除节点的数值（假定Type类型可直接赋值）
	p->pred->succ = p->succ;//后继
	p->succ->pred = p->pred;//前驱
	delete p;//释放节点
	this->_size--;//更新规模
	return e;//返回备份的数值
}
template <typename Type> void List<Type>::merge(List<Type>& L) {
	this->merge(this->first(), this->size(), L, L.first(), L.size());
}
template <typename Type> void List<Type>::sort(ListNodePosi(Type) p, int n) {
	switch (rand() % 3) {//随机选取排序算法
	case 1:
		this->insertionSort(p, n);
		break;//插入排序
	case 2:
		this->selectionSort(p, n);
		break;//选择排序
	default:
		this->mergeSort(p, n);
		break;//归并排序
	}
}
template <typename Type> void List<Type>::sort() {
	this->sort(this->first(), this->_size);
}
template <typename Type> int List<Type>::deduplicate() {
	if (this->_size < 2)return 0;//平凡列表自然无重复
	int oldSize = this->_size;//记录原规模
	ListNodePosi(Type) p = header->succ;
	Rank r = 0;//p从首节点开始
	while (this->trailer != p) {//依次直到末节点
		ListNodePosi(Type) q = find(p->data, r, p);//在p的r个（真）前驱中查找雷同者
		q ? remove(q) : r++;//若的确存在，则删除之，否则秩加一
		p = p->succ;
	}
	return oldSize = this->_size;//列表规模变化量，即被删除元素总数
}
template <typename Type> int List<Type>::uniquify() {
	if (this->_size < 2)return 0;//平凡列表自然无重复
	int oldSize = this->_size;//记录原规模
	ListNodePosi(Type) p = this->first();
	ListNodePosi(Type) q = p->succ;//p为各区段起点,q为其后继
	while (this->trailer != q) {//反复考察紧邻的节点对(p, q)
		if (p->data != q->data)p = q;//若互异，则转向下一区段
		else this->remove(q);//否则（雷同）删除后者
		q = p->succ;
	}
	return oldSize - this->_size;//列表规模变化量，即被删除元素总数
}
template <typename Type> void List<Type>::reverse() {
	Type* temp = new Type[this->_size];//构造临时数组暂存数据
	ListNodePosi(Type) p = this->first();//从首节点开始
	for (int i = 0; i < this->_size; i++, p = p->succ)temp[i] = p->data;//将列表拷贝在temp数组内
	p = this->first();//p指针复位
	for (int i = 0; i < this->_size; i++, p = p->succ)p->data = temp[this->_size - i - 1];//将temp数组逆向拷贝到列表中
	delete[]temp;//释放temp内存
}
template <typename Type> void List<Type>::traverse(void(*visit)(Type&)) {
	for (ListNodePosi(Type) p = this->header->succ; p != this->trailer; p = p->succ)visit(p->data);
}
template <typename Type> template <typename VST> void List<Type>::traverse(VST& visit) {
	for (ListNodePosi(Type) p = this->header->succ; p != this->trailer; p = p->succ)visit(p->data);
}