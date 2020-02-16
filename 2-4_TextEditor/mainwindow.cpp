#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUi();
    //qDebug("initUi finished");
    initSingleSlots();
    //qDebug("initSingleSlots finished");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    label_CurrentFile = new QLabel;
    label_CurrentFile->setMinimumWidth(150);
    label_CurrentFile->setText("Current File:");
    ui->statusBar->addWidget(label_CurrentFile);

    progressbarFileLoad = new QProgressBar;
    progressbarFileLoad->setMaximumWidth(200);
    progressbarFileLoad->setMinimum(5);
    progressbarFileLoad->setMaximum(50);
    progressbarFileLoad->setValue(ui->textEdit->font().pointSize());
    ui->statusBar->addWidget(progressbarFileLoad);

    spinboxFontSize = new QSpinBox;
    spinboxFontSize->setMinimumWidth(50);
    spinboxFontSize->setMinimum(5);
    spinboxFontSize->setMaximum(50);
    spinboxFontSize->setValue(ui->textEdit->font().pointSize());
    ui->mainToolBar->addWidget(new QLabel("字体大小:"));
    ui->mainToolBar->addWidget(spinboxFontSize);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(new QLabel("字体:"));
    fontcombobox = new QFontComboBox;
    fontcombobox->setMinimumWidth(150);
    QFont f = ui->textEdit->font();
    fontcombobox->setCurrentFont(f);
    ui->mainToolBar->addWidget(fontcombobox);
}

void MainWindow::on_actBold_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
}

void MainWindow::on_actItalic_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontItalic(true);
    }
    else
    {
        ui->textEdit->setFontItalic(false);
    }
}

void MainWindow::on_actUnderline_triggered(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontUnderline(true);
    }
    else
    {
        ui->textEdit->setFontUnderline(false);
    }
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
        ui->actCopy->setEnabled(b);
        ui->actCut->setEnabled(b);
        ui->actPaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat txtformat;
    txtformat = ui->textEdit->currentCharFormat();
    ui->actBold->setChecked(txtformat.font().bold());
    ui->actItalic->setChecked(txtformat.fontItalic());
    ui->actUnderline->setChecked(txtformat.fontUnderline());
    //spinboxFontSize->setValue(int(txtformat.fontPointSize()));
}

void MainWindow::on_spinboxFontSize_changed(int fontsize)
{
    QTextCharFormat txtcharformat;
    txtcharformat.setFontPointSize(fontsize);
    ui->textEdit->mergeCurrentCharFormat(txtcharformat);
    progressbarFileLoad->setValue(fontsize);
}

//void MainWindow::on_fontcombobox_changed(const QFont &font)
//{
//    QTextCharFormat txtcharformat;
//    txtcharformat.setFont(font,QTextCharFormat::FontPropertiesSpecifiedOnly);
//    ui->textEdit->mergeCurrentCharFormat(txtcharformat);
//}

void MainWindow::on_fontcombobox_changed(const QString &fontname)
{
    QTextCharFormat txtcharformat;
    txtcharformat.setFontFamily(fontname);
    ui->textEdit->mergeCurrentCharFormat(txtcharformat);
}

void MainWindow::initSingleSlots()
{
    connect(spinboxFontSize,SIGNAL(valueChanged(int)),this,SLOT(on_spinboxFontSize_changed(int))); //将spinboxFontSize的valueChanged()和this的on_spinboxFontSize_changed()关联
    connect(fontcombobox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_fontcombobox_changed(const QString&)));
}

void MainWindow::on_actOpen_triggered()
{
    QString cur_path = QDir::currentPath();
    QString file_filter = "cpp file(*.h *.cpp);;text file(*.txt);;all files(*.*)";
    QString title = "open a file";
    QString file_name = QFileDialog::getOpenFileName(this, title, cur_path, file_filter);
    qDebug()<<file_name;
    if(file_name.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择要打开文件!\nPlease select the file to import!");
        return;
    }
    QFile file(file_name);
    if(!file.exists())
    {
        QMessageBox::critical(this, "Warning", "打开文件失败!\nFile open error!");
        return;
    }
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return;
    }
//    ui->textEdit->setText(file.readAll()); //QFile + QIODevice
    QTextStream txt_stream(&file);
    txt_stream.setAutoDetectUnicode(true);//自动检测编码
//    ui->textEdit->setPlainText(txt_stream.readAll()); //QFile + QTextStream一次性读入
    //逐行读入
    while(!txt_stream.atEnd())
    {
        ui->textEdit->append(txt_stream.readLine());
    }
    file.close();
}

void MainWindow::on_actNew_triggered()
{
    QString current_path = QDir::currentPath();
    QString title = "Save to file";
    QString file_filter = "header file(*.h);;source file(*.cpp);;text file(*.txt);;all(*.*)";
    QString file_save_path = QFileDialog::getSaveFileName(this, title, current_path, file_filter);
    if(file_save_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择文件存储位置!\n Please set file export!");
        return;
    }
    QFile file(file_save_path);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return;
    }
    QString str = ui->textEdit->toPlainText();
    //QFile + IODevice方式写入
//    QByteArray byte_array = str.toUtf8();
//    file.write(byte_array, str.length());
    //QFile + QtextStream方式写入
    QTextStream txt_stream(&file);
    txt_stream.setAutoDetectUnicode(true);
    txt_stream<<str;
    file.close();
}
