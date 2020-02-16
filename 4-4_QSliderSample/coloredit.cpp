#include "coloredit.h"
#include "ui_coloredit.h"

ColorEdit::ColorEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorEdit)
{
    ui->setupUi(this);
    init();
}

ColorEdit::~ColorEdit()
{
    delete ui;
}

void ColorEdit::init()
{
    connect(ui->HSliderRed,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->HSliderGreen,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->HSliderBlue,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->HSliderAlpha,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->dialRed,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->dialGreen,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->dialBlue,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
    connect(ui->dialAlpha,SIGNAL(valueChanged(int)),this,SLOT(on_rgba_value_changed(int)));
}

void ColorEdit::on_rgba_value_changed(int)
{
    int r = ui->HSliderRed->value();
    int g = ui->HSliderGreen->value();
    int b = ui->HSliderBlue->value();
    int a = ui->HSliderAlpha->value();
    ui->labelRedValue->setText(QString::number(r).prepend("R: "));
    ui->labelGreenValue->setText(QString::number(g).prepend("G: "));
    ui->labelBlueValue->setText(QString::number(b).prepend("B: "));
    ui->labelAlphaValue->setText(QString::number(a).prepend("A: "));
    QColor color;
    color.setRgb(r, g, b, a);
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(p);
}

void ColorEdit::on_HSliderRed_valueChanged(int value)
{
    ui->dialRed->setValue(value);
}

void ColorEdit::on_HSliderGreen_valueChanged(int value)
{
    ui->dialGreen->setValue(value);
}

void ColorEdit::on_HSliderBlue_valueChanged(int value)
{
    ui->dialBlue->setValue(value);
}

void ColorEdit::on_HSliderAlpha_valueChanged(int value)
{
    ui->dialAlpha->setValue(value);
}

void ColorEdit::on_dialRed_valueChanged(int value)
{
    ui->HSliderRed->setValue(value);
}

void ColorEdit::on_dialGreen_valueChanged(int value)
{
    ui->HSliderGreen->setValue(value);
}

void ColorEdit::on_dialBlue_valueChanged(int value)
{
    ui->HSliderBlue->setValue(value);
}

void ColorEdit::on_dialAlpha_valueChanged(int value)
{
    ui->HSliderAlpha->setValue(value);
}

