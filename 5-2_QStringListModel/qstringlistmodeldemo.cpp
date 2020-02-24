#include "QStringListModelDemo.h"
#include "ui_QStringListModelDemo.h"

QStringListModelDemo::QStringListModelDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QStringListModelDemo)
{
    ui->setupUi(this);
    str_list_model = new QStringListModel();
    ui->listView->setModel(str_list_model);
}

QStringListModelDemo::~QStringListModelDemo()
{
    delete ui;
    delete str_list_model;
}

void QStringListModelDemo::on_btn_initialize_clicked()
{
    //read csv
    QString dir = QDir::currentPath();
    QString filter = "my data(*.mydata)";
    QString path = QFileDialog::getOpenFileName(this, "Select the mydata file", dir, filter);
    if(path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择国家-人口mydata文件!\nPlease select the country-population mydata file.");
        return;
    }
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return;
    }
    QTextStream txt_stream(&file);
    QStringList str_list;
    txt_stream.readLine();//去除表头
    while(!txt_stream.atEnd())
    {
        QString line_str = txt_stream.readLine();
        QStringList line_split = line_str.split(",");
        QString str_used = "";
        if(line_split.size() == 5)
        {
            str_used.append(line_split[1]).append(" population: ").append(line_split[2]).append(", percent: ").append(line_split[4]);
        }
        str_list.append(str_used);
    }
    str_list_model->setStringList(str_list);
    file.close();
}

void QStringListModelDemo::on_btn_append_clicked()
{
    str_list_model->insertRow(str_list_model->rowCount());
    QModelIndex index = str_list_model->index(str_list_model->rowCount()-1);
    str_list_model->setData(index, "append string");
    ui->listView->setCurrentIndex(index);
}

void QStringListModelDemo::on_btn_insert_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    str_list_model->insertRow(index.row());//此处通过index获取row
    str_list_model->setData(index, "inserted string");
    ui->listView->setCurrentIndex(index);
}

void QStringListModelDemo::on_btn_delete_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    str_list_model->removeRow(index.row());
}

void QStringListModelDemo::on_btn_clear_clicked()
{
    str_list_model->removeRows(0, str_list_model->rowCount());
}
