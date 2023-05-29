#include "GraphMatrix.h"
#include "Tools.h"
template <typename Tv, typename Te> GraphMatrix<Tv, Te>::GraphMatrix() {
	this->n = 0;
	this->e = 0;
}
template <typename Tv, typename Te> GraphMatrix<Tv, Te>::~GraphMatrix() {
	for (int j = 0; j < this->n; j++) {//所有动态创建的
		for (int k = 0; k < this->n; k++) {//边记录
			delete E[j][k];//逐条删除
		}
	}
	string name = typeid(Tv).name();
	if (SearchString(name, '*') != -1) {
		for (int i = 0; i < this->n; i++) {
			delete V[i].data;
		}//释放City*的内存
	}
}
template <typename Tv, typename Te> Tv& GraphMatrix<Tv, Te>::vertex(int i) {
	return V[i].data;
}
template <typename Tv, typename Te> int GraphMatrix<Tv, Te>::inDegree(int i) {
	return V[i].inDegree;
}
template <typename Tv, typename Te> int GraphMatrix<Tv, Te>::outDegree(int i) {
	return V[i].outDegree;
}
template <typename Tv, typename Te> int GraphMatrix<Tv, Te>::firstNbr(int i) {
	return this->nextNbr(i, this->n);
}
template <typename Tv, typename Te> int GraphMatrix<Tv, Te>::nextNbr(int i, int j) {
	do { j--; }
	while ((j > -1) && (!exists(i, j)));//逆向线性试探
	return j;
}
template <typename Tv, typename Te> VStatus& GraphMatrix<Tv, Te>::status(int i) {
	return V[i].status;
}
template <typename Tv, typename Te> int& GraphMatrix<Tv, Te>::dTime(int i) {
	return V[i].dTime;
}
template <typename Tv, typename Te> int& GraphMatrix<Tv, Te>::fTime(int i) {
	return V[i].fTime;
}
template <typename Tv, typename Te> int& GraphMatrix<Tv, Te>::parent(int i) {
	return V[i].parent;
}
template <typename Tv, typename Te> int& GraphMatrix<Tv, Te>::priority(int i) {
	return V[i].priority;
}
template <typename Tv, typename Te> int GraphMatrix<Tv, Te>::insert(Tv const& vertex) {
	for (int j = 0; j < this->n; j++)E[j].insert(NULL);//各顶点预留一条潜在的关联边
	this->n++;
	E.insert(Vector<Edge<Te>*>(this->n, this->n, (Edge<Te>*)NULL));//创建新顶点对应的边向量
	return V.insert(Vertex<Tv>(vertex));//顶点向量增加一个顶点
}
template <typename Tv, typename Te> Tv GraphMatrix<Tv, Te>::remove(int i) {
	for (int j = 0; j < this->n; j++) {//所有出边
		if (exists(i, j)) {
			delete E[i][j];
			V[j].inDegree--;
		}//逐一删除
	}
	E.remove(i);//删除第i行
	this->n--;
	Tv vBak = vertex(i);
	V.remove(i);//删除顶点i
	for (int j = 0; j < this->n; j++) {//所有入边
		if (Edge<Te>* e = E[j].remove(i)) {
			delete e;
			V[i].outDegree--;
		}//逐一删除
	}
	return vBak;//返回被删除顶点的信息
}
template <typename Tv, typename Te> bool GraphMatrix<Tv, Te>::exists(int i, int j) {
	return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != NULL;
}
template <typename Tv, typename Te> EType& GraphMatrix<Tv, Te>::type(int i, int j) {
	return E[i][j]->type;
}
template <typename Tv, typename Te> Te& GraphMatrix<Tv, Te>::edge(int i, int j) {
	return E[i][j]->data;
}
template <typename Tv, typename Te> double& GraphMatrix<Tv, Te>::weight(int i, int j) {
	return E[i][j]->weight;
}
template <typename Tv, typename Te> void GraphMatrix<Tv, Te>::insert(Te const& edge, double w, int i, int j) {
	if (exists(i, j))return;//确保该边不存在
	E[i][j] = new Edge<Te>(edge, w);//创建新边
	this->e++;
	V[i].outDegree++;
	V[j].inDegree++;//更新数据
}
template <typename Tv, typename Te> Te GraphMatrix<Tv, Te>::remove(int i, int j) {
	Te eBak = edge(i, j);//备份
	delete E[i][i];//删除记录
	E[i][j] = NULL;
	this->e--;
	V[i].outDegree--;
	V[j].inDegree--;
	return eBak;//返回备份
}
