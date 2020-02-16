#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_toolbox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_toolbox()
{
    //toolbutton与action绑定
    ui->toolbtn_append->setDefaultAction(ui->act_append);
    ui->toolbtn_clear->setDefaultAction(ui->act_clear);
    ui->toolbtn_delete->setDefaultAction(ui->act_delete);
    ui->toolbtn_initialize->setDefaultAction(ui->act_initialize);
    ui->toolbtn_insert->setDefaultAction(ui->act_insert);
    ui->toolbtn_select_all->setDefaultAction(ui->act_select_all);
    ui->toolbtn_select_invert->setDefaultAction(ui->act_select_invert);
    ui->toolbtn_select_none->setDefaultAction(ui->act_select_none);

    ui->toolbtn_table_append->setDefaultAction(ui->act_table_append);
    ui->toolbtn_table_auto_resize->setDefaultAction(ui->act_table_auto_resize);
    ui->toolbtn_table_clear->setDefaultAction(ui->act_table_clear);
    ui->toolbtn_table_delete->setDefaultAction(ui->act_table_delete);
    ui->toolbtn_table_initialize->setDefaultAction(ui->act_table_initialize);
    ui->toolbtn_table_insert->setDefaultAction(ui->act_table_insert);
    ui->toolbtn_table_select_all->setDefaultAction(ui->act_table_select_all);
    ui->toolbtn_table_select_invert->setDefaultAction(ui->act_table_select_invert);

    ui->toolbtn_tableview_initialize->setDefaultAction(ui->act_tableview_initialize);
    //toolbutton样式设置
    //QString toolbtn_style = "border-style:flat;background-color:white";
    QString toolbtn_style = "border-style:flat;background-color:rgb(245, 245, 245)";
    ui->toolbtn_append->setStyleSheet(toolbtn_style );
    ui->toolbtn_clear->setStyleSheet(toolbtn_style);
    ui->toolbtn_delete->setStyleSheet(toolbtn_style);
    ui->toolbtn_initialize->setStyleSheet(toolbtn_style);
    ui->toolbtn_insert->setStyleSheet(toolbtn_style);
    ui->toolbtn_select_all->setStyleSheet(toolbtn_style);
    ui->toolbtn_select_invert->setStyleSheet(toolbtn_style);
    ui->toolbtn_select_none->setStyleSheet(toolbtn_style);

    ui->toolbtn_table_append->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_auto_resize->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_clear->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_delete->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_initialize->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_insert->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_select_all->setStyleSheet(toolbtn_style);
    ui->toolbtn_table_select_invert->setStyleSheet(toolbtn_style);

    ui->toolbtn_tableview_initialize->setStyleSheet(toolbtn_style);
}

QList<QStringList> MainWindow::read_csv(const QString &file_path)
{
    QList<QStringList> v;
    std::ifstream file;
    file.open(file_path.toStdString(), std::ios::in);
    std::string line;
    while(std::getline(file, line))
    {
        QStringList qstring_list;
        std::stringstream ss(line);
        std::string str;
        while(std::getline(ss, str, ','))
        {
            if(str != "")
            {
                qstring_list.append(QString::fromStdString(str));
            }
        }
        v.append(qstring_list);
    }
    file.close();
    return v;
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    ui->tabWidget->setCurrentIndex(index);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->toolBox->setCurrentIndex(index);
}

//获取items目录下的所有文件名列表
QList<QString> MainWindow::get_dir_items(QString path)
{
    QDir dir;
    dir.setPath(path);
    return dir.entryList(QDir::Files);
}

void MainWindow::on_act_initialize_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, "open a folder");
    qDebug()<<path;
    if(path.isEmpty())
    {
       QMessageBox::warning(this, "Warning", "请选择一个目录！\nPlease select a folder!");
    }
    else
    {
        QList<QString> items_str = get_dir_items(path);
        qDebug()<<items_str;
        ui->listWidget->clear();
    //    ui->listWidget->addItems(items_str);
        QListWidgetItem *item;
        for(int i = 0; i<items_str.size(); ++i)
        {
            item = new QListWidgetItem();
            item->setText(items_str[i]);
            //item->setCheckState(Qt::Checked);
            item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
            ui->listWidget->addItem(item);
        }
    }
}

void MainWindow::on_act_insert_triggered()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("Inserted item");
    item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    if(items.size() > 0)
    {
        int row = ui->listWidget->row(items[0]);
        ui->listWidget->insertItem(row, item);
    }
    else
    {
        ui->listWidget->insertItem(0, item);
    }
}

void MainWindow::on_act_append_triggered()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText("Appended item");
    item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    ui->listWidget->addItem(item);
}

void MainWindow::on_act_delete_triggered()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    for(int i = 0; i<items.count(); ++i)
    {
        int row = ui->listWidget->row(items[i]);
        ui->listWidget->takeItem(row);
        delete  items[i];
    }
}

void MainWindow::on_act_clear_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_act_select_all_triggered()
{
    int item_count = ui->listWidget->count();
    for(int i = 0;i<item_count; ++i)
    {
        ui->listWidget->item(i)->setSelected(true);
    }
}

void MainWindow::on_act_select_none_triggered()
{
    int item_count = ui->listWidget->count();
    for(int i = 0;i<item_count; ++i)
    {
        ui->listWidget->item(i)->setSelected(false);
    }
}

void MainWindow::on_act_select_invert_triggered()
{
    int item_count = ui->listWidget->count();
    for(int i = 0;i<item_count; ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setSelected(!(item->isSelected()));
    }
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menu_list = new QMenu(this);
    menu_list->addAction(ui->act_initialize);
    menu_list->addSeparator();
    menu_list->addAction(ui->act_append);
    menu_list->addAction(ui->act_insert);
    menu_list->addAction(ui->act_delete);
    menu_list->addAction(ui->act_clear);
    menu_list->addSeparator();
    menu_list->addAction(ui->act_select_all);
    menu_list->addAction(ui->act_select_none);
    menu_list->addAction(ui->act_select_invert);
    menu_list->exec(QCursor::pos());
    delete menu_list;
}

void MainWindow::on_act_table_initialize_triggered()
{
    QString filter = "csv file(*.csv)";
    QString dir = QDir::currentPath();
    QString file_path = QFileDialog::getOpenFileName(this, "select a csv file", dir, filter);
    qDebug()<<"csv path:"<<file_path;
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择一个csv文件! \nPlease select a csv file!");
    }
    else
    {
        QList<QStringList> v = read_csv(file_path);
        if(v.size()>0)
        {
            qDebug()<<v[0];
            ui->tableWidget->setColumnCount(v[0].size());
            ui->tableWidget->setRowCount(v.size()-1);
            //设置表格HorizontalHeader
            for(int i = 0; i<v[0].size(); ++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(v[0][i]);
                QFont font = ui->tableWidget->font();
                font.setPointSize(10);
                item->setFont(font);
                ui->tableWidget->setHorizontalHeaderItem(i, item);
            }
            ui->tableWidget->setHorizontalHeaderLabels(v[0]);
            v.removeFirst();
            QTime t;
            t.start();
            //将读入的数据内容以逐个item的方式载入表格
            for(int i = 0; i<v.size(); ++i)
            {
                for(int j = 0; j<v[i].size(); ++j)
                {
                    QTableWidgetItem *item= new QTableWidgetItem();
                    item->setText(v[i][j]);
                    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i,j,item);
                }
            }
            qDebug()<<"TableWidget initialize "<<v.size()*v[0].size()<<" items cost time:"<<t.elapsed()<<"ms";
        }

    }
}

void MainWindow::on_act_table_append_triggered()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
}

void MainWindow::on_act_table_insert_triggered()
{
    //若存在多选，则在第一个item所在行前插入
    QList<QTableWidgetItem *> selected_items = ui->tableWidget->selectedItems();
    int row_to_insert = ui->tableWidget->rowCount() + 1;
    foreach(QTableWidgetItem *item, selected_items)
    {
        if(row_to_insert > ui->tableWidget->row(item))
        {
            row_to_insert = ui->tableWidget->row(item);
        }
    }
    qDebug()<<row_to_insert;
    //int row_to_insert = ui->tableWidget->currentRow();在当前选中的item所在行前插入
    ui->tableWidget->insertRow(row_to_insert);
}

