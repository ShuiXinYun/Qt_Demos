#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QDir>
#include <QFileDialog>
#include <QtWidgets>
#include <fstream>
#include <string>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QList<QStringList> read_csv(const QString&);
    ~MainWindow();

private slots:
    void on_act_initialize_triggered();

    void on_act_insert_triggered();

    void on_act_append_triggered();

    void on_act_delete_triggered();

    void on_act_clear_triggered();

    void on_act_select_all_triggered();

    void on_act_select_none_triggered();

    void on_act_select_invert_triggered();

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_act_table_initialize_triggered();

    void on_act_table_append_triggered();

    void on_act_table_insert_triggered();

    void on_act_table_delete_triggered();

    void on_act_table_select_all_triggered();

    void on_act_table_select_invert_triggered();

    void on_act_table_auto_resize_triggered();

    void on_act_table_clear_triggered();

    void on_toolBox_currentChanged(int index);

    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_act_tableview_initialize_triggered();

private:
    Ui::MainWindow *ui;
    void init_toolbox();
    QList<QString> get_dir_items(QString);
};

#endif // MAINWINDOW_H
