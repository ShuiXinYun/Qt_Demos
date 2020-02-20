#ifndef QSTINGLISTMODELDEMO_H
#define QSTINGLISTMODELDEMO_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class QStingListModelDemo;
}

class QStingListModelDemo : public QWidget
{
    Q_OBJECT

public:
    explicit QStingListModelDemo(QWidget *parent = nullptr);
    ~QStingListModelDemo();

private slots:
    void on_btn_initialize_clicked();

    void on_btn_append_clicked();

    void on_btn_insert_clicked();

    void on_btn_delete_clicked();

    void on_btn_clear_clicked();

private:
    Ui::QStingListModelDemo *ui;
    QStringListModel* str_list_model;
};

#endif // QSTINGLISTMODELDEMO_H
