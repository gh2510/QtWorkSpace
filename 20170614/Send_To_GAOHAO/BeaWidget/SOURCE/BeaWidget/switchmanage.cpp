#include "switchmanage.h"
#include "ui_switchmanage.h"
#include "addswitchdialog.h"
#include"connection.h"
#include"logindialog.h"
#include <QtGui>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QApplication>
#include <QDesktopWidget>
SwitchManage::SwitchManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SwitchManage)
{
    ui->setupUi(this);
    setFixedSize(QApplication::desktop()->width()*5/6,QApplication::desktop()->height()*5/6+5);
    switchTableModel = new myStandardItemModel();
    tableview =new QTableView();
    tableview->setModel(switchTableModel);
    tableview->sortByColumn (0,Qt::AscendingOrder);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);
    tableview->verticalHeader ()->setVisible (false);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);

    tableview->setFixedHeight(QApplication::desktop()->height()*3/4);
    tableview->setAutoFillBackground (true);

    tableview->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
    "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
    "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
    "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");

    tableview->verticalHeader()->setDefaultSectionSize(40);

    btn_add =new commonButton();
    btn_add->setText("添加");
    btn_add->setFixedSize(110,60);
    btn_add->setVisible(false);
    btn_delete =new commonButton();
    btn_delete->setText("删除");
    btn_delete->setFixedSize(110,60);
    btn_delete->setVisible(false);
    btn_update =new commonButton();
    btn_update->setText("修改");
    btn_update->setFixedSize(110,60);
   btn_update->setVisible(false);
    bottom_layout=new QHBoxLayout();
    bottom_layout->addStretch(2);
    bottom_layout->addWidget(btn_add,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(btn_delete,0,Qt::AlignVCenter);
    bottom_layout->addStretch(1);
    bottom_layout->addWidget(btn_update,0,Qt::AlignVCenter);
    bottom_layout->addStretch(2);
    init_table();
    mainLayout=new QVBoxLayout();
    mainLayout->setMargin(10);
    mainLayout->addWidget(tableview,0,Qt::AlignHCenter);
    if(userLevel==0)//是管理员
    {
         connect(tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry()));
         btn_delete->setVisible(true);
         btn_update->setVisible(true);
         btn_add->setVisible(true);
    }

    mainLayout->addLayout(bottom_layout,0);
    mainLayout->addStretch(1);

    setLayout(mainLayout);   
    connect(btn_add,SIGNAL(click()),this,SLOT(addEntry()));
    connect(btn_delete,SIGNAL(click()),this,SLOT(removeEntry()));
    connect(btn_update,SIGNAL(click()),this,SLOT(editEntry()));
}
void SwitchManage::init_table()
{
    QSqlQuery  sqlquery("",DBConnection::db);

    sqlquery.exec("select  ID,name,description,location,IP,IP2,remark  from switch");
    int itemCount=0;
    switchTableModel->clear();

    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("序号")));    
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("交换机标识")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("交换机名称")));
    switchTableModel->setHorizontalHeaderItem(3,new QStandardItem(tr("位置")));
    switchTableModel->setHorizontalHeaderItem(4,new QStandardItem(tr("带内管理IP")));
    switchTableModel->setHorizontalHeaderItem(5,new QStandardItem(tr("带外管理IP")));
    switchTableModel->setHorizontalHeaderItem(6,new QStandardItem(tr("端口数量")));
    while(sqlquery.next())
    {
        switchTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        switchTableModel->setItem(itemCount,1,new QStandardItem(sqlquery.value(1).toString()));
        switchTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));
        switchTableModel->setItem(itemCount,3,new QStandardItem(sqlquery.value(3).toString()));
        switchTableModel->setItem(itemCount,4,new QStandardItem(sqlquery.value(4).toString()));
        switchTableModel->setItem(itemCount,5,new QStandardItem(sqlquery.value(5).toString()));
        switchTableModel->setItem(itemCount,6,new QStandardItem(sqlquery.value(6).toString()));

        itemCount++;
    }
sqlquery.finish();
sqlquery.clear();
  tableview->setModel(switchTableModel);

  int wi=QApplication::desktop()->width()/9;
  tableview->setColumnWidth(0,wi-wi*2/3);
  tableview->setColumnWidth(1,wi-wi/3);
  tableview->setColumnWidth(2,wi+wi*2/3);
  tableview->setColumnWidth(3,wi+wi*2/3);
  tableview->setColumnWidth(4,wi);
  tableview->setColumnWidth(5,wi);
  tableview->setColumnWidth(6,wi-wi/3);
  tableview->setFixedWidth((wi+5)*7);
 // tableview->setFixedHeight(QApplication::desktop()->height()*4/5);
}

SwitchManage::~SwitchManage()
{
    delete switchTableModel;
    delete tableview;
    delete btn_add;
    delete btn_delete;
    delete btn_update;
    delete bottom_layout;
    delete mainLayout;
    delete ui;
}


//! [2]
void SwitchManage::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    AddSwitchDialog aDialog;
    aDialog.setWindowTitle("添加交换机");
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
    if (aDialog.exec()==QDialog::Accepted) {
        QString name = aDialog.switchNameLineEdit->text().trimmed();
        QString address = aDialog.ipAddressLineEdit->text().trimmed();
        QString address2=aDialog.ipAddress2LineEdit->text().trimmed();
        QString description=aDialog.descriptionLineEdit->text().trimmed();
        QString location= aDialog.locationEdit->text().trimmed();
        QString remark= aDialog.remarkEdit->currentText().trimmed();
        QString community="public";
        if(name==""||address==""||location=="")
        {
            QMessageBox::information(this,"信息错误","请填写详细内容信息!");
            return;
        }
        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("select count(*) from switch where name=?");
        sqlquery.bindValue(0,name);
        sqlquery.exec();
        sqlquery.next();
        int res_num=sqlquery.value(0).toInt();
        if(res_num>0)
        {
            QMessageBox::information(this,"信息错误","交换机名重复");
        }
        else
        {

            sqlquery.prepare("insert into switch (location,name,description,IP,IP2,community,remark)  values(?,?,?,?,?,?,?)");
            sqlquery.bindValue(0,location);
            sqlquery.bindValue(1,name);
            sqlquery.bindValue(2,description);
            sqlquery.bindValue(3,address);
            sqlquery.bindValue(4,address2);
            sqlquery.bindValue(5,community);
            sqlquery.bindValue(6,remark);
            sqlquery.exec();
/*
            sqlquery.prepare("insert into switch_topo (name,ip,community,pox_x,pos_y)  values(?,?,'public',0,0)");
            sqlquery.bindValue(0,name);
            sqlquery.bindValue(1,address);
            sqlquery.exec();
*/
            init_table();

            QString insert_sql = "insert into switch_topo values (?, ?, ?,?,?)";
            sqlquery.prepare(insert_sql);
            sqlquery.addBindValue(name);
            sqlquery.addBindValue(address);
            sqlquery.addBindValue(community);
            sqlquery.addBindValue(0);
            sqlquery.addBindValue(0);
            sqlquery.exec();

            //emit signal_update();//暂时不需要
        }
        sqlquery.finish();
        sqlquery.clear();
    }
}

void SwitchManage::removeEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index =tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString name;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row, 0, QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        table_index = tb_in_da.toInt();

        QModelIndex nameIndex = switchTableModel->index(row, 1, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("delete from switch where ID=?");
        sqlquery.bindValue(0,table_index);
        sqlquery.exec();
        init_table();

        QString insert_sql = "delete from switch_topo where name=?";
        sqlquery.prepare(insert_sql);
        sqlquery.addBindValue(name);
        sqlquery.exec();

        insert_sql="delete from switch_line where switch_name1=? or switch_name2=?";
        sqlquery.prepare(insert_sql);
        sqlquery.addBindValue(name);
        sqlquery.addBindValue(name);
        sqlquery.exec();
        sqlquery.finish();
        sqlquery.clear();
        //emit signal_update();//暂时不需要
    }
}
void SwitchManage::slot_init()
{
    init_table();
}
//! [2]


