#include "usermanage.h"
#include "ui_usermanage.h"
#include "adduserdialog.h"
#include"connection.h"
#include"logindialog.h"
#include <QtGui>
#include <QMessageBox>
#include <QSqlRecord>
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QDate>
#include "mainwindow.h"
#include "newadduserdialog.h"

UserManage::UserManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManage)
{
    qDebug()<<__FILE__<<__LINE__<<"\n"
           <<"初始化 UserManage"
           <<"\n";
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    ui->widget->setFixedSize(this->width(),this->height());
    ui->tableView->setFixedWidth(ui->widget->width());
    ui->tableView->setMinimumHeight(ui->widget->height()*8.5/10);
//    ui->widget_button->setFixedWidth(ui->tableView->width());
//    ui->widget_button->setFixedHeight(60);
    userTableModel = new myStandardItemModel();
    ui->tableView->setModel(userTableModel);

    ui->tableView->sortByColumn (0,Qt::AscendingOrder);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->setVisible (false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAutoFillBackground (true);
    ui->tableView->verticalHeader()->setDefaultSectionSize(40);

    init_table();
    setViewSize();

    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editEntry()));
    connect(ui->pushButton_remove,SIGNAL(clicked()),this,SLOT(removeEntry()));
    connect(ui->pushButton_edit,SIGNAL(clicked()),this,SLOT(editEntry()));
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(addEntry()));
}

void UserManage::setViewSize()
{
    int wi=ui->tableView->width()/3-3;
    ui->tableView->setColumnWidth(0,wi);
    ui->tableView->setColumnWidth(1,wi);
//    ui->tableView->setColumnWidth(2,wi);
}

void UserManage::init_table()
{
    QSqlQuery  sqlquery("",DBConnection::db);
    sqlquery.exec("select  *  from user");
    int itemCount=0;
    userTableModel->clear();
    userTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("用户名")));
    userTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("密码")));
    userTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("权限")));
    while(sqlquery.next())
    {
        userTableModel->setItem(itemCount,0,new QStandardItem(sqlquery.value(0).toString()));
        userTableModel->setItem(itemCount,1,new QStandardItem("*****"));//sqlquery.value(1).toString()
        userTableModel->setItem(itemCount,2,new QStandardItem(sqlquery.value(2).toString()));

        itemCount++;
    }
    sqlquery.finish();
    sqlquery.clear();
}
UserManage::~UserManage()
{
    if(userTableModel)delete userTableModel;
    delete ui;
}



//! [2]
void UserManage::addEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
//    AddUserDialog aDialog;
    NewAddUserDialog aDialog;       //Shang add in 2017.03.07
    aDialog.setWindowTitle ("添加用户");
    aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,
                  (QApplication::desktop()->height()-aDialog.height())/2);


    if (aDialog.exec()) {
//        QString name = aDialog.userNameLineEdit->text();
//        QString password = aDialog.passwordLineEdit->text();
//        QString userlevel= aDialog.userlevelEdit->currentText ();

        QString name = aDialog.getUserName();
        QString password = aDialog.getPassword();
        QString userlevel= aDialog.getUserLevel();

        if(name==""||password==""||userlevel=="")
        {
            QMessageBox::information(0,"信息错误","请填写详细内容信息!");
            return;
        }
        addEntry(name, password,userlevel);
    }

}


//! [2]
void UserManage::addEntry (QString name, QString password,QString userlevel) //插入记录
{

    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QSqlQuery sqlquery("",DBConnection::db);
    sqlquery.prepare("select count(*) from user where account=?");
    sqlquery.bindValue(0,name);
    sqlquery.exec();
    sqlquery.next();
    int res_num=sqlquery.value(0).toInt();
    if(res_num>0)
    {
        QMessageBox::information(0,"信息错误","该用户名已注册");
        return ;
    }
    else
    {

        sqlquery.prepare("insert into user (account,password,level)  values(?,?,?)");
        sqlquery.bindValue(0,name);
        sqlquery.bindValue(1,password);
        sqlquery.bindValue(2,userlevel);

        sqlquery.exec();

        init_table();
        setViewSize();
   }
    sqlquery.finish();
    sqlquery.clear();

    QString newRecord ;  //yangmeng 161026 日志实时更新

    //写入日志文件，qhy 2016.11.29
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);

    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QMessageBox::information(0,tr("错误11"),tr("日志文件打开失败！"),QMessageBox::Ok);
    }
    QTextStream out(&file);
    newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [用户管理]")+tr("增加")+name;
    out<<newRecord<<endl;
    file.close();

    emit signal_addRecord(newRecord);
}

