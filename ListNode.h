#pragma once
#define ListNodePosi(Type) ListNode<Type>*//列表节点位置
#include <iostream>
typedef int Rank;//秩
template <typename Type> struct ListNode {
	Type data;//数值
	ListNodePosi(Type) pred;//前驱
	ListNodePosi(Type) succ;//后继
	ListNode(){}//针对header和trailer的构造
	ListNode(Type e, ListNodePosi(Type) p = NULL, ListNodePosi(Type) s = NULL) : data(e), pred(p), succ(s){}//默认构造器
	ListNodePosi(Type) insertAsPred(Type const& e);//紧靠当前节点之前插入新节点
	ListNodePosi(Type) insertAsSucc(Type const& e);//紧靠当前节点之后插入新节点
};