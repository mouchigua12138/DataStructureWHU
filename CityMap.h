#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "GraphMatrix.cpp"
struct City {
	std::string Country, CityName;
	double X, Y;
	City(std::string Country, std::string CityName, double X, double Y) {
		this->Country = Country;
		this->CityName = CityName;
		this->X = X;
		this->Y = Y;
	}
};
struct Table {
	int n;
	string cityName;
	Table(int n, string city) {
		this->n = n;
		this->cityName = city;
	}
};
void CreateCityGraph(Graph<City*, int>* Map, const char* CityFile, const char* EdgeFile);//读取文件
int SearchCityPositionInGraph(Graph<City*, int>* Map, string strCityName);//通过城市名查找图中节点编号
void DBPrint(Graph<City*, int>* Map);
Stack<City*> SearchRoadDijkstra(Graph<City*, int>* Map, int first, int last);
void PrintRoad(Stack<City*>& s);
void PrintRoadTime(Graph<City*, int>*Map, Stack<City*> s);
void ViewOnBaiduMap(Graph<City*, int>* Map, Stack<City*>& s);