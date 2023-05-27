#include "QtCityMap.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCityMap w;
    w.show();
    return a.exec();
}
