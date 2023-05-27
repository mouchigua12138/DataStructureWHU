#include <iostream>
#include <memory>
#include "BinTree.h"
#include "Comparer.cpp"
template <typename Type> int BinTree<Type>::updateHeight(BinNodePosi(Type) x) {
	x->height = 1 + std::max(stature(x->lc), stature(x->rc));
	return x->height;
}
template <typename Type> void BinTree<Type>::updateHeightAbove(BinNodePosi(Type) x) {
	while (x) {
		this->updateHeight(x);
		x = x->parent;
	}//从x出发覆盖历代祖先
}
template <typename Type> BinTree<Type>::BinTree() {
	this->_size = 0;
	this->_root = NULL;
}
template <typename Type> BinTree<Type>::~BinTree() {
	if (0 < this->_size)this->remove(this->_root);
}
template <typename Type> int BinTree<Type>::size() const {
	return this->_size;
}
template <typename Type> bool BinTree<Type>::empty() const {
	return !this->_root;
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::root() const {
	return this->_root;
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::insertAsRoot(Type const& e) {
	this->_size = 1;
	this->_root = new BinNode<Type>(e);
	return this->_root;
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::insertAsLC(BinNodePosi(Type) x, Type const& e) {
	this->_size++;//更新规模
	x->insertAsLC(e);
	this->updateHeightAbove(x);//更新高度
	return x->lc;
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::insertAsRC(BinNodePosi(Type) x, Type const& e) {
	this->_size++;//更新规模
	x->insertAsRC(e);
	this->updateHeightAbove(x);//更新高度
	return x->rc;
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::attachAsLC(BinNodePosi(Type) x, BinTree<Type>*& S) {
	x->lc = S->_root;
	if (x->lc) x->lc->parent = x;//接入
	this->_size += S->_size;//更新规模
	this->updateHeightAbove(x);//更新祖先高度
	S->_root = NULL;
	S->_size = 0;
	delete S;
	S = NULL;//释放原树
	return x;//返回接入位置
}
template <typename Type> BinNodePosi(Type) BinTree<Type>::attachAsRC(BinNodePosi(Type) x, BinTree<Type>*& S) {
	x->rc = S->_root;
	if (x->rc) x->rc->parent = x;//接入
	this->_size += S->_size;//更新规模
	this->updateHeightAbove(x);//更新祖先高度
	S->_root = NULL;
	S->_size = 0;
	delete S;
	S = NULL;//释放原树
	return x;//返回接入位置
}
template <typename Type> int BinTree<Type>::remove(BinNodePosi(Type) x) {
	FromParentTo(*x) = NULL;//切断来自父节点的指针
	this->updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x);//删除子树x
	this->_size = this->_size - n;//更新规模
	return n;//返回删除节点总数
}
template <typename Type> BinTree<Type>* BinTree<Type>::secede(BinNodePosi(Type) x) {
	//FromParentTo(*x) = NULL;//切断来自父节点的指针
	this->updateHeightAbove(x->parent);//更新原树中所有祖先的高度
	BinTree<Type>* S = new BinTree<Type>;
	S->_root = x;
	x->parent = NULL;//新树以x为根
	S->_size = x->size();
	this->_size -= S->_size;//更新规模
	return S;//返回分离出来的子树S
}
template <typename Type> template <typename VST> void BinTree<Type>::travLevel(VST& visit) {
	if (this->_root)this->_root->travLevel(visit);
}
template <typename Type> template <typename VST> void BinTree<Type>::travPre(VST& visit) {
	if (this->_root)this->_root->travPre(visit);
}
template <typename Type> template <typename VST> void BinTree<Type>::travIn(VST& visit) {
	if (this->_root)this->_root->travIn(visit);
}
template <typename Type> template <typename VST> void BinTree<Type>::travPost(VST& visit) {
	if (this->_root)this->_root->travPost(visit);
}
template <typename Type> bool BinTree<Type>::operator < (BinTree<Type> const& t) {
	return this->_root && t._root && lt(this->_root, t._root);
}
template <typename Type> bool BinTree<Type>::operator > (BinTree<Type> const& t) {
	return this->_root && t._root && mt(this->_root, t._root);
}
template <typename Type> bool BinTree<Type>::operator == (BinTree<Type> const& t) {
	return this->_root && t._root && eq(this->_root, t._root);
}
template <typename Type> static int removeAt(BinNodePosi(Type) x) {
    if (!x)return 0;//递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//递归释放左、右子树
	delete x;//释放被删除节点
	return n;//返回删除节点总数
}