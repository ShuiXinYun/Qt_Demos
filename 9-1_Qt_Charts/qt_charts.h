#ifndef QT_CHARTS_H
#define QT_CHARTS_H

#include <QMainWindow>
#include <QtCharts>

namespace Ui {
class Qt_Charts;
}

class Qt_Charts : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qt_Charts(QWidget *parent = nullptr);
    ~Qt_Charts();

private:
    Ui::Qt_Charts *ui;
};

#endif // QT_CHARTS_H
