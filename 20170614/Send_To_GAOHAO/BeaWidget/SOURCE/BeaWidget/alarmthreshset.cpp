#include "alarmthreshset.h"
#include "ui_alarmthreshset.h"
#include "addthreshdialog.h"
#include"connection.h"
#include"logindialog.h"
#include "EditSingleThreshDlg.h"
#include <QtGui>
#include <QMessageBox>
#include "switchthread.h"
#include <QSqlRecord>
#include <QSqlQuery>

AlarmThreshSet::AlarmThreshSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlarmThreshSet)
{
    ui->setupUi(this);
    setFixedSize(QApplication::desktop()->width()*5/6,QApplication::desktop()->height()); // gaohao hide height()*7/8

    sqlquery = new QSqlQuery("",DBConnection::db);

    threshTableModel = new myStandardItemModel(this);
    ui->tableView->setModel(threshTableModel);
    ui->tableView->sortByColumn (0,Qt::AscendingOrder);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader ()->setVisible (false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   int wi=QApplication::desktop()->width()/4;
    ui->tableView->setColumnWidth(0,wi);
    ui->tableView->setColumnWidth(1,wi);
    ui->tableView->setColumnWidth(2,wi);
    ui->tableView->setColumnWidth(3,wi );
    ui->tableView->setFixedWidth(wi*4);
    ui->tableView->setFixedHeight(QApplication::desktop()->height()*4/5);
    ui->tableView->setAutoFillBackground (true);
    ui->tableView->horizontalHeader()->setStyleSheet
   ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
   "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
   "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    ui->tableView->verticalHeader()->setDefaultSectionSize(40);  //默认阈值部分的行距

    singleThreshTableModel = new myStandardItemModel(this);   //单端口部分的阈值
    ui->singleTreshView->setModel(singleThreshTableModel);
    ui->singleTreshView->sortByColumn (0,Qt::AscendingOrder);
    ui->singleTreshView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->singleTreshView->horizontalHeader()->setStretchLastSection(true);
    ui->singleTreshView->verticalHeader ()->setVisible (false);
    ui->singleTreshView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->singleTreshView->setSelectionMode(QAbstractItemView::SingleSelection);
    wi=QApplication::desktop()->width()/4;
    ui->singleTreshView->setColumnWidth(0,wi);
    ui->singleTreshView->setColumnWidth(1,wi);
    ui->singleTreshView->setColumnWidth(2,wi);
    ui->singleTreshView->setColumnWidth(3,wi);
    ui->singleTreshView->setFixedWidth(wi*4);
    ui->singleTreshView->setFixedHeight(QApplication::desktop()->height()*3/5);
    ui->singleTreshView->setAutoFillBackground (true);
    ui->singleTreshView->verticalHeader()->setDefaultSectionSize(40);
    ui->singleTreshView->horizontalHeader()->setStyleSheet
   ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
   "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
   "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");


    ui->pushButton_remove->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->pushButton_edit->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->pushButton_add->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->pushButton_add->setFixedSize(80,30);
    ui->pushButton_edit->setFixedSize(80,30);
    ui->pushButton_remove->setFixedSize(80,30);


    ui->btnSingleAdd->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->btnSingleDel->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->btnSingleEdit->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                           " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                        "border-style: outset;}"
                                       "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                       "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                           " border-style: outset; }"  );
    ui->btnSingleAdd->setFixedSize(80,30);
    ui->btnSingleEdit->setFixedSize(80,30);
    ui->btnSingleDel->setFixedSize(80,30);


    init_table();
    ui->mainLayout->setMargin(10);
    setLayout(ui->mainLayout);
    if(userLevel==1)//是普通用户
    {
         ui->pushButton_add->setVisible(false);
         ui->pushButton_edit->setVisible(false);
         ui->pushButton_remove->setVisible(false);
    }

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(54,54,54));
    palette.setColor(QPalette::WindowText,QColor("white"));
    ui->tableView->setPalette (palette);

    //connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry()));
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry(QModelIndex)));    //yangmeng 161026 改为双列显示
//    connect(ui->pushButton_remove,SIGNAL(clicked()),this,SLOT(removeEntry()));    //yangmeng 161026 改为双列显示 -- 暂时隐掉
//    connect(ui->pushButton_edit,SIGNAL(clicked()),this,SLOT(editEntry()));
//    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(addEntry()));

    connect(ui->singleTreshView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editSingleEntry()));
    connect(ui->btnSingleDel,SIGNAL(clicked()),this,SLOT(delSingleEntry()));
    connect(ui->btnSingleEdit,SIGNAL(clicked()),this,SLOT(editSingleEntry()));
    connect(ui->btnSingleAdd,SIGNAL(clicked()),this,SLOT(addSingleEntry()));


}

//增加某交换机单个端口的速率阈值
void AlarmThreshSet::addSingleEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    EditSingleThreshDlg aDialog;
    aDialog.setWindowTitle ("添加告警");

    if (aDialog.exec()==QDialog::Accepted) {
        QString switchname = aDialog.switchName->currentText().trimmed();
        QString switchport = aDialog.switchPort->text().trimmed();
        QString type = aDialog.type->currentText().trimmed();
        QString value = aDialog.value->text().trimmed();

        if(switchname==""||switchport==""||type==""||value=="")
        {
            QMessageBox::information(this,"信息错误","请填写详细内容信息!");
            return;
        }
       // QSqlQuery sqlquery("",DBConnection::db);

        //增加的记录不能是重复的交换机 端口和类型，即每个口的进和出都只能设置一次, qhy----2016.10.28
        sqlquery->prepare("select count(*) from singlethresh where switchname = ? and switchport = ? and type = ? ");
        sqlquery->bindValue(0, switchname);
        sqlquery->bindValue(1, switchport);
        sqlquery->bindValue(2, type);
        sqlquery->exec();
        sqlquery->next();
        int res_num=sqlquery->value(0).toInt();
        if (res_num>0) {
            QMessageBox::information(this,"信息错误","每个端口只能设置一个"+ type + "阈值!");
            return;
        }
        sqlquery->prepare("insert into singlethresh values(?,?,?,?)");
        sqlquery->bindValue(0, switchname);
        sqlquery->bindValue(1, switchport);
        sqlquery->bindValue(2, type);
        sqlquery->bindValue(3, value);
        sqlquery->exec();
        sqlquery->finish();
        sqlquery->clear();
        init_table();

        // gaohao 将修改完的内容写入到内存中
        int io = 0;
        if(type == "进速率")
            io = 0;
        else
            io = 1;
        //emit alarmSet(switchname,switchport.toInt(),io,value.toDouble());
        emit alarmAdd(switchname,switchport.toInt(),io,value.toDouble());   //yangmeng 161101
    }
}

