#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtNetwork>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGetHostNameIp_clicked();

    void on_btnGetAllNetInterfaces_clicked();

    void on_btnGetAllAddresses_clicked();

    void on_btnGetDomainName_clicked();

private:
    Ui::MainWindow *ui;
    QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
};

#endif // MAINWINDOW_H
