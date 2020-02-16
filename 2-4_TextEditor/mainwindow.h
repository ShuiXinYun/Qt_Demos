#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QVariant>
#include <QtWidgets>
#include <QObject>
#include <QTextCodec>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actBold_triggered(bool checked);

    void on_actItalic_triggered(bool checked);

    void on_actUnderline_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_spinboxFontSize_changed(int fontsize);

    void on_fontcombobox_changed(const QString &fontname);

    void on_textEdit_selectionChanged();

    void on_actOpen_triggered();

    void on_actNew_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *label_CurrentFile;
    QProgressBar *progressbarFileLoad;
    QSpinBox *spinboxFontSize;
    QFontComboBox *fontcombobox;
    void initUi();
    void initSingleSlots();
};

#endif // MAINWINDOW_H