//修改某交换机单个端口的速率阈值
void AlarmThreshSet::editSingleEntry()
{

    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index = ui->singleTreshView->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        int row = index.at(0).row ();

        QModelIndex singleIndex = singleThreshTableModel->index(row,0, QModelIndex());
        QVariant varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString switchname = varName.toString();

        singleIndex = singleThreshTableModel->index(row,1, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString switchport = varName.toString();

        singleIndex = singleThreshTableModel->index(row,2, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString type = varName.toString();

        singleIndex = singleThreshTableModel->index(row,3, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString value = varName.toString();


        EditSingleThreshDlg aDialog;
        aDialog.setWindowTitle("修改阈值");
        aDialog.switchName->setEnabled(false);
        aDialog.switchPort->setEnabled(false);
        aDialog.type->setEnabled(false);
        aDialog.switchName->setCurrentIndex(aDialog.switchName->findText(switchname));
        aDialog.switchPort->setValue(switchport.toInt());
        aDialog.type->setCurrentIndex(aDialog.type->findText(type));
        aDialog.value->setText(value);


        if (aDialog.exec()==QDialog::Accepted)
        {
            QString newValue = aDialog.value->text();

            if (!newValue.isEmpty ())
            {
                QSqlQuery query("",DBConnection::db);
                QString update_sql = "update singlethresh set value=? where switchname=?  and switchport=? and type=?";
                query.prepare(update_sql);
                query.bindValue(0,newValue);
                query.bindValue(1,switchname);
                query.bindValue(2,switchport);
                query.bindValue(3,type);
                query.exec();
                query.finish();
                query.clear();
                init_table();

                // gaohao 将修改完的内容写入到内存中
                int io = 0;
                if(type == "进速率")
                    io = 0;
                else
                    io = 1;
                emit alarmSet(switchname,switchport.toInt(),io,newValue.toDouble());
            }

        }

    }
}

//删除单个阈值
void AlarmThreshSet::delSingleEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    int curRow = ui->singleTreshView->currentIndex().row();//获取选中的行
    if (curRow>=0)
    {
        int ok = QMessageBox::warning(this,"删除告警阈值!","你确定删除该类型告警阈值吗？",
                                      QMessageBox::Yes,QMessageBox::Cancel);
        QModelIndex singleIndex = singleThreshTableModel->index(curRow,0, QModelIndex());
        QVariant varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString switchname = varName.toString();

        singleIndex = singleThreshTableModel->index(curRow,1, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString switchport = varName.toString();

        singleIndex = singleThreshTableModel->index(curRow,2, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString type = varName.toString();

        singleIndex = singleThreshTableModel->index(curRow,3, QModelIndex());
        varName = singleThreshTableModel->data(singleIndex, Qt::DisplayRole);
        QString value = varName.toString();

        if(ok == QMessageBox::Cancel)
        {
            ui->tableView->selectRow (curRow);
            ui->tableView->setFocus ();
        }
        else
        {
           // QSqlQuery sqlquery("",DBConnection::db);
            qDebug()<<"删除阈值"<<switchname<<switchport<<type<<value;
            sqlquery->prepare("delete from singlethresh where switchname=? and switchport=? and type=? and value=?");
            sqlquery->bindValue(0,switchname);
            sqlquery->bindValue(1,switchport);
            sqlquery->bindValue(2,type);
            sqlquery->bindValue(3,value);

            sqlquery->exec();
            sqlquery->finish();
            sqlquery->clear();
            init_table();

            // gaohao 将修改完的内容写入到内存中
            int io = 0;
            if(type == "进速率")
                io = 0;
            else
                io = 1;
            emit alarmDel(switchname,switchport.toInt(),io);
        }
    }
}

//初始化阈值设置界面
void AlarmThreshSet::init_table()
{
   // QSqlQuery  sqlquery("",DBConnection::db);;
    sqlquery->exec("select  *  from thresh");
    int itemCount=0;
    threshTableModel->clear();
    threshTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("性能参数")));
    threshTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("阈值设置")));
    threshTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("性能参数")));     //yangmeng 161026 改为双列显示
    threshTableModel->setHorizontalHeaderItem(3,new QStandardItem(tr("阈值设置")));

    while(sqlquery->next())
    {
        //threshTableModel->setItem(itemCount,0,new QStandardItem(sqlquery->value(0).toString()));
        //threshTableModel->setItem(itemCount,1,new QStandardItem(sqlquery->value(1).toString()));
        //yangmeng 161026 改为双列显示
        if(itemCount%2 == 0)
        {
            threshTableModel->setItem(itemCount/2,0,new QStandardItem(sqlquery->value(0).toString()));
            threshTableModel->setItem(itemCount/2,1,new QStandardItem(sqlquery->value(1).toString()));
        }
        else
        {
            threshTableModel->setItem(itemCount/2,2,new QStandardItem(sqlquery->value(0).toString()));
            threshTableModel->setItem(itemCount/2,3,new QStandardItem(sqlquery->value(1).toString()));
        }
        //ui->tableView->setRowHeight(itemCount,20);
        itemCount++;
    }

  ui->tableView->setModel(threshTableModel);
  int wi=QApplication::desktop()->width();
