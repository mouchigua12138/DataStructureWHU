#include <fstream>
#include "Graph.h"
#include "ListQueue.cpp"
template <typename Tv, typename Te> void Graph<Tv, Te>::reset() {
	for (int i = 0; i < n; i++) {//对所有顶点
		status(i) = UNDISCOVERED;
		dTime(i) = fTime(i) = -1;
		parent(i) = -1;
		priority(i) = INT_MAX;
		for (int j = 0; j < n; j++)if (exists(i, j))type(i, j) = UNDETERMINED;//所有边的类型
	}
}
template <typename Tv, typename Te> void Graph<Tv, Te>::bfs(int s) {
	this->reset();
	int clock = 0;
	int v = s;//初始化
	do {
		if (status(v) == UNDISCOVERED)BFS(v, clock);//一旦遇到尚未发现的顶点即从该顶点出发启动一次	BFS
		v++;
		v = v % n;
	} while (s != v);//按序号检查,不重不漏
}
template <typename Tv, typename Te> void Graph<Tv, Te>::BFS(int v, int& clock) {
	ListQueue<int> Q;//引入辅助队列
	status(v) = DISCOVERED;
	Q.enqueue(v);//初始化起点
	while (!Q.empty()) {//在Q变空之前，不断
		int v = Q.dequeue();//取出队首顶点v
		dTime(v) = ++clock;
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {//枚举v的所有邻居u
			if (status(u) == UNDISCOVERED) {//若u尚未被发现，则
				status(u) = DISCOVERED;
				Q.enqueue(u);//发现该顶点
				type(v, u) = TREE;
				parent(u) = v;//引入树边拓展支撑树
			}
			else {//若u已被发现，或者甚至已访问完毕，则
				type(v, u) = CROSS;//将(v, u)归类与跨边
			}
		}
		status(v) = VISITED;//至此，当前顶点v访问完毕
	}
}
template <typename Tv, typename Te> void Graph<Tv, Te>::dfs(int s) {
	this->reset();
	int clock = 0;
	int v = s;//初始化
	do {
		if (status(v) == UNDISCOVERED)DFS(v, clock);//一旦遇到尚未发现的顶点即从该顶点出发启动一次DFS
		v++;
		v = v % n;
	} while (s != v);//按序号检查,不重不漏
}
template <typename Tv, typename Te> void Graph<Tv, Te>::DFS(int v, int& clock) {
	clock++;
	dTime(v) = clock;
	status(v) = DISCOVERED;//发现当前顶点v
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
		switch (status(u)) {
		case UNDISCOVERED://u尚未发现，意味着支撑树可在此拓展
			type(v, u) = TREE;
			parent(u) = v;
			DFS(u, clock);
			break;
		case DISCOVERED://u已被发现但尚未访问完毕，应属被后代指向的祖先
			type(v, u) = BACKWARD;
			break;
		default://u已访问完毕，则视承袭关系分为前向边或跨边
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED;
	clock++;
	fTime(v) = clock;//至此，当前顶点v访问完毕
}
template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
	this->reset();
	int v = s;//初始化
	do {
		if (status(v) == UNDISCOVERED)PFS(v, prioUpdater);
		v++;
		v = v % n;//从该顶点出发启动一次PFS
	} while (s != v);//按序号检查，不重不漏
}
template <typename Tv, typename Te> template <typename PU> void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
	priority(s) = 0;
	status(s) = VISITED;
	parent(s) = -1;//初始化，起点s加至PFS树中
	while (true) {//将下一顶点和边加至PFS树中
		for (int w = firstNbr(s); w > -1; w = nextNbr(s, w)) {//枚举s的所有邻居w
			prioUpdater(this, s, w);//更新顶点w的优先级及其父节点
		}
		for (int shortest = INT_MAX, w = 0; w < n; w++) {
			if (status(w) == UNDISCOVERED) {//从尚未加入遍历树的顶点中
				if (shortest > priority(w)) {//选出下一个
					shortest = priority(w);
					s = w;
				}//优先级最高的顶点s
			}
		}
		if (status(s) == VISITED)break;//直至所有顶点均已加入
		status(s) = VISITED;
		type(parent(s), s) = TREE;//将s及与其父的联边加入遍历树
	}
}
