#include "qwdialog.h"
#include "ui_qwdialog.h"

QWDialog::QWDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialog)
{
    ui->setupUi(this);
    connect(ui->rbtnBlack, SIGNAL(clicked()), this, SLOT(set_text_color()));
    connect(ui->rbtnBlue, SIGNAL(clicked()), this, SLOT(set_text_color()));
    connect(ui->rbtnRed,SIGNAL(clicked()), this, SLOT(set_text_color()));
}

QWDialog::~QWDialog()
{
    delete ui;
}

void QWDialog::on_chkBoxUnderline_clicked(bool checked)
{
    QFont font = ui->textEdit->font();
    font.setUnderline(checked);
    ui->textEdit->setFont(font);
}

void QWDialog::on_chkBoxItalic_clicked(bool checked)
{
    QFont font = ui->textEdit->font();
    font.setItalic(checked);
    ui->textEdit->setFont(font);
}

void QWDialog::on_chkBoxBold_clicked(bool checked)
{
    QFont font = ui->textEdit->font();
    font.setBold(checked);
    ui->textEdit->setFont(font);
}

void QWDialog::set_text_color()
{
    QPalette p = ui->textEdit->palette();
    if(ui->rbtnBlue->isChecked())
    {
        p.setColor(QPalette::Text, Qt::blue);
    }
    else if(ui->rbtnRed->isChecked())
    {
        p.setColor(QPalette::Text, Qt::red);
    }
    else if(ui->rbtnBlack->isChecked())
    {
        p.setColor(QPalette::Text, Qt::black);
    }
    else
    {
        p.setColor(QPalette::Text, Qt::black);
    }
    ui->textEdit->setPalette(p);
}