void MainWindow::on_act_table_delete_triggered()
{
    QList<QTableWidgetItem *> selected_items = ui->tableWidget->selectedItems();
    QSet<int> selected_rows;
    foreach(QTableWidgetItem *item, selected_items)
    {
        selected_rows.insert(ui->tableWidget->row(item));
    }
    //需要逆序遍历remove
//    foreach(int i, selected_rows)
//    {
//        ui->tableWidget->removeRow(i);
//    }
    QList<int> selected_rows_list = selected_rows.toList();
    qSort(selected_rows_list.begin(), selected_rows_list.end());
    qDebug()<<selected_rows_list<<", "<<selected_rows.size();
    for(auto i = selected_rows_list.rbegin(); i<selected_rows_list.rend(); ++i) //逆序遍历
    {
        ui->tableWidget->removeRow(*i);
    }
}

void MainWindow::on_act_table_clear_triggered()
{
    ui->tableWidget->clearContents();
}

void MainWindow::on_act_table_select_all_triggered()
{
    ui->tableWidget->selectAll();
}

void MainWindow::on_act_table_select_invert_triggered()
{
    QTableWidgetSelectionRange range(0, 0, 10, 5);
    int row = ui->tableWidget->rowCount();

    //单个选中、反选，性能低 low performance
//    int column = ui->tableWidget->columnCount();
//    for(int r = 0; r < row; ++r)
//    {
//        for(int c = 0; c<column; ++c)
//        {
//            bool is_selected = ui->tableWidget->item(r, c)->isSelected();
//            ui->tableWidget->item(r, c)->setSelected(!is_selected);
//        }
//    }


    //只对行操作选中反选
//    QList<QTableWidgetItem*> selected_items = ui->tableWidget->selectedItems();
//    QSet<int> selected_rows; //存储所有选中的行
//    foreach(QTableWidgetItem* item, selected_items)
//    {
//        selected_rows.insert(ui->tableWidget->row(item));
//    }
//    qDebug()<<selected_rows;
//    ui->tableWidget->setCurrentItem(NULL); //取消所有选中
    //只对行操作选中反选,性能低,low performance
    QTime t;
    t.start();
    for(int i = 0; i<row; ++i)
    {
        ui->tableWidget->selectRow(i); //选中的行再进行selectRow()即取消选中
    }
    qDebug()<<t.elapsed()<<"ms.";
}

void MainWindow::on_act_table_auto_resize_triggered()
{
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}


void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menu_list = new QMenu(this);
    menu_list->addAction(ui->act_table_initialize);
    menu_list->addSeparator();
    menu_list->addAction(ui->act_table_append);
    menu_list->addAction(ui->act_table_insert);
    menu_list->addAction(ui->act_table_delete);
    menu_list->addAction(ui->act_table_clear);
    menu_list->addSeparator();
    menu_list->addAction(ui->act_table_select_all);
    menu_list->addAction(ui->act_table_select_invert);
    menu_list->addSeparator();
    menu_list->addAction(ui->act_table_auto_resize);
    menu_list->exec(QCursor::pos());
    delete menu_list;
}

void MainWindow::on_act_tableview_initialize_triggered()
{
    QString filter = "csv file(*.csv)";
    QString dir = QDir::currentPath();
    QString file_path = QFileDialog::getOpenFileName(this, "select a csv file", dir, filter);
    qDebug()<<"csv path:"<<file_path;
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "请选择一个csv文件! \nPlease select a csv file!");
    }
    else
    {
        QList<QStringList> v = read_csv(file_path);
        if(v.size()>0)
        {
            int row = v.size();
            int column = v[0].size();
            QStandardItemModel* model = new QStandardItemModel(row, column, this);
            model->setHorizontalHeaderLabels(v[0]);
//            for(int i =0; i<v[0].size(); ++i)
//            {
//                model->setHeaderData(i, Qt::Horizontal, v[0][i]);
//            }
            v.removeFirst();
            QTime t;
            t.start();
            for(int r = 0; r<v.size(); ++r)
            {
                for(int c = 0; c<column; ++c)
                {
                    model->setItem(r, c, new QStandardItem(v[r][c]));
                }
            }
            ui->tableView->setModel(model);
            qDebug()<<"TableView initialize "<<v.size()*v[0].size()<<" items cost time:"<<t.elapsed()<<"ms";
        }
    }
//    ui->tableView
}
