#include "BinNode.h"
#include "ListQueue.cpp"
template <typename Type> BinNodePosi(Type) BinNode<Type>::insertAsLC(Type const& e) {
	this->lc = new BinNode(e, this);//将e作为当前节点的左孩子插入二叉树
	return this->lc;
}
template <typename Type> BinNodePosi(Type) BinNode<Type>::insertAsRC(Type const& e) {
	this->rc = new BinNode(e, this);//将e作为当前节点的右孩子插入二叉树
	return this->rc;
}
template <typename Type> BinNodePosi(Type) BinNode<Type>::succ() {
	BinNodePosi(Type) s = this;//记录后继的临时变量
	if (this->rc) {//若有右孩子，则直接后继必在右子树中
		s = this->rc;//右子树中
		while (HasLChild(*s))s = s->lc;//最靠左（最小）的节点
	}
	else {//否则，直接后继是“将当前节点包含于其左子树的最低祖先”
		while (IsRChild(*s))s = s->parent;//逆向地沿向右分支，不断朝左上方移动
		s = s->parent;//最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}
template <typename Type> template <typename VST> void BinNode<Type>::travLevel(VST& visit) {
	ListQueue<BinNodePosi(Type)> Q;//辅助队列
	Q.enqueue(this);//根节点入队
	while (!Q.empty()) {//在队列再次变空之前，反复迭代
		BinNodePosi(Type) x = Q.dequeue();//取出首节点
		visit(x->data);
		if (HasLChild(*x))Q.enqueue(x->lc);//左孩子入队
		if (HasRChild(*x))Q.enqueue(x->rc);//右孩子入队
	}
}
template <typename Type> template <typename VST> void BinNode<Type>::travPre(VST& visit) {
	travPre_R(this, visit);
}
template <typename Type> template <typename VST> void BinNode<Type>::travIn(VST& visit) {
	travIn_R(this, visit);
}
template <typename Type> template <typename VST> void BinNode<Type>::travPost(VST& visit) {
	travPost_R(this, visit);
}