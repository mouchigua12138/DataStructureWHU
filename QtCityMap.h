#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_QtCityMap.h"

#include "CityMap.h"

class QtCityMap : public QMainWindow
{
    Q_OBJECT

public:
    QtCityMap(QWidget *parent = Q_NULLPTR);

    ~QtCityMap();
private slots:
    void DBPrintOnEdit();
    void DijkstraPrint();
private:
    Ui::QtCityMapClass ui;

    Graph<City*, int>* map;
};
