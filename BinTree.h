#pragma once
#include "BinNode.cpp"
template <typename Type> class BinTree {
protected:
	int _size;//规模
	BinNodePosi(Type) _root;//根节点
	virtual int updateHeight(BinNodePosi(Type) x);//更新节点x的高度
	void updateHeightAbove(BinNodePosi(Type) x);//更新节点x及其祖先的高度
public:
	BinTree();//构造函数
	~BinTree();//析构函数
	int size() const;//规模
	bool empty() const;//判空
	BinNodePosi(Type) root() const;//树根
	BinNodePosi(Type) insertAsRoot(Type const& e);//插入根节点
	BinNodePosi(Type) insertAsLC(BinNodePosi(Type) x, Type const& e);//e作为x的左孩子插入
	BinNodePosi(Type) insertAsRC(BinNodePosi(Type) x, Type const& e);//e作为x的右孩子插入
	BinNodePosi(Type) attachAsLC(BinNodePosi(Type) x, BinTree<Type>*& S);//T作为x的左子树插入
	BinNodePosi(Type) attachAsRC(BinNodePosi(Type) x, BinTree<Type>*& S);//T作为x的右子树插入
	int remove(BinNodePosi(Type) x);//删除以x处节点为根的子树，返回该子树原先的规模
	BinTree<Type>* secede(BinNodePosi(Type) x);//将子树x从当前树中摘除，并将其转换为一棵独立子树
	template <typename VST> void travLevel(VST& visit);//层次遍历
	template <typename VST> void travPre(VST& visit);//先序遍历
	template <typename VST> void travIn(VST& visit);//中序遍历
	template <typename VST> void travPost(VST& visit);//后序遍历
	bool operator < (BinTree<Type> const& t);
	bool operator > (BinTree<Type> const& t);
	bool operator == (BinTree<Type> const& t);
};
template <typename Type> static int removeAt(BinNodePosi(Type) x);