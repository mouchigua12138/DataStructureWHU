#pragma once
#include <iostream>
#include <string>
typedef enum { UNDISCOVERED, DISCOVERED, VISITED }VStatus;//顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD }EType;//边在遍历树中所属的类型
template <typename Tv, typename Te> class Graph{
private:
	void reset();//重置图顶点和边的信息
	void BFS(int, int&);//（连通域）广度优先遍历算法
	void DFS(int, int&);//（连通域）深度优先遍历算法
	template <typename PU> void PFS(int, PU);//（连通域）优先级搜索框架
public:
	virtual ~Graph(){}//使用虚函数继承的特性释放内存
	int n;//顶点总数
	virtual int insert(Tv const&) = 0;//插入顶点，返回编号
	virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点信息
	virtual Tv& vertex(int) = 0;//顶点v的数据（顶点v的确存在）
	virtual int inDegree(int) = 0;//顶点v的出度（顶点v的确存在）
	virtual int outDegree(int) = 0;//顶点v的入度（顶点v的确存在）
	virtual int firstNbr(int) = 0;//顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0;//顶点v相对于顶点j的下一个邻接顶点
	virtual VStatus& status(int) = 0;//顶点v的状态
	virtual int& dTime(int) = 0;//顶点v的时间标签dTime
	virtual int& fTime(int) = 0;//顶点v的时间标签fTime
	virtual int& parent(int) = 0;//顶点v在遍历树中的父亲
	virtual int& priority(int) = 0;//顶点v在遍历树中的优先级数
	int e;//边总数
	virtual bool exists(int, int) = 0;//边(v, u)是否存在
	virtual void insert(Te const&, double, int, int) = 0;//在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0;//删除顶点v和u之间的边e,返回该边信息
	virtual EType& type(int, int) = 0;//边(v, u)的类型
	virtual Te& edge(int, int) = 0;//边(v, u)的数据（该边的确存在）
	virtual double& weight(int, int) = 0;//边(v, u)的权重
	void bfs(int);//广度优先遍历算法
	void dfs(int);//深度优先遍历算法
	template <typename PU> void pfs(int, PU);//优先级搜索框架
};

template <typename Tv, typename Te> struct PrimPU {//针对Prim算法的优先级更新器
	virtual void operator () (Graph<Tv, Te>* g, int uk, int v) {
		if (g->status(v) == UNDISCOVERED) {//对于uk每一尚未被发现的邻接顶点v
			if (g->priority(v) > g->weight(uk, v)) {//按Prim策略做松弛
				g->priority(v) = g->weight(uk, v);//更新优先级
				g->parent(v) = uk;//更新父节点
			}
		}
	}
};
template <typename Tv, typename Te> struct DijkstraPU {//针对Dijkstra算法的优先级更新器
	virtual void operator () (Graph<Tv, Te>* g, int uk, int v) {
		if (g->status(v) == UNDISCOVERED) {//对于uk每一尚未被发现的邻接顶点v，按Dijkstra策略
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {//做松弛
				g->priority(v) = g->priority(uk) + g->weight(uk, v);//更新优先级
				g->parent(v) = uk;//更新父节点
			}
		}
	}
};