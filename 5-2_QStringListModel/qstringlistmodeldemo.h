#ifndef QSTRINGLISTMODELDEMO_H
#define QSTRINGLISTMODELDEMO_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class QStringListModelDemo;
}

class QStringListModelDemo : public QWidget
{
    Q_OBJECT

public:
    explicit QStringListModelDemo(QWidget *parent = nullptr);
    ~QStringListModelDemo();

private slots:
    void on_btn_initialize_clicked();

    void on_btn_append_clicked();

    void on_btn_insert_clicked();

    void on_btn_delete_clicked();

    void on_btn_clear_clicked();

private:
    Ui::QStringListModelDemo *ui;
    QStringListModel* str_list_model;
};

#endif // QSTRINGLISTMODELDEMO_H
