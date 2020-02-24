#include "QStringListModelDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    QStringListModelDemo w;
    w.show();

    return a.exec();
}
