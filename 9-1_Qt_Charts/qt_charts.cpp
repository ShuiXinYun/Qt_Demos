#include "qt_charts.h"
#include "ui_qt_charts.h"

Qt_Charts::Qt_Charts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_Charts)
{
    ui->setupUi(this);
}

Qt_Charts::~Qt_Charts()
{
    delete ui;
}
