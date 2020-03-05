#ifndef MYSTANDARDITEMMODEL_H
#define MYSTANDARDITEMMODEL_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
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

    bool read_q_stream(const QString& file_path);
    bool read_binary(const QString& file_path);
    bool export_q_stream(const QString& file_path, const QList<CountryPopulation>);
    bool export_binary(const QString& file_path, const QList<CountryPopulation>);
};

#endif // MYSTANDARDITEMMODEL_H