//   ui->tableView->setColumnWidth(0,wi/5);
//   ui->tableView->setColumnWidth(1,wi/5);
//   ui->tableView->setFixedWidth(wi*5/6);
//   ui->tableView->setFixedHeight(QApplication::desktop()->height()*2/6);
  ui->tableView->setColumnWidth(0,wi*5/24);//yangmeng 161026 改为双列显示
  ui->tableView->setColumnWidth(1,wi*5/24-10);
  ui->tableView->setColumnWidth(2,wi*5/24);
  ui->tableView->setColumnWidth(3,wi*5/24-10);
  ui->tableView->setFixedWidth(wi*5/6-35);
  ui->tableView->setFixedHeight(QApplication::desktop()->height()*1.6/7);       //yangmeng 161026
   sqlquery->finish();
   sqlquery->clear();

 //  setFixedHeight(QApplication::desktop()->height()*7/8); // gaohao hide
  sqlquery->exec("Select * from singlethresh order by switchname , switchport");
  singleThreshTableModel->clear();
  singleThreshTableModel->setHorizontalHeaderItem(0, new QStandardItem(tr("交换机名")));
  singleThreshTableModel->setHorizontalHeaderItem(1, new QStandardItem(tr("端口号")));
  singleThreshTableModel->setHorizontalHeaderItem(2, new QStandardItem(tr("类型")));
  singleThreshTableModel->setHorizontalHeaderItem(3, new QStandardItem(tr("阈值")));
   itemCount=0;

   while(sqlquery->next())
   {
       singleThreshTableModel->setItem(itemCount,0,new QStandardItem(sqlquery->value(0).toString()));
       singleThreshTableModel->setItem(itemCount,1,new QStandardItem(sqlquery->value(1).toString()));
       singleThreshTableModel->setItem(itemCount,2,new QStandardItem(sqlquery->value(2).toString()));
       singleThreshTableModel->setItem(itemCount,3,new QStandardItem(sqlquery->value(3).toString()));
       itemCount++;
   }
   ui->singleTreshView->setColumnWidth(0,wi*5/24);
   ui->singleTreshView->setColumnWidth(1,wi*5/24-10);
   ui->singleTreshView->setColumnWidth(2,wi*5/24);
   ui->singleTreshView->setColumnWidth(3,wi*5/24-80);
   ui->singleTreshView->setFixedWidth(wi*5/6-35);
   ui->singleTreshView->setFixedHeight(QApplication::desktop()->height()*1/2);       //yangmeng 161026
   sqlquery->finish();
   sqlquery->clear();
 }

AlarmThreshSet::~AlarmThreshSet()
{
    if(threshTableModel)
    delete threshTableModel;
    delete ui;
}

void AlarmThreshSet::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    AddThreshDialog aDialog;
    aDialog.setWindowTitle ("添加告警");

    if (aDialog.exec()==QDialog::Accepted) {
        QString alarmname = aDialog.alarmNameLineEdit->text();
        QString threshedit= aDialog.threshEdit->text ();
        if(alarmname==""||threshedit=="")
        {
            QMessageBox::information(this,"信息错误","请填写详细内容信息!");
            return;
        }
        addEntry(alarmname, threshedit);
    }
}

//增加对交换机整体适用的阈值
void AlarmThreshSet::addEntry (QString alarmname,QString threshedit) //插入记录
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    //QSqlQuery sqlquery("",DBConnection::db);;
    sqlquery->prepare("select count(*) from thresh where alarmname=?");
    sqlquery->bindValue(0,alarmname);
    sqlquery->exec();
    sqlquery->next();
    int res_num=sqlquery->value(0).toInt();
    if(res_num>0)
    {
        QMessageBox::information(this,"信息错误","该性能参数已经存在");
        return ;
    }
    else
    {

        sqlquery->prepare("insert into thresh (alarmname,threshedit)  values(?,?)");
        sqlquery->bindValue(0,alarmname);
        sqlquery->bindValue(1,threshedit);

        sqlquery->exec();

        init_table();
    }
    sqlquery->finish();
    sqlquery->clear();
}

//! [4a]
//yangmeng 161026 改为双列显示
//修改对交换机整体适用的阈值
void AlarmThreshSet::editEntry(QModelIndex index)
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    //QModelIndexList index = ui->tableView->selectionModel()->selectedRows ();

//    if (!index.isEmpty ())
//    {
        QString alarmname;
        QString threshedit;
//        int row = index.at(0).row ();

//        QModelIndex alarmnameIndex = threshTableModel->index(row,0, QModelIndex());
//        QVariant varName = threshTableModel->data(alarmnameIndex, Qt::DisplayRole);
//        alarmname = varName.toString();