//! [4a]
void SwitchManage::editEntry()
{
    if(userLevel)
    {
        QMessageBox::information(this,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index =tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString name;
        QString location;
        QString address;
        QString address2;
        QString description;
        QString remark;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row, 0, QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        table_index = tb_in_da.toInt();


        QModelIndex nameIndex = switchTableModel->index(row, 1, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex descriptionIndex = switchTableModel->index(row, 2, QModelIndex());
        QVariant varDescription = switchTableModel->data(descriptionIndex, Qt::DisplayRole);
        description = varDescription.toString();


        QModelIndex locationIndex = switchTableModel->index(row, 3, QModelIndex());
        QVariant vaLocation= switchTableModel->data(locationIndex, Qt::DisplayRole);
        location = vaLocation.toString();

        QModelIndex addressIndex = switchTableModel->index(row, 4, QModelIndex());
        QVariant varAddr = switchTableModel->data(addressIndex, Qt::DisplayRole);
        address = varAddr.toString();

        QModelIndex addressIndex2 = switchTableModel->index(row, 5, QModelIndex());
        QVariant varAddr2 = switchTableModel->data(addressIndex2, Qt::DisplayRole);
        address2 = varAddr2.toString();

        QModelIndex communityIndex = switchTableModel->index(row, 6, QModelIndex());
        QVariant varCommunity = switchTableModel->data(communityIndex, Qt::DisplayRole);
        remark = varCommunity.toString();

        //! [4b]
        AddSwitchDialog aDialog;
        aDialog.setWindowTitle(tr("修改交换机信息"));

        aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
        aDialog.setIsEdit(true);

        aDialog.switchNameLineEdit->setText(name);
        aDialog.ipAddressLineEdit->setText(address);
        aDialog.ipAddress2LineEdit->setText(address2);
        aDialog.descriptionLineEdit->setText(description);
        aDialog.locationEdit->setText(location);
        aDialog.remarkEdit->setCurrentIndex(aDialog.remarkEdit->findText(remark));
        aDialog.setModal(true);        
        if (aDialog.exec()==QDialog::Accepted)
        {
            QString newName = aDialog.switchNameLineEdit->text();
            QString newIP = aDialog.ipAddressLineEdit->text ();
            QString newIP2 = aDialog.ipAddress2LineEdit->text ();
            QString description = aDialog.descriptionLineEdit->text ();

            QString newLocation = aDialog.locationEdit->text ();
            QString newRemark = aDialog.remarkEdit->currentText();
            if (!newName.isEmpty ()&&!newIP.isEmpty ()&&!newLocation.isEmpty ())
            {               
                QSqlQuery query("",DBConnection::db);;
                QString update_sql = "update switch set description=?,IP=?,IP2=?,location=?, remark=? where ID=? ";
                query.prepare(update_sql);
                query.bindValue(0,description);
                query.bindValue(1,newIP);
                query.bindValue(2,newIP2);
                query.bindValue(3,newLocation);
                query.bindValue(4,newRemark);
                query.bindValue(5,table_index);
                query.exec();
                query.finish();

                 update_sql = "update switch_topo set  ip=? where name=? ";
                 query.prepare(update_sql);
                 query.bindValue(0,newIP);
                 query.bindValue(1,newName);
                 query.exec();

                query.finish();
                query.clear();
                init_table();
                //emit signal_update(); //暂时不需要
            }
            else{
                QMessageBox::information(this,"信息不完整","请填写完整信息");
            }

        }

       tableview->selectRow (row);
       tableview->setFocus ();
    }
}
//! [4b]


