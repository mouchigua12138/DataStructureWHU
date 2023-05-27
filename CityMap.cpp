#include <QMessageBox>
#include "CityMap.h"
void CreateCityGraph(Graph<City*, int>* Map, const char* CityFile, const char* EdgeFile) {
	std::ifstream cityIn, edgeIn;
	cityIn.open(CityFile, std::ios::in);//打开城市表
	if (!cityIn.is_open()) {
		std::cout << "文件未正确打开";
		exit(0);
	}//检查文件是否正常打开

	edgeIn.open(EdgeFile, std::ios::in);//打开路径表
	if (!edgeIn.is_open()) {
		std::cout << "文件未正确打开";
		exit(0);
	}//检查文件是否正常打开

	Vector<Table*> v;
	for (; cityIn.peek() != EOF;) {
		std::string Country, CityName;
		double X, Y;
		char elem;
		for (elem = cityIn.get(); elem != ','; elem = cityIn.get()) {
			Country.push_back(elem);
		}//读入Country
		for (elem = cityIn.get(); elem != ','; elem = cityIn.get()) {
			CityName.push_back(elem);
		}//读入CityName
		cityIn >> X;//读入X
		char trash = cityIn.get();//处理','
		cityIn >> Y;//读入Y
		trash = cityIn.get();//处理'\n'
		City* city = new City(Country, CityName, X, Y);
		int num = Map->insert(city);
		v.insert(new Table(num, CityName));//建立字典向量，便于查找
	}//读入节点
	cityIn.close();//关闭文件

	for (; edgeIn.peek() != EOF;) {
		std::string City1, City2, Transportation, Information;
		int nCity1, nCity2;
		double weight, cost;
		char elem;
		for (elem = edgeIn.get(); elem != ','; elem = edgeIn.get()) {
			City1.push_back(elem);
		}//读入City1
		for (int i = 0; i < v.size(); i++) {
			Table* t = v[i];
			if (t->cityName == City1) {
				nCity1 = t->n;
				break;
			}
		}//遍历向量v查找City2的序号
		for (elem = edgeIn.get(); elem != ','; elem = edgeIn.get()) {
			City2.push_back(elem);
		}//读入City2
		for (int i = 0; i < v.size(); i++) {
			Table* t = v[i];
			if (t->cityName == City2) {
				nCity2 = t->n;
				break;
			}
		}//遍历向量v查找City2的序号
		for (elem = edgeIn.get(); elem != ','; elem = edgeIn.get()) {
			Transportation.push_back(elem);
		}//读入Transportation
		edgeIn >> weight;
		char trash = edgeIn.get();
		edgeIn >> cost;
		trash = edgeIn.get();
		for (elem = edgeIn.get(); elem != '\n'; elem = edgeIn.get()) {
			Information.push_back(elem);
		}//读入Information

		if (Map->exists(nCity1, nCity2)) {//如果边(nCity1, nCity2)已存在
			double OriginWeight = Map->weight(nCity1, nCity2);
			if (OriginWeight > weight) {//如果新边的权值更小
				Map->remove(nCity1, nCity2);//删除原边
				Map->insert(0, weight, nCity1, nCity2);//插入权值更小的新边
			}
		}
		else {//如果边(nCity1, nCity2)不存在
			Map->insert(0, weight, nCity1, nCity2);//创建权值为weight的边(nCity1, nCity2)
		}
	}
	edgeIn.close();//关闭文件
}
int SearchCityPositionInGraph(Graph<City*, int>* Map, string strCityName) {
	for (int i = 0; i < Map->n; i++) {
		if (Map->vertex(i)->CityName == strCityName)return i;
	}
	return -1;
}
void DBPrint(Graph<City*, int>* Map) {
	Vector<Table*> v;
	for (int i = 0; i < Map->n; i++) {
		v.insert(new Table(Map->dTime(i), Map->vertex(i)->CityName));
	}//建立查询表
	for (int i = 0; i < Map->n; i++) {
		for (int j = 0; j < Map->n - 1; j++) {
			if (v[i]->n < v[j]->n) {
				Table temp = *v[i];
				*v[i] = *v[j];
				*v[j] = temp;
			}
		}
	}//排序
	for (int i = 0; i < Map->n; i++) {
		cout << v[i]->cityName << endl;	
	}//输出
}
Stack<City*> SearchRoadDijkstra(Graph<City*, int>* Map, int first, int last) {
	Stack<City*> v;
	DijkstraPU<City*, int> dijkstra;
	Map->pfs(first, dijkstra);//对Map进行Dijkstra算法
	int i;
	for (i = last; i != first && i != -1; i = Map->parent(i)) {
		v.push(Map->vertex(i));
	}
	if (i == -1) {
		v.remove(0, v.size());
		return v;
	}//如果分别在两个连通分量上
	v.push(Map->vertex(first));
	return v;
}
void PrintRoad(Stack<City*>& s) {
	while (!s.empty()) {
		cout << s.pop()->CityName << endl;
	}
}

