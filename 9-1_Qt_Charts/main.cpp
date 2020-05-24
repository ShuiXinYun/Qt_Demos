#include "qt_charts.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_Charts w;
    w.show();

    return a.exec();
}
