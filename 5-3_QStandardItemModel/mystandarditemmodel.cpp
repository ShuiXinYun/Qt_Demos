#include "mystandarditemmodel.h"
#include "ui_mystandarditemmodel.h"

MyStandardItemModel::MyStandardItemModel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyStandardItemModel)
{
    ui->setupUi(this);
    tableview_model = new QStandardItemModel();
}

MyStandardItemModel::~MyStandardItemModel()
{
    delete ui;
    delete tableview_model;
}

void MyStandardItemModel::on_btnInitialize_clicked()
{
    //read csv
    QList<CountryPopulation> cp_list;
    QString dir = QDir::currentPath();
    QString filter = "csv(*.csv)";
    QString file_path = QFileDialog::getOpenFileName(this, "Select the mydata file", dir, filter);
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择国家-人口csv文件!\nPlease select the country-population csv file.");
        return;
    }
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return;
    }
    QTextStream txt_stream(&file);
    QStringList str_list;
    QStringList title_str_list = txt_stream.readLine().split(",");//去除表头
    if(title_str_list.size() != 5)
    {
        QMessageBox::critical(this, "Error", "文件格式错误!\nFile format error!");
    }
    while(!txt_stream.atEnd())
    {
        QString line_str = txt_stream.readLine();
        QStringList line_split = line_str.split(",");
        if(line_split.size() == title_str_list.size())
        {
            CountryPopulation cp(line_split[0].toInt(), line_split[1], line_split[2].toLongLong(), line_split[3], line_split[4].toDouble());
            cp_list.append(cp);
        }
    }
//    tableview_model->setRowCount(cp_list.size());
//    tableview_model->setColumnCount(title_str_list.size());
    qDebug()<<"cp_list size:"<<cp_list.size();
    for(int r = 0; r<cp_list.size(); ++r)
    {
        for(int c = 0; c<title_str_list.size(); ++c)
        {
            QStandardItem *item;
            switch (c){
                case 0:
                    item = new QStandardItem(QString::number(cp_list[r].rank));
                    break;
                case 1:
                    item = new QStandardItem(cp_list[r].country_name);
                    break;
                case 2:
                    item = new QStandardItem(QString::number(cp_list[r].population));
                    break;
                case 3:
                    item = new QStandardItem(cp_list[r].date);
                    break;
                case 4:
                    item = new QStandardItem(QString::number(cp_list[r].percent, 'g', 4));
                    break;
                default:
                    break;
            }
            tableview_model->setItem(r,c,item);
        }
    }
    tableview_model->setHorizontalHeaderLabels(title_str_list);
    ui->tableView->setModel(tableview_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    file.close();
}

void MyStandardItemModel::on_btnRead_clicked()
{
    tableview_model->removeRows(0, tableview_model->rowCount());
    QList<CountryPopulation> cp_list;
    QString file_path = QFileDialog::getOpenFileName(this, "Select country-population mydata file", QDir::currentPath(), "mydata file(*.mydata)");
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择国家-人口mydata文件!\nPlease select the country-population mydata file.");
        return;
    }
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return;
    }
    QDataStream data_stream(&file);
    QStringList title_str_list;
    data_stream>>title_str_list;
    while(!data_stream.atEnd())
    {
        CountryPopulation cp;
        data_stream>>cp;
        cp_list.append(cp);
    }
    for(int r = 0; r<cp_list.size(); ++r)
    {
        for(int c = 0; c<title_str_list.size(); ++c)
        {
            QStandardItem *item;
            switch (c){
                case 0:
                    item = new QStandardItem(QString::number(cp_list[r].rank));
                    break;
                case 1:
                    item = new QStandardItem(cp_list[r].country_name);
                    break;
                case 2:
                    item = new QStandardItem(QString::number(cp_list[r].population));
                    break;
                case 3:
                    item = new QStandardItem(cp_list[r].date);
                    break;
                case 4:
                    item = new QStandardItem(QString::number(cp_list[r].percent, 'g', 4));
                    break;
                default:
                    break;
            }
            tableview_model->setItem(r,c,item);
        }
    }
    tableview_model->setHorizontalHeaderLabels(title_str_list);
    ui->tableView->setModel(tableview_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    file.close();
}

void MyStandardItemModel::on_btnAppend_clicked()
{
    tableview_model->insertRow(tableview_model->rowCount());
    QModelIndex index = tableview_model->index(tableview_model->rowCount()-1,0);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void MyStandardItemModel::on_btnInsert_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    qDebug()<<"the row: "<<index.row();
    tableview_model->insertRow(index.row());
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void MyStandardItemModel::on_btnDelete_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    tableview_model->removeRow(index.row());
}

void MyStandardItemModel::on_btnClear_clicked()
{
    tableview_model->removeRows(0, tableview_model->rowCount());
}

void MyStandardItemModel::on_btnExport_clicked()
{
    int row = tableview_model->rowCount();
    int column = tableview_model->columnCount();
    QList<CountryPopulation> cp_list;
    for(int r = 0; r<row; ++r)
    {
        CountryPopulation cp;
        for(int c = 0; c<column; ++c)
        {
            switch (c) {
            case 0:
                cp.rank = tableview_model->item(r, c)->text().toInt();
                break;
            case 1:
                cp.country_name = tableview_model->item(r, c)->text();
                break;
            case 2:
                cp.population = tableview_model->item(r, c)->text().toLongLong();
                break;
            case 3:
                cp.date = tableview_model->item(r, c)->text();
                break;
            case 4:
                cp.percent = tableview_model->item(r, c)->text().toDouble();
                break;
            default:
                break;
            }
        }
        cp_list.append(cp);
    }

    QString dir = QDir::currentPath();
    QString filter = "mydata(*.mydata)";
    QString file_path = QFileDialog::getSaveFileName(this, "Set the save file name", dir, filter);
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请设置输出的mydata文件!\nPlease set the save file name.");
        return;
    }

    QFile file(file_path);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return;
    }

    QStringList title_str_list;
    for(int i = 0; i<HEADERSIZE; ++i)
    {
        title_str_list.append(tableview_model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
    }
    qDebug()<<"title_string: "<<title_str_list;
    QDataStream data_stream(&file);
    data_stream<<title_str_list;
    for(int i = 0; i<cp_list.size(); ++i)
    {
        data_stream<<cp_list[i];
    }
    file.close();
}
