#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_getOpenFileName_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Select a File", QDir::currentPath());
    ui->textEdit_fileDialog->setText(file_path);
}

void Widget::on_btn_getOpenFileNames_clicked()
{
    QStringList file_paths_list = QFileDialog::getOpenFileNames(this, "Select files", QDir::currentPath());
    QString file_paths;
    for(int i = 0; i<file_paths_list.size(); ++i)
    {
        file_paths.append(file_paths_list[i]).append("\n");
    }
    ui->textEdit_fileDialog->setText(file_paths);
}

void Widget::on_btn_getSaveFileName_clicked()
{
    QString save_file_path = QFileDialog::getSaveFileName(this, "Set save file name", QDir::currentPath());
    ui->textEdit_fileDialog->setText(save_file_path);
}

void Widget::on_btn_getExistingDirectory_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select a directory", QDir::currentPath());
    ui->textEdit_fileDialog->setText(dir);
}

void Widget::on_btn_colorDialog_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select a color");
    QPalette p = ui->textEdit_color->palette();
    p.setColor(QPalette::Base, color);
    ui->textEdit_color->setPalette(p);
}

void Widget::on_btn_fontDialog_clicked()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    QString font_name = font.toString();
    ui->lineEditFont->setText(font_name);
    ui->lineEditFont->setFont(font);
}

void Widget::on_btn_MsgInformation_clicked()
{
    QMessageBox::information(this, "Information", "QMessage information.");
}

void Widget::on_btn_MsgQuestion_clicked()
{
    int btn = QMessageBox::question(this, "Question", "QMessage question.", QMessageBox::Yes, QMessageBox::No, QMessageBox::Abort);
    if(btn == QMessageBox::Yes)
    {
        ui->textEdit_input->setText("Yes button clicked.");
    }
    else if(btn == QMessageBox::No)
    {
        ui->textEdit_input->setText("No button clicked.");
    }
    else if (btn == QMessageBox::Abort)
    {
        ui->textEdit_input->setText("Abort button clicked.");
    }
}

void Widget::on_btn_MsgWarning_clicked()
{
    QMessageBox::warning(this, "Warning", "QMessage Warning.");
}

void Widget::on_btn_MsgCritical_clicked()
{
    QMessageBox::critical(this, "Critical", "QMessage Critical.");
}

void Widget::on_btn_MsgAbout_clicked()
{
    QMessageBox::about(this, "About", "QMessage About.");
}

void Widget::on_btn_MsgAboutQt_clicked()
{
    QMessageBox::aboutQt(this, "QMessage About Qt");
}

void Widget::on_btn_inputDialog_getText_clicked()
{
    QString text = QInputDialog::getText(this, "Input", "请输入一行文字：", QLineEdit::Normal, "Default input");
    ui->textEdit_input->setText(text);
}

void Widget::on_btn_inputDialog_getInt_clicked()
{
    INT32 i = QInputDialog::getInt(this, "Input an integer between 0~1000", "请输入 0~1000 的整数：", 0, 0, 1000);
    ui->textEdit_input->setText(QString::number(i));
}

void Widget::on_btn_inputDialog_getDouble_clicked()
{
    double d = QInputDialog::getDouble(this, "Input a double between 0.0~3.14", "请输入0.0~3.14的浮点数", 0.0, 0.0, 3.14, 2);
    ui->textEdit_input->setText(QString::number(d, 'g', 3));
}

void Widget::on_btn_inputDialog_getItem_clicked()
{
    QStringList str_list = {"item1", "item2", "item3"};
    QString text  = QInputDialog::getItem(this, "Select a item", "请选择一个项目：", str_list, 0, false);
    ui->textEdit_input->setText(text);
}

void Widget::on_btn_inputDialog_getMultiLineText_clicked()
{
    QString text = QInputDialog::getMultiLineText(this, "Please input multi-line text", "请输入多行数据：", "default");
    ui->textEdit_input->setText(text);
}
