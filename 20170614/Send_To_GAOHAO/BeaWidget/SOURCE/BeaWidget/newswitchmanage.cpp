#include "newswitchmanage.h"
#include "ui_newswitchmanage.h"
#include "connection.h"
#include "logindialog.h"
#include "addswitchdialog.h"
#include "newaddswitchdialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

NewSwitchManage::NewSwitchManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewSwitchManage)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    switchTableModel = NULL;

    iniModel();
    iniView();

//    connect(ui->tableview,SIGNAL(doubleClicked(QModelIndex)),
//            this,SLOT(editEntry()));

    connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(addEntry()));
    connect(ui->btn_delete,SIGNAL(clicked()),this,SLOT(removeEntry()));
    connect(ui->btn_update,SIGNAL(clicked()),this,SLOT(editEntry()));
    connect(ui->tableview,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(editEntry(QModelIndex)));

    if(userLevel == 0)
    {
        setManageBtnVisible(true);
    }
    else
    {
        setManageBtnVisible(false);
    }
    ui->btn_add->hide();
    ui->btn_delete->hide();

}

void NewSwitchManage::iniModel()
{
    if(!switchTableModel)
    {
       switchTableModel = new myStandardItemModel();
    }

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
}

void NewSwitchManage::iniView()
{
    ui->tableview->setModel(switchTableModel);
    ui->tableview->sortByColumn (0,Qt::AscendingOrder);
    ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableview->horizontalHeader()->setStretchLastSection(true);
    ui->tableview->verticalHeader()->setVisible (false);
    ui->tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableview->setAutoFillBackground (true);

    int wi=this->width()/8;
    ui->tableview->setColumnWidth(0,wi-wi*2/3);
    ui->tableview->setColumnWidth(1,wi-wi/3);
    ui->tableview->setColumnWidth(2,wi+wi*2/3);
    ui->tableview->setColumnWidth(3,wi+wi*2/3);
    ui->tableview->setColumnWidth(4,wi);
    ui->tableview->setColumnWidth(5,wi);
    ui->tableview->setColumnWidth(6,wi-wi/3);
    ui->tableview->setMinimumWidth(this->width()*9/10);


}

void NewSwitchManage::setManageBtnVisible(bool isVisibled)
{
    ui->btn_add->setVisible(isVisibled);
    ui->btn_delete->setVisible(isVisibled);
    ui->btn_update->setVisible(isVisibled);
}

void NewSwitchManage::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
//    AddSwitchDialog aDialog;
    NewAddSwitchDialog aDialog;
    aDialog.setWindowTitle("添加交换机");
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
    if (aDialog.exec()==QDialog::Accepted)
    {
//        QString name = aDialog.switchNameLineEdit->text().trimmed();
//        QString address = aDialog.ipAddressLineEdit->text().trimmed();
//        QString address2=aDialog.ipAddress2LineEdit->text().trimmed();
//        QString description=aDialog.descriptionLineEdit->text().trimmed();
//        QString location= aDialog.locationEdit->text().trimmed();
//        QString remark= aDialog.remarkEdit->currentText().trimmed();

        QString name = aDialog.getName().trimmed();
        QString address = aDialog.getIP_In().trimmed();
        QString address2=aDialog.getIp_Out().trimmed();
        QString description=aDialog.getDescription().trimmed();
        QString location= aDialog.getLocation().trimmed();
        QString remark= aDialog.getRemark().trimmed();

        QString community="public";
        if(name ==""||address==""||location=="")
        {
            QMessageBox::information(0,"信息错误","请填写详细内容信息!");
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
            QMessageBox::information(0,"信息错误","交换机名重复");
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
//            init_table();
            iniModel();
            iniView();

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


void NewSwitchManage::editEntry(QModelIndex)
{
    editEntry();
}

void NewSwitchManage::editEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index =ui->tableview->selectionModel()->selectedRows ();

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
//        AddSwitchDialog aDialog;
        NewAddSwitchDialog *aDialog= new NewAddSwitchDialog();
        aDialog->setWindowTitle(tr("修改交换机信息"));

        aDialog->move((QApplication::desktop()->width()-aDialog->width())/2,
                      (QApplication::desktop()->height()-aDialog->height())/2);
        aDialog->setIsEdit(true);

        aDialog->setInfShow(name,address,address2,description,location,remark);
        aDialog->setModal(true);
        if (aDialog->exec()==QDialog::Accepted)
        {
            QString newName = aDialog->getName();
            QString newIP = aDialog->getIP_In();
            QString newIP2 = aDialog->getIp_Out();
            QString description = aDialog->getDescription();

            QString newLocation = aDialog->getLocation();
            QString newRemark = aDialog->getRemark();

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
                iniModel();
                iniView();
                //emit signal_update(); //暂时不需要
            }
            else
            {
                QMessageBox::information(0,"信息不完整","请填写完整信息");
            }

        }

       ui->tableview->selectRow (row);
       ui->tableview->setFocus ();

       delete aDialog;
       aDialog = NULL;
    }
}

void NewSwitchManage::removeEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index =ui->tableview->selectionModel()->selectedRows ();

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
//        init_table();//change
        iniModel();
        iniView();

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

void NewSwitchManage::slot_init()
{
    iniModel();
    iniView();
}

NewSwitchManage::~NewSwitchManage()
{
    if(switchTableModel)delete switchTableModel;
    delete ui;
}


