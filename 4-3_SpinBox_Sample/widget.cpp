#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnCaculate_clicked()
{
    int num = ui->spinBox_number->value();
    double price = ui->DspinBoxPrice->value();
    double total = num*price;
//    QString total_str = QString::number(total,'g',2);
    QString total_str;
    total_str.setNum(total,'f',2);
    total_str.prepend("$ ");
    ui->lineEditTotal->setText(total_str);
}