void PrintRoadTime(Graph<City*, int>* Map, Stack<City*> s) {

	if (s.empty()) {
		cout << "两地之间不存在路径！";
		return;
	}

	double ans = 0;
	for (int i = 0; i < s.size() - 1; i++) {
		int last = SearchCityPositionInGraph(Map, s[i]->CityName);
		int first = SearchCityPositionInGraph(Map, s[i + 1]->CityName);
		ans += Map->weight(first, last);
	}
	
	cout << "从" << s[s.size() - 1]->CityName << "到" << s[0]->CityName << "的最短路径如下所示：\n";
	PrintRoad(s);
	cout << "该路径共计用时" << ans << "小时\n";
}

void ViewOnBaiduMap(Graph<City*, int>* Map, Stack<City*>& s) {

	ofstream fileOut;
	fileOut.open("graph.htm", ios::out | ios::binary);

	if (!fileOut.is_open()) {
		cout << "百度地图网页打开失败！";
		return;
	}

	fileOut << "<!DOCTYPE html><html><head><style type='text/css'>body, html{width: 100%;height: 100%;margin:0;font-family:'微软雅黑';}#allmap{height:100%;width:100%;}#r-result{width:100%;}</style>\
                <script type='text/javascript' src='http://api.map.baidu.com/api?v=2.0&ak=nSxiPohfziUaCuONe4ViUP2N'></script>\
                <title>Shortest path</title></head><body><div id='allmap'></div></div></body></html><script type='text/javascript'>\
                var map = new BMap.Map('allmap');var point = new BMap.Point(0, 0);map.centerAndZoom(point, 2);map.enableScrollWheelZoom(true);";//生成空白地图
	
	if (s.empty()) {
		fileOut << "</script>";//网页文件尾
		fileOut.close();
		return;//无最短路径时返回空地图
	}

	int nCount = 1;//变量命名
	City* CityFirst;
	City* CityNext;
	CityFirst = s.pop();//初始化栈类读取

	fileOut << "var marker0 = new BMap.Marker(new BMap.Point(" << CityFirst->Y << ", " << CityFirst->X << "));map.addOverlay(marker0);";
	fileOut << "var infoWindow0 = new BMap.InfoWindow(\" <p style = 'font-size:14px;'> ";
	fileOut << "country: " << CityFirst->Country;
	fileOut << "<br / >city : " << CityFirst->CityName << "</p>\"); ";
	fileOut << "marker0.addEventListener(\"click\", function(){this.openInfoWindow(infoWindow0); }); ";

	while (!s.empty()) {//当栈类非空时
		CityNext = s.pop();
		fileOut << "var marker" << nCount << " = new BMap.Marker(new BMap.Point(" << CityNext->Y << ", " << CityNext->X << "));map.addOverlay(marker" << nCount << ");";
		fileOut << "var infoWindow" << nCount << " = new BMap.InfoWindow(\" <p style = 'font-size:14px;'>";
		fileOut << "country: " << CityNext->Country;
		fileOut << "<br / >city : " << CityNext->CityName << "</p>\"); ";
		fileOut << "marker" << nCount << ".addEventListener(\"click\", function(){this.openInfoWindow(infoWindow" << nCount << "); }); ";
		fileOut << "var path" << nCount << " = new BMap.Polyline([";
		fileOut << "new BMap.Point(" << CityFirst->Y << ", " << CityFirst->X << "),";
		fileOut << "new BMap.Point(" << CityNext->Y << ", " << CityNext->X << ")],";
		fileOut << " {strokeColor:'#18a45b', strokeWeight : 8, strokeOpacity : 0.8}); ";
		fileOut << "map.addOverlay(path" << nCount << ");";
		CityFirst = CityNext;
		nCount++;//通过更新nCount的数值实现对JavaScript语句中不同变量实现不同铭名
	}

	fileOut << "</script>";//网页文件尾
	fileOut.close();
}