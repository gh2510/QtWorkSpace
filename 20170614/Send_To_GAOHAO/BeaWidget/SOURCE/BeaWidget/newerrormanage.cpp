#include "newerrormanage.h"
#include "ui_newerrormanage.h"
#include "connection.h"
#include "logindialog.h"
#include "adderrordialog.h"
#include "newadderrordialog.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDateTime>
#include <QApplication>
#include <QDesktopWidget>


#include <QDebug>


NewErrorManage::NewErrorManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewErrorManage)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());

    switchTableModel = new myStandardItemModel();

    init_table();
    iniView();
    setViewSize();
    if(userLevel==0)        //guanliyuan
    {
        ui->btn_add->setVisible(true);
        ui->btn_delete->setVisible(true);
    }
    connect(ui->tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry()));
    connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(addEntry()));
    connect(ui->btn_delete,SIGNAL(clicked()),this,SLOT(removeEntry()));
    connect(ui->btn_update,SIGNAL(clicked()),this,SLOT(editEntry()));
    connect(ui->btn_show,SIGNAL(clicked()),this,SLOT(showEntry()));

}

void NewErrorManage::init_table()
{
    QSqlQuery  sqlquery("",DBConnection::db);
    sqlquery.exec("select  errorcode,errorinfo,measure,time  from errormanage");
    int itemCount=0;
    switchTableModel->clear();
    switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("出错代码")));
    switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("出错信息")));
    switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("建议措施")));
    switchTableModel->setHorizontalHeaderItem(3,new QStandardItem(tr("录入时间")));

    while(sqlquery.next())
    {
        switchTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        switchTableModel->setItem(itemCount,1,new QStandardItem(sqlquery.value(1).toString()));
        switchTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));
        switchTableModel->setItem(itemCount,3,new QStandardItem(sqlquery.value(3).toString()));
        itemCount++;
    }
    sqlquery.finish();
    sqlquery.clear();

    ui->tableview->setModel(switchTableModel);
}

void NewErrorManage::iniView()
{
    ui->tableview->sortByColumn (0,Qt::AscendingOrder);
    ui->tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableview->horizontalHeader()->setStretchLastSection(true);
    ui->tableview->verticalHeader()->setVisible (false);
    ui->tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableview->setAutoFillBackground (true);

}

void NewErrorManage::setViewSize()
{
    int wi=this->width()*9/10;
    ui->tableview->setColumnWidth(0,wi*1/12);
    ui->tableview->setColumnWidth(1,wi*5/12);
    ui->tableview->setColumnWidth(2,wi*5/12);
    ui->tableview->setColumnWidth(3,wi*1/12);
}

void NewErrorManage::setManageBtnVisible(bool isVisibled)
{
    ui->btn_add->setVisible(isVisibled);
    ui->btn_delete->setVisible(isVisibled);
}

void NewErrorManage::editEntry()
{

    QModelIndexList index =ui->tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        QString errorinfo;
        QString measure;
        //QString remark;
        //int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row, 0, QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        errorcode = tb_in_da.toString();

        QModelIndex nameIndex = switchTableModel->index(row, 1, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        errorinfo = varName.toString();

        QModelIndex locationIndex = switchTableModel->index(row, 2, QModelIndex());
        QVariant vaLocation= switchTableModel->data(locationIndex, Qt::DisplayRole);
        measure = vaLocation.toString();


        /*
        QModelIndex communityIndex = switchTableModel->index(row, 4, QModelIndex());
        QVariant varCommunity = switchTableModel->data(communityIndex, Qt::DisplayRole);
        remark = varCommunity.toString();
*/
        //! [4b]
//        AddErrorDialog aDialog;
        NewAddErrorDialog aDialog;
        aDialog.setWindowTitle(tr("修改故障信息"));
        aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,
                     (QApplication::desktop()->height()-aDialog.height())/2);
        aDialog.setText(errorcode,errorinfo,measure);
        aDialog.setDialogFlag(false);
        if (aDialog.exec())
        {

            QString newCode = aDialog.getCode();
            QString newInfo = aDialog.getInfo();
            QString newMeasure = aDialog.getMeasure();

            if (!newCode.isEmpty ()&&!newInfo.isEmpty ()&&!newMeasure.isEmpty ())
            {
                QSqlQuery query("",DBConnection::db);;
                QString update_sql = "update errormanage set errorinfo=?,measure=? ,time=? where errorcode=? ";
                query.prepare(update_sql);
                query.bindValue(0,newInfo);
                query.bindValue(1,newMeasure);
                query.bindValue(2,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(3,newCode);
                //query.bindValue(3,table_index);
                query.exec();
                query.finish();
                query.clear();
                init_table();
                setViewSize();
            }
            else{
                QMessageBox::information(0,"信息不完整","请填写完整信息");
            }
        }
        ui->tableview->selectRow(row);
        ui->tableview->setFocus();
    }
}

