#include "ListNode.h"
template <typename Type> ListNodePosi(Type) ListNode<Type>::insertAsPred(Type const& e) {
	ListNodePosi(Type) x = new ListNode(e, pred, this);//创建新节点
	pred->succ = x;
	pred = x;//设置正向链接
	return x;//返回新节点位置
}
template <typename Type> ListNodePosi(Type) ListNode<Type>::insertAsSucc(Type const& e) {
	ListNodePosi(Type) x = new ListNode(e, this, succ);//创建新节点
	succ->pred = x;
	succ = x;//设置逆向链接
	return x;//返回新节点位置
}