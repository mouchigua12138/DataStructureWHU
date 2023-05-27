#pragma once
#include <iostream>
#include "Graph.cpp"
#include "Stack.cpp"
template <typename Tv> struct Vertex {
	Tv data;//数据
	int inDegree, outDegree;//入度，出度
	VStatus status;//状态
	int dTime, fTime;//时间标签
	int parent;//在遍历树中的父节点
	int priority;//在遍历树中的优先级数
	Vertex(Tv const& d = (Tv)0) : data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		                          dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};
template <typename Te> struct Edge {
	Te data;//数据
	double weight;//权重
	EType type;//类型
	Edge(Te const& d, double w) : data(d), weight(w), type(UNDETERMINED){}
};
template <typename Tv, typename Te> class GraphMatrix : public Graph<Tv, Te>{//顶点类型，边类型
private:
	Vector<Vertex<Tv>> V;//顶点集（向量）
	Vector<Vector<Edge<Te>*>> E;//边集（邻接矩阵）
public:
	GraphMatrix();//构造函数
	~GraphMatrix();//析构函数
	virtual Tv& vertex(int i);//数据
	virtual int inDegree(int i);//入度
	virtual int outDegree(int i);//出度
	virtual int firstNbr(int i);//首个邻接节点
	virtual int nextNbr(int i, int j);//相对于顶点j的下一个邻接顶点
	virtual VStatus& status(int i);//状态
	virtual int& dTime(int i);//时间标签dTime
	virtual int& fTime(int i);//时间标签fTime
	virtual int& parent(int i);//在遍历树中的父亲
	virtual int& priority(int i);//在遍历树中的优先级数
	virtual int insert(Tv const& vertex);//插入顶点，返回编号
	virtual Tv remove(int i);//删除第i个顶点及其关联边
	virtual bool exists(int i, int j);//边(i, j)是否存在
	virtual EType& type(int i, int j);//边(i, j)的类型
	virtual Te& edge(int i, int j);//边(i, j)的数据
	virtual double& weight(int i, int j);//边(i, j)的权重
	virtual void insert(Te const& edge, double w, int i, int j);//插入权重为w的边e = (i, j)
	virtual Te remove(int i, int j);//删除顶点i和j之间的边
};