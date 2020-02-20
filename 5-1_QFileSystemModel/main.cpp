#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    auto codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