//! [4a]
void UserManage::editEntry()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index = ui->tableView->selectionModel()->selectedRows ();

    if (!index.isEmpty ())
    {
        QString name;
        QString password;
        QString userlevel;
        int row = index.at(0).row ();

        QModelIndex nameIndex = userTableModel->index(row,0, QModelIndex());
        QVariant varName = userTableModel->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QModelIndex passwordIndex = userTableModel->index(row,1, QModelIndex());
        QVariant varAddr = userTableModel->data(passwordIndex, Qt::DisplayRole);
        password = varAddr.toString();

        QModelIndex userlevelIndex = userTableModel->index(row,2, QModelIndex());
        QVariant varuserlevel = userTableModel->data(userlevelIndex, Qt::DisplayRole);
        userlevel = varuserlevel.toString();

        //! [4b]
//        AddUserDialog aDialog;

        NewAddUserDialog aDialog;

        aDialog.setWindowTitle("修改用户");
        aDialog.setNameEn(false);
        //aDialog.userNameLineEdit->setReadOnly (true);
//        aDialog.userNameLineEdit->setText(name);
//        aDialog.passwordLineEdit->setText(password);
      //  aDialog.userlevelEdit->setCurrentText (userlevel);
//         aDialog.userlevelEdit->setCurrentIndex(0);// (userlevel);

        aDialog.setInfoShow(name,password,userlevel);
        aDialog.move((QApplication::desktop()->width()-aDialog.width())/2,
                      (QApplication::desktop()->height()-aDialog.height())/2);

        if (aDialog.exec())
        {
//            QString newUser = aDialog.userNameLineEdit->text();
//            QString newPassword = aDialog.passwordLineEdit->text ();
//            QString newuserlevel = aDialog.userlevelEdit->currentText ();

            QString newUser = aDialog.getUserName();
            QString newPassword = aDialog.getPassword();
            QString newuserlevel = aDialog.getUserLevel();

            if (!newUser.isEmpty ()&&!newPassword.isEmpty ()&&!newuserlevel.isEmpty ())
            {

                QSqlQuery query("",DBConnection::db);;
                QString update_sql = "update user set password=?,level=? where account=? ";
                query.prepare(update_sql);
                query.bindValue(0,newPassword);
                query.bindValue(1,newuserlevel);
                query.bindValue(2,newUser);
                query.exec();

                init_table();
                setViewSize();
                query.finish();
                query.clear();

                QString newRecord ;  //yangmeng 161026 日志实时更新

                //写入日志文件
                //调用静态函数获得当前日志文件名
                MainWindow::setLogfileName();
                QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29
                if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
                {
                    QMessageBox::information(0,tr("错误12"),tr("日志文件打开失败！"),QMessageBox::Ok);
                }
                QTextStream out(&file);
                newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [用户管理]")+tr("修改")+newUser;
                out<<newRecord<<endl;
                file.close();

                emit signal_addRecord(newRecord);
            }
            else{
                QMessageBox::information(0,"空项","请将信息填写完整");
            }
        }    
    }
}
//! [4b]


void UserManage::removeEntry () //删除当前行
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QModelIndexList index =ui->tableView->selectionModel()->selectedRows ();
    switch(QMessageBox::question(0,tr("删除用户"),tr("是否删除?"),
              QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Ok))
      {
      case QMessageBox::Cancel:
        return;
   }
    if (!index.isEmpty ())
    {
        QString name;
        int table_index;
        int row = index.at(0).row ();

        QModelIndex nameIndex = userTableModel->index(row, 0, QModelIndex());
        QVariant varName = userTableModel->data(nameIndex, Qt::DisplayRole);
        name = varName.toString();

        QSqlQuery sqlquery("",DBConnection::db);
        sqlquery.prepare("delete from user where account=?");
        sqlquery.bindValue(0,name);
        sqlquery.exec();
        init_table();
        setViewSize();
        sqlquery.exec();
        sqlquery.finish();
        sqlquery.clear();

        QString newRecord ; //yangmeng 161026 日志实时更新

        //写入日志文件
        //调用静态函数获得当前日志文件名
        MainWindow::setLogfileName();
        QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29
        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QMessageBox::information(0,tr("错误13"),tr("日志文件打开失败！"),QMessageBox::Ok);
        }
        QTextStream out(&file);
        newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [用户管理]")+tr("删除")+name;
        out<<newRecord<<endl;
        file.close();

        emit signal_addRecord(newRecord);

    }

}