//        QModelIndex thresheditIndex = threshTableModel->index(row,1, QModelIndex());
//        QVariant varThreshedit = threshTableModel->data(thresheditIndex, Qt::DisplayRole);
//        threshedit = varThreshedit.toString();

        int row = index.row ();
        int column = index.column ();

        if(column%2 == 0)   //判断点击的是列数，奇数列为性能阈值，偶数列为性能项
        {
            QModelIndex alarmnameIndex = threshTableModel->index(row,column, QModelIndex());
            QVariant varName = threshTableModel->data(alarmnameIndex, Qt::DisplayRole);
            alarmname = varName.toString();

            QModelIndex thresheditIndex = threshTableModel->index(row,column+1, QModelIndex());
            QVariant varThreshedit = threshTableModel->data(thresheditIndex, Qt::DisplayRole);
            threshedit = varThreshedit.toString();
        }
        else
        {
            QModelIndex alarmnameIndex = threshTableModel->index(row,column-1, QModelIndex());
            QVariant varName = threshTableModel->data(alarmnameIndex, Qt::DisplayRole);
            alarmname = varName.toString();

            QModelIndex thresheditIndex = threshTableModel->index(row,column, QModelIndex());
            QVariant varThreshedit = threshTableModel->data(thresheditIndex, Qt::DisplayRole);
            threshedit = varThreshedit.toString();
        }

        //! [4b]
        AddThreshDialog aDialog;
        aDialog.setWindowTitle("修改阈值");
        aDialog.setNameEn(false);      
        aDialog.alarmNameLineEdit->setText(alarmname);    
        aDialog.threshEdit->setText(threshedit);// (userlevel);

        if (aDialog.exec()==QDialog::Accepted)
        {
            QString newAlarmname = aDialog.alarmNameLineEdit->text();

            QString newThreshedit = aDialog.threshEdit->text ();

            if (!newThreshedit.isEmpty ())
            {
                QSqlQuery query("",DBConnection::db);
                QString update_sql = "update thresh set threshedit=? where alarmname=? ";
                query.prepare(update_sql);
                query.bindValue(0,newThreshedit);
                query.bindValue(1,newAlarmname);
                query.exec();
                query.finish();
                query.clear();
                init_table();

                // gaohao Add 将内容写入到阈值中
               if(alarmname == "温度（°C）")
                    SwitchThread::temMaxValue = newThreshedit.toDouble();
               else if(alarmname == "内存利用率（%）")
                    SwitchThread::memMaxValue = newThreshedit.toDouble();
               else if(alarmname == "电口(千兆)端口进速率（Mbps）")
                     SwitchThread::ele_in = newThreshedit.toDouble();
               else if(alarmname == "电口(千兆)端口出速率（Mbps）")
                     SwitchThread::ele_out = newThreshedit.toDouble();
               else if(alarmname == "光口(万兆)端口进速率（Mbps）")
                     SwitchThread::fiber_in = newThreshedit.toDouble();
               else if(alarmname == "光口(万兆)端口出速率（Mbps）")
                     SwitchThread::fiber_out = newThreshedit.toDouble();

             }

         }

//        }

}
//! [4b]

//删除对交换机整体适用的阈值
void AlarmThreshSet::removeEntry () //删除当前行
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    int curRow = ui->tableView->currentIndex().row();//获取选中的行
    if (curRow>=0)
    {
        int ok = QMessageBox::warning(this,"删除告警阈值!","你确定删除该类型告警阈值吗？",
                                      QMessageBox::Yes,QMessageBox::Cancel);
        QModelIndex nameIndex = threshTableModel->index(curRow, 0, QModelIndex());
        QVariant varName = threshTableModel->data(nameIndex, Qt::DisplayRole);
       QString  name = varName.toString();
        if(ok == QMessageBox::Cancel)
        {
            ui->tableView->selectRow (curRow);
            ui->tableView->setFocus ();
        }
        else
        {
            //QSqlQuery sqlquery("",DBConnection::db);
            qDebug()<<"删除阈值"<<name;
            sqlquery->prepare("delete from thresh where alarmname=?");
            sqlquery->bindValue(0,name);
            sqlquery->exec();
            sqlquery->finish();
            sqlquery->clear();
            init_table();
        }
    }
}
