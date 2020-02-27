#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_getOpenFileName_clicked();

    void on_btn_getOpenFileNames_clicked();

    void on_btn_getSaveFileName_clicked();

    void on_btn_getExistingDirectory_clicked();

    void on_btn_colorDialog_clicked();

    void on_btn_fontDialog_clicked();

    void on_btn_MsgInformation_clicked();

    void on_btn_MsgQuestion_clicked();

    void on_btn_MsgWarning_clicked();

    void on_btn_MsgCritical_clicked();

    void on_btn_MsgAbout_clicked();

    void on_btn_MsgAboutQt_clicked();

    void on_btn_inputDialog_getText_clicked();

    void on_btn_inputDialog_getInt_clicked();

    void on_btn_inputDialog_getDouble_clicked();

    void on_btn_inputDialog_getItem_clicked();

    void on_btn_inputDialog_getMultiLineText_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
