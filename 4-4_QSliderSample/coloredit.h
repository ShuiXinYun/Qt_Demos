#ifndef COLOREDIT_H
#define COLOREDIT_H

#include <QWidget>

namespace Ui {
class ColorEdit;
}

class ColorEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ColorEdit(QWidget *parent = nullptr);
    ~ColorEdit();

private slots:
    void on_HSliderRed_valueChanged(int value);

    void on_HSliderGreen_valueChanged(int value);

    void on_HSliderBlue_valueChanged(int value);

    void on_HSliderAlpha_valueChanged(int value);

    void on_dialRed_valueChanged(int value);

    void on_dialGreen_valueChanged(int value);

    void on_dialBlue_valueChanged(int value);

    void on_dialAlpha_valueChanged(int value);

    void on_rgba_value_changed(int);

private:
    Ui::ColorEdit *ui;
    void init();
};

#endif // COLOREDIT_H
