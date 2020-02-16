#ifndef MYTIMEWIDGET_H
#define MYTIMEWIDGET_H

#include <QWidget>
#include <QtCore>

namespace Ui {
class MyTimeWidget;
}

class MyTimeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTimeWidget(QWidget *parent = nullptr);
    ~MyTimeWidget();

private slots:
    void on_btnReadTime_clicked();

    void on_btnSetTime_clicked();

    void on_btnStartTimer_clicked();

    void on_spinBoxTimerPeriod_valueChanged(int arg1);

    void on_btnStopTimer_clicked();

    void on_timer_1_timeout();

    void on_timer_2_timeout();
private:
    Ui::MyTimeWidget *ui;
    QTimer *timer_1;
    QTimer *timer_2; //show elapsed time during every timer_1 interval to update progress bar
    QTime time_elapsed_count;

};

#endif // MYTIMEWIDGET_H