void NewErrorManage::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
//    AddErrorDialog aDialog;
    NewAddErrorDialog aDialog;
    aDialog.setDialogFlag(true);
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);
    if (aDialog.exec()) {
//        QString errorcode = aDialog.codeLineEdit->text().trimmed();
//        QString errorinfo = aDialog.infoLineEdit->toPlainText().trimmed();
//        QString measure = aDialog.measureLineEdit->toPlainText().trimmed();

        QString errorcode = aDialog.getCode().trimmed();
        QString errorinfo = aDialog.getInfo().trimmed();
        QString measure = aDialog.getMeasure().trimmed();

        if(errorcode==""||errorinfo==""||measure=="")
        {
            QMessageBox::information(0,"信息错误","请填写详细内容信息!");
            return;
        }
        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("select count(*) from errormanage where errorcode=?");
        sqlquery.bindValue(0,errorcode);
        sqlquery.exec();
        sqlquery.next();
        int res_num = sqlquery.value(0).toInt();
        if(res_num>0)
        {
            QMessageBox::information(0,"信息错误","出错代码重复");
        }
        else
        {
            sqlquery.prepare("insert into errormanage (errorcode,errorinfo,measure,time)  values(?,?,?,?)");
            sqlquery.bindValue(0,errorcode);
            sqlquery.bindValue(1,errorinfo);
            sqlquery.bindValue(2,measure);
            sqlquery.bindValue(3,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            sqlquery.exec();

            init_table();
            setViewSize();
        }
        sqlquery.finish();
        sqlquery.clear();
    }
}

void NewErrorManage::removeEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    switch(QMessageBox::question(0,tr("删除记录"),tr("是否删除?"),
                                 QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
    {
    case QMessageBox::Cancel:
        return;
    }
    QModelIndexList index = ui->tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        //int table_index;
        int row = index.at(0).row();

        QModelIndex nameIndex = switchTableModel->index(row, 0, QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex, Qt::DisplayRole);
        errorcode = varName.toString();

        QSqlQuery  sqlquery("",DBConnection::db);
        QString delete_sql = "delete from errormanage where errorcode=?";
        sqlquery.prepare(delete_sql);
        sqlquery.addBindValue(errorcode);
        sqlquery.exec();
        sqlquery.finish();
        sqlquery.clear();
        init_table();
        setViewSize();

    }
}

void NewErrorManage::showEntry()
{
    QModelIndexList index = ui->tableview->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString errorcode;
        QString errorinfo;
        QString measure;
        //QString remark;
        //int table_index;
        int row = index.at(0).row ();

        QModelIndex tb_in_Index = switchTableModel->index(row,0,QModelIndex());
        QVariant tb_in_da = switchTableModel->data(tb_in_Index, Qt::DisplayRole);
        errorcode = tb_in_da.toString();


        QModelIndex nameIndex = switchTableModel->index(row,1,QModelIndex());
        QVariant varName = switchTableModel->data(nameIndex,Qt::DisplayRole);
        errorinfo = varName.toString();


        QModelIndex locationIndex = switchTableModel->index(row,2,QModelIndex());
        QVariant vaLocation= switchTableModel->data(locationIndex,Qt::DisplayRole);
        measure = vaLocation.toString();


        /*
        QModelIndex communityIndex = switchTableModel->index(row, 4, QModelIndex());
        QVariant varCommunity = switchTableModel->data(communityIndex, Qt::DisplayRole);
        remark = varCommunity.toString();
        */
        //! [4b]
//        AddErrorDialog aDialog;
        NewAddErrorDialog aDialog;
        aDialog.setWindowTitle(tr("查看故障信息"));
        aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,(QApplication::desktop()->height()-aDialog.height())/2);

//        aDialog.codeLineEdit->setText(errorcode);
//        aDialog.infoLineEdit->setText(errorinfo);
//        aDialog.measureLineEdit->setText(measure);

        aDialog.setText(errorcode,errorinfo,measure);
        aDialog.setDialogFlag2(false);

        aDialog.exec();
        ui->tableview->selectRow(row);
        ui->tableview->setFocus();
    }
}

void NewErrorManage::slot_init()
{
    init_table();
    setViewSize();
}

NewErrorManage::~NewErrorManage()
{
    delete ui;
}

