#include "mystandarditemmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyStandardItemModel w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    w.show();

    return a.exec();
}
