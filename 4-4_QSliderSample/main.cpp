#include "coloredit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorEdit w;
    w.show();

    return a.exec();
}
