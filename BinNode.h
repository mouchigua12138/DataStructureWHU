#pragma once
#define BinNodePosi(Type) BinNode<Type>*//节点位置
#define stature(p) ((p) ? (p)->height : -1)//节点高度（与“空树高度为-1”的约定相统一）
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!((x).parent->lc))
#define IsRChild(x) (!((x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)-:parent->lc)//兄弟
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)//叔叔
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))//来自父亲的引用
#include <iostream>
typedef enum {
	RB_RED,
	RB_BLACK
}RBColor;//节点颜色
template <typename Type> struct BinNode{//二叉树节点模板
	Type data;//数值
	BinNodePosi(Type) parent;//父节点
	BinNodePosi(Type) lc;//左孩子节点
	BinNodePosi(Type) rc;//右孩子节点
	int height;//高度
	int npl;//Null Path Length
	RBColor color;//颜色（红黑树）
	BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED){}//默认构造器
	BinNode(Type e, BinNodePosi(Type) p = NULL, BinNodePosi(Type) lc = NULL, BinNodePosi(Type) rc = NULL,
		    int h = 0, int l = 1, RBColor c =RB_RED) : data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
	int size() {
		if (this == NULL)return 0;
		int size = 1 + this->lc->size() + this->rc->size();
		return size;
	}//统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(Type) insertAsLC(Type const& e);//作为当前节点的左孩子插入新节点
	BinNodePosi(Type) insertAsRC(Type const& e);//作为当前节点的右孩子插入新节点
	BinNodePosi(Type) succ();//取当前节点的直接后继
	template <typename VST> void travLevel(VST& visit);//子树层次遍历
	template <typename VST> void travPre(VST& visit);//子树先序遍历
	template <typename VST> void travIn(VST& visit);//子树中序遍历
	template <typename VST> void travPost(VST& visit);//子树后序遍历
	bool operator < (BinNode const& bn){
		return data < bn.data;
	}//小于
	bool operator > (BinNode const& bn) {
		return data > bn.data;
	}//大于
	bool operator = (BinNode const& bn) {
		return data == bn.data;
	}//等于
};
template <typename Type, typename VST> void travPre_R(BinNodePosi(Type) x, VST& visit) {
	if (!x)return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}
template <typename Type, typename VST> void travIn_R(BinNodePosi(Type) x, VST& visit) {
	if (!x)return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}
template <typename Type, typename VST> void travPost_R(BinNodePosi(Type) x, VST& visit) {
	if (!x)return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}