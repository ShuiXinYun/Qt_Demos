#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = QDir::currentPath();
    file_sys_model = new QFileSystemModel(this);
    file_sys_model->setRootPath(path);
    ui->treeView->setModel(file_sys_model);
    ui->treeView->setRootIndex(file_sys_model->index(path));
    ui->tableView->setModel(file_sys_model);
    ui->tableView->setRootIndex(file_sys_model->index(path));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->listView->setModel(file_sys_model);
    ui->listView->setRootIndex(file_sys_model->index(path));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete file_sys_model;
}

void MainWindow::on_btnOpenFolder_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Select a folder");

    if(path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择一个文件夹!\nPlease select a folder!");
        return;
    }
    else
    {
        QString text = "Folder: ";
        text.append(path);
        ui->label_path->setText(text);
        file_sys_model->setRootPath(path);
        qDebug()<<"file_sys_model root path:"<<file_sys_model->rootPath();
        ui->treeView->setRootIndex(file_sys_model->index(path));//设置treeView根节点为选定的目录
        ui->tableView->setRootIndex(file_sys_model->index(path));
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->listView->setRootIndex(file_sys_model->index(path));
    }
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->tableView->setRootIndex(index);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->listView->setRootIndex(index);

    if(file_sys_model->isDir(index))
    {
        ui->label_file_folder->setText(file_sys_model->filePath(index).prepend("Folder: "));
        ui->label_size->setText("...");
    }
    else
    {
        ui->label_file_folder->setText(file_sys_model->filePath(index).prepend("File: "));
        QString type_size = file_sys_model->type(index).prepend("File type: ");
        double size = file_sys_model->size(index)/1024.0;
        if(size < 1024)
        {
            type_size.append(", file size: ").append(QString::asprintf("%.1f KB.", size));
        }
        else
        {
            type_size.append(", file size: ").append(QString::asprintf("%.1f MB.", size/1024.0));
        }
        ui->label_size->setText(type_size);
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if(!file_sys_model->isDir(index))
    {
        QDesktopServices::openUrl(QUrl(file_sys_model->filePath(index)));//listView item双击事件, 调用系统程序打开文件
    }
}
