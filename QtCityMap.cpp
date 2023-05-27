#include <QMessageBox>
#include <QWebEngineSettings>
#include "QtCityMap.h"

QtCityMap::QtCityMap(QWidget *parent)
    : QMainWindow(parent)
{
    map = new GraphMatrix<City*, int>;
    CreateCityGraph(map, "cities.csv", "routes.csv");
    
    ui.setupUi(this);

    QString strDir = QCoreApplication::applicationDirPath();
    if (strDir.endsWith("Debug"))strDir.chop(10);
    else if (strDir.endsWith("Release"))strDir.chop(12);
    QWebEngineSettings* setting = ui.webEngineView->settings();
    //ui.webEngineView->load(QUrl("file:///D:/graph.htm"));
    setting->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    ui.webEngineView->load(QUrl("file:///" + strDir + "/QtCityMap/graph.htm"));
    ui.webEngineView->show();
}

QtCityMap::~QtCityMap() {
    if (!map)delete map;
}

void QtCityMap::DBPrintOnEdit() {
    QString strCity = ui.lineEdit->text();
    string cityName = strCity.toStdString();
    int nPosition = SearchCityPositionInGraph(map, cityName);

    if(nPosition == -1){
        QMessageBox::information(NULL, "提示", "未找到该城市", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui.lineEdit_2->setText("NULL");
        ui.lineEdit_3->setText("NULL");
        return;
    }

    map->dfs(nPosition);
    Vector<Table*> v;
    for (int i = 0; i < map->n; i++) {
        v.insert(new Table(map->dTime(i), map->vertex(i)->CityName));
    }//建立查询表
    for (int i = 0; i < map->n; i++) {
        for (int j = 0; j < map->n - 1; j++) {
            if (v[i]->n < v[j]->n) {
                Table temp = *v[i];
                *v[i] = *v[j];
                *v[j] = temp;
            }
        }
    }//排序
    QString strDFS;
    for (int i = 0; i < map->n; i++) {
        strDFS += v[i]->cityName + "  ";
    }//输出
    ui.lineEdit_2->setText(strDFS);

    map->bfs(nPosition);
    Vector<Table*> V;
    for (int i = 0; i < map->n; i++) {
        V.insert(new Table(map->dTime(i), map->vertex(i)->CityName));
    }//建立查询表
    for (int i = 0; i < map->n; i++) {
        for (int j = 0; j < map->n - 1; j++) {
            if (V[i]->n < V[j]->n) {
                Table temp = *V[i];
                *V[i] = *V[j];
                *V[j] = temp;
            }
        }
    }//排序
    QString strBFS;
    for (int i = 0; i < map->n; i++) {
        strBFS += V[i]->cityName + "  ";
    }//输出
    ui.lineEdit_3->setText(strBFS);
}

void QtCityMap::DijkstraPrint() {
    QString firstCity = ui.lineEdit_4->text();
    string  strFirst  = firstCity.toStdString();
    QString lastCity  = ui.lineEdit_5->text();
    string  strLast   = lastCity.toStdString();

    int nFirst = SearchCityPositionInGraph(map, strFirst);
    int nLast  = SearchCityPositionInGraph(map, strLast);
    
    if (nFirst == -1 && nLast == -1) {
        QMessageBox::information(NULL, "提示", "起点与终点均不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui.lineEdit_6->setText("-1");
        return;
    }
    else if (nFirst == -1) {
        QMessageBox::information(NULL, "提示", "起点不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui.lineEdit_6->setText("-1");
        return;
    }
    else if (nLast == -1) {
        QMessageBox::information(NULL, "提示", "终点不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui.lineEdit_6->setText("-1");
        return;
    }

    Stack<City*> s = SearchRoadDijkstra(map, nFirst, nLast);

    if (s.empty()) {
        QMessageBox::information(NULL, "提示", "两地之间不存在路径", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui.lineEdit_6->setText("-1");
        return;
    }

    double ans = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        int last  = SearchCityPositionInGraph(map, s[i]->CityName);
        int first = SearchCityPositionInGraph(map, s[i + 1]->CityName);
        ans += map->weight(first, last);
    }

    QString Ans = QString::number(ans, 'f', 2);
    ui.lineEdit_6->setText(Ans);

    ViewOnBaiduMap(map, s);

    QString strDir = QCoreApplication::applicationDirPath();
    if (strDir.endsWith("Debug"))strDir.chop(10);
    else if (strDir.endsWith("Release"))strDir.chop(12);
    ui.webEngineView->load(QUrl("file:///" + strDir + "/QtCityMap/graph.htm"));
    ui.webEngineView->show();
}