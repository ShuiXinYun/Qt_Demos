# Qt Demos for book《Qt5.9 c++开发指南》

> 学习Qt过程中做的一些小demo，用书是Qt5.9 c++开发指南》.
---
## 2-1_HelloWorld
Hello World.

![](./README/2-1_HelloWorld.png)
+ Label
+ Push Button
+ SIGNAL & SLOT

## 2-2_Widgets
Simple editor.

![](./README/2-2_Widgets.png)
+ Check Box
+ Radio Button
+ Layout
+ Text Edit: set font italic, set font bold, set font underline, set palette(to set textedit font color)
+ SIGNAL & SLOT
+ QObject::connect: `connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type = Qt::AutoConnection)`

## 2-4_TextEditor
Text editor.

![](./README/2-4_TextEditor.png)
+  **Design Mode: 代码化+可视化(code+ui)**
+  Set icon
+  ToorBar
+  statusBar
+  SIGNAL & SLOT
+  Action
+  qDebug()
+  ProgressBar
+  SpinBox
+  Text Edit: set font, set font italic, set font bold, set font underline, set font pointsize, clear...
+  QDir
+  QFileDialog
+  QMessageBox
+  QFile + QIODevice & QFile + QTextStream to read and write text file

## 4-3_SpinBox_Sample
Simple price caculator.

![](./README/4-3_SpinBox_Sample.png)
+ SpinBox(prefix, suffix)
+ Group Box
+ lineEdit
+ `QString::number(), QString.setNum()`...

## 4-4_QSliderSample
Simple Color Mixer

![](./README/4-4_QSliderSample.png)
+ Slider
+ Dial
+ QColor: `QColor color; color.setRgb(r, g, b, a);`
+ QPalette:
  ```Qt
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(p);
  ```

## 4-5_Time
Use of time Classes.

![](./README/4-5_Time.png)
+ QTime
  ```Qt
  QTime t;
  t.start();
  //do something
  t.elapsed();//do something time in miliseconds.
  ```
+ QDateTime
  ```Qt
  QDateTime datetime = QDateTime::currentDateTime();
  QString time_str = datetime.toString("yyyy-MM-dd hh:mm:ss"));
  QDateTime datetime = QDateTime::fromString(time_str,"yyyy-MM-dd hh:mm:ss");
  ```
+ QTimer
  ```Qt
  QTimer* timer_1 = new QTimer(this);
  timer_1->stop();
  timer_1->setInterval(1000);
  connect(timer_1, SIGNAL(timeout()), this, SLOT(on_timer_1_timeout()));
  
  void on_on_timer_1_timeout()
  {
      //do something every timer interval
  }
  ```
+ Date/Time Edit

## 4-7_ItemWidget
Use of item-based or model-view Widgets.

![](./README/4-7_ItemWidget.png)
+ Tool Box(Container)
+ Tab Widget(Container)
+ QListWidgetItem
+ QListWidget(item based)
+ QTableWidgetItem
+ QTableWidget(item based), how to fill the table with items
+ QStandardItemModel
+ QTableView(Model-View), setModel
+ QListWidget/QTableWidget: append, insert, delete(QTableWidget逆序遍历remove), clear, selectAll, selectNone, selectInvert, autoResize
+ How to custom right-click Menu: 如何自定义右键快捷菜单
+ Tool Button(How to bind action)
+ Button setStyleSheet
+ Read CSV(std ifstream, getline() split string)
+ Container:QList, QStringList
+ QDir:
  ```Qt
  //get dir_path files.
  QDir dir;
  dir.setPath(path);
  return dir.entryList(QDir::Files);
  ```
  
## 5-1_QFileSystemModel
Use of QFileSystemModel to show the file-system.

![](./README/5-1_QFileSystemModel.png)
+ QFileSystemModel: setRootPath, **index(QString path)**, size(), type(), filePath
+ QTreeView/QTableView/QListView: setModel,setRootIndex
  ```qt
  file_sys_model->setRootPath(path);
  qDebug()<<"file_sys_model root path:"<<file_sys_model->rootPath();
  ui->treeView->setRootIndex(file_sys_model->index(path));//设置treeView根节点为选定目录
  ui->tableView->setRootIndex(file_sys_model->index(path));
  ui->tableView->resizeColumnsToContents();
  ui->tableView->resizeRowsToContents();
  ui->listView->setRootIndex(file_sys_model->index(path));
  ```
+ QDesktopServices: `QDesktopServices::openUrl(QUrl(file_sys_model->filePath(index)));//listView item双击事件, 调用系统程序打开文件`

## 5-2_QStringListModel
Use of QStringListModel + QListView to show a csv file.

![](./README/5-2_QStringListModel.png)
+ QStringListModel: setStringList, insertRow(), setData(), removeRow(), removeRows(),**index(int row)**
+ QModelIndex: QModelIndex.row()
+ Bind the QStringListModel to QListView using QListView.setModel(), the QListView changes with the QStringListModel,
+ QListView: currentIndex(), setCurrentIndex()

## 5-3_QStandardItemModel

![](./README/5-3_QStandardItemModel.png)

+ QStandardItemModel
+ Bind QStandardItemModel to QTableView
+ QTextStream: read csv file
+ CountryPopulation class
+ QDataStream: export TableView data and read binary data to TableView, override >> & << operator to read and write data from and to CountryPopulation objects.
+ Append/Insert/Delete/Modify the table, set the index on focus