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
    QString file_path = QFileDialog::getOpenFileName(this, "Select the qdata file", dir, filter);
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
    QStringList file_format = {"QStream", "Binary"};
    bool ok = false;
    QString format = QInputDialog::getItem(this, "Select input file format", "Select file format:", file_format, 0, false, &ok);
    if(format == file_format[0] && ok)
    {
        QString file_path = QFileDialog::getOpenFileName(this, "Select country-population qdata file", QDir::currentPath(), "qdata file(*.qdata)");
        if(file_path.isEmpty())
        {
            return;
        }
        if(!read_q_stream(file_path))
        {
            QMessageBox::critical(this, "Error", "Read file error!");
            return;
        }
    }
    if(format == file_format[1] && ok)
    {
        QString file_path = QFileDialog::getOpenFileName(this, "Select country-population data file", QDir::currentPath(), "data file(*.data)");
        if(file_path.isEmpty())
        {
            return;
        }
        if(!read_binary(file_path))
        {
            QMessageBox::critical(this, "Error", "Read file error!");
            return;
        }
    }
}

bool MyStandardItemModel::read_q_stream(const QString& file_path)
{
    QList<CountryPopulation> cp_list;
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return false;
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
    return true;
}

bool MyStandardItemModel::read_binary(const QString& file_path)
{
    QList<CountryPopulation> cp_list;
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return false;
    }
    QDataStream data_stream(&file);
    data_stream.setByteOrder(QDataStream::LittleEndian);
    int row, column;
    data_stream.readRawData((char*)&row, sizeof(int));
    data_stream.readRawData((char*)&column, sizeof(int));
    QStringList title_str_list;
    for(int i = 0; i<column; ++i)
    {
        char* buf;
        unsigned int str_len;
        data_stream.readBytes(buf, str_len);
        QString str = QString::fromLocal8Bit(buf, str_len);
        title_str_list.append(str);
    }
//    qDebug()<<title_str_list;
    for(int i = 0; i<row; ++i)
    {
        int rank;

        char* country_name_buf;
        unsigned int country_name_length;

        long long population;

        char* date_buf;
        unsigned int date_length;

        double percent;

        data_stream.readRawData((char*)&rank, sizeof(rank));

        data_stream.readBytes(country_name_buf, country_name_length);
        QString country_name(QString::fromLocal8Bit(country_name_buf, country_name_length));

        data_stream.readRawData((char*)&population, sizeof(population));

        data_stream.readBytes(date_buf, date_length);
        QString date(QString::fromLocal8Bit(date_buf, date_length));

        data_stream.readRawData((char*)&percent, sizeof(percent));

        cp_list.append(CountryPopulation(rank, country_name, population, date, percent));
    }
    qDebug()<<cp_list.size();
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
    return true;
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
    if(!(row||column))
    {
        QMessageBox::warning(this, "Warning", "No data!");
        return;
    }
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

    QStringList file_format = {"QStream", "Binary"};
    bool ok = false;
    QString format = QInputDialog::getItem(this, "Select file format", "Select file format:", file_format, 0, false, &ok);
    if(format == file_format[0] && ok)
    {
        QString file_path = QFileDialog::getSaveFileName(this, "Set the save file name", QDir::currentPath(), "qdata(*.qdata)");
        if(file_path.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "请设置输出的qdata文件!\nPlease set the save file name.");
            return;
        }
        if(!export_q_stream(file_path, cp_list))
        {
            QMessageBox::critical(this, "Error", "Export file error");
            return;
        }
        QMessageBox::information(this, "Information", "Export file success");
    }
    if(format == file_format[1] && ok)
    {
        QString file_path = QFileDialog::getSaveFileName(this, "Set the save file name", QDir::currentPath(), "data(*.data)");
        if(file_path.isEmpty())
        {
//            QMessageBox::warning(this, "Warning", "请设置输出的data文件!\nPlease set the save file name.");
            return;
        }
        if(!export_binary(file_path, cp_list))
        {
            QMessageBox::critical(this, "Error", "Export file error");
            return;
        }
        QMessageBox::information(this, "Information", "Export file success");
    }
}


bool MyStandardItemModel::export_q_stream(const QString &file_path, const QList<CountryPopulation> cp_list)
{
    QFile file(file_path);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return false;
    }

    QStringList title_str_list;
    for(int i = 0; i<tableview_model->columnCount(); ++i)
    {
        title_str_list.append(tableview_model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
    }
//    qDebug()<<"title_string: "<<title_str_list;
    QDataStream data_stream(&file);
    data_stream<<title_str_list;
    for(int i = 0; i<cp_list.size(); ++i)
    {
        data_stream<<cp_list[i];
    }
    file.close();
    return true;
}

bool MyStandardItemModel::export_binary(const QString &file_path, const QList<CountryPopulation> cp_list)
{
    QFile file(file_path);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox::critical(this, "Error", "打开文件失败!\nOpen file error!");
        return false;
    }

    QStringList title_str_list;
    for(int i = 0; i<tableview_model->columnCount(); ++i)
    {
        title_str_list.append(tableview_model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString());
    }

    QDataStream data_binary_stream(&file);
    data_binary_stream.setByteOrder(QDataStream::LittleEndian);
    int row = tableview_model->rowCount();
    int column = tableview_model->columnCount();
    //写入行数和列数
    data_binary_stream.writeRawData((char*)&row, sizeof(int));
    data_binary_stream.writeRawData((char*)&column, sizeof(int));
    //写入表头
    for(int i = 0; i<title_str_list.size(); ++i)
    {
        QByteArray str_byte_array = title_str_list[i].toLocal8Bit();
        data_binary_stream.writeBytes(str_byte_array, str_byte_array.size());
    }
    for(int i = 0; i<cp_list.size(); ++i)
    {
        try
        {
            data_binary_stream.writeRawData((char *)&cp_list[i].rank, sizeof (cp_list[i].rank));
            data_binary_stream.writeBytes(cp_list[i].country_name.toLocal8Bit(), cp_list[i].country_name.toLocal8Bit().size());
            data_binary_stream.writeRawData((char *)&cp_list[i].population, sizeof (cp_list[i].population));
            data_binary_stream.writeBytes(cp_list[i].date.toLocal8Bit(), cp_list[i].date.toLocal8Bit().size());
            data_binary_stream.writeRawData((char *)&cp_list[i].percent, sizeof (cp_list[i].percent));
        }
        catch (...)
        {
            return false;
        }
    }
    file.close();
    return true;
}
