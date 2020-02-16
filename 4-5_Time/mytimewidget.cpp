#include "mytimewidget.h"
#include "ui_mytimewidget.h"

MyTimeWidget::MyTimeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTimeWidget)
{
    ui->setupUi(this);
    ui->btnStopTimer->setEnabled(false);
    timer_1 = new QTimer(this);
    timer_1->stop();
    timer_1->setInterval(1000);
    timer_2 = new QTimer(this);
    timer_2->setInterval(10);
    timer_2->stop();

    connect(timer_1, SIGNAL(timeout()), this, SLOT(on_timer_1_timeout()));
    connect(timer_2, SIGNAL(timeout()), this, SLOT(on_timer_2_timeout()));

    QDateTime datetime = QDateTime::currentDateTime();
    ui->lineEditSystemTime->setText(datetime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->dateTimeEdit->setDateTime(datetime);
}

MyTimeWidget::~MyTimeWidget()
{
    delete ui;
    delete timer_1;
    delete timer_2;
}

void MyTimeWidget::on_btnReadTime_clicked()
{
    QDateTime datetime = QDateTime::currentDateTime();
    ui->lineEditSystemTime->setText(datetime.toString("yyyy-MM-dd hh:mm:ss"));
}

void MyTimeWidget::on_btnSetTime_clicked()
{
    QDateTime datetime = QDateTime::fromString(ui->lineEditSystemTime->text(),"yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit->setDateTime(datetime);
}

void MyTimeWidget::on_btnStartTimer_clicked()
{
    ui->lineEditTimer1Count->setText(QString::number(0));
    timer_1->start();
    timer_2->start();
    time_elapsed_count.start();
    ui->btnStartTimer->setEnabled(false);
    if(!ui->btnStopTimer->isEnabled())
    {
        ui->btnStopTimer->setEnabled(true);
    }
}

void MyTimeWidget::on_btnStopTimer_clicked()
{
    timer_1->stop();
    timer_2->stop();
    if(!ui->btnStartTimer->isEnabled())
    {
        ui->btnStartTimer->setEnabled(true);
    }
    ui->btnStopTimer->setEnabled(false);
}

void MyTimeWidget::on_spinBoxTimerPeriod_valueChanged(int arg1)
{
    timer_1->setInterval(arg1);
}

void MyTimeWidget::on_timer_1_timeout()
{
    int count = ui->lineEditTimer1Count->text().toInt();
    ++count;
    ui->lineEditTimer1Count->setText(QString::number(count));
}

void MyTimeWidget::on_timer_2_timeout()
{
    if(timer_1->isActive())
    {
        QString time_elapsed = QString::number(time_elapsed_count.elapsed());
        ui->lineEditTimeElapsed->setText(time_elapsed.append(" ms"));
        int time_elapsed_interval = timer_1->interval() - timer_1->remainingTime();
        int value = int(100.0*time_elapsed_interval / timer_1->interval());
        ui->progressBar->setValue(value);
    }
}

