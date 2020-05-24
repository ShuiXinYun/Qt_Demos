#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGetHostNameIp_clicked()
{
    QString hostname = QHostInfo::localHostName();
    QHostInfo host_info = QHostInfo::fromName(hostname);
    QList<QHostAddress> address_list = host_info.addresses();
    ui->plainTextEdit->appendPlainText("本机hostname: " + hostname +"\n============================");
    if(address_list.isEmpty())
    {
        ui->plainTextEdit->appendPlainText("ip empty");
    }
    else
    {
        for(int i=0; i<address_list.size(); ++i)
        {
            QHostAddress a_host = address_list.at(i);
            ui->plainTextEdit->appendPlainText("protocol: "+protocolName(a_host.protocol()));
            ui->plainTextEdit->appendPlainText("ip address: "+a_host.toString());
        }
    }
}

void MainWindow::on_btnGetAllNetInterfaces_clicked()
{

}

void MainWindow::on_btnGetAllAddresses_clicked()
{

}

void MainWindow::on_btnGetDomainName_clicked()
{
    QString domain_adress = ui->lineEditWebAdress->text();
}

QString MainWindow::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{
    switch (protocol)
    {
    case QAbstractSocket::IPv4Protocol:
        return "Ipv4";
    case QAbstractSocket::IPv6Protocol:
        return "Ipv6";
    case QAbstractSocket::AnyIPProtocol:
        return "Any ip";
    default:
        return "unknown ip";
    }
}
