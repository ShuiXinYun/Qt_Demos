#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    w.show();

    return a.exec();
}
