#ifndef MYSTANDARDITEMMODEL_H
#define MYSTANDARDITEMMODEL_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include "countrypopulation.h"

namespace Ui {
class MyStandardItemModel;
}

class MyStandardItemModel : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyStandardItemModel(QWidget *parent = nullptr);
    ~MyStandardItemModel();

private slots:
    void on_btnInitialize_clicked();

    void on_btnRead_clicked();

    void on_btnAppend_clicked();

    void on_btnInsert_clicked();

    void on_btnDelete_clicked();

    void on_btnClear_clicked();

    void on_btnExport_clicked();

private:
    Ui::MyStandardItemModel *ui;
    QStandardItemModel* tableview_model;
};

#endif // MYSTANDARDITEMMODEL_H
