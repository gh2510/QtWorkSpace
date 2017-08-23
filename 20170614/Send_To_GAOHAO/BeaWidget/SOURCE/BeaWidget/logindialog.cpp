#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainframe.h"
#include "defcommon.h"
#include <QMessageBox>
#include "pushbutton_diy.h"
#include"connection.h"
#include <QApplication>
#include<QDebug>
#include <QTextCodec>
#include <QFile>
#include<QTextStream>
#include<QDate>
#include <QStringList>
#include <QDir>
#include <QPixmap>
#include <QSqlQuery>
#include "mainwindow.h"
bool userLevel=0;
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->btn_manageLogin,SIGNAL(clicked()),this,SLOT(on_loginBtn_clicked()));
    connect(ui->btn_defaultLogin,SIGNAL(clicked()),this,SLOT(on_defaultLoginBtn_clicked()));
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void LoginDialog::quit()
{
    userLevel=1;         //yangmeng 161022 tiaoshi
    QDialog::reject();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

//默认用户登录按钮响应  yangmeng 161023
void LoginDialog::on_defaultLoginBtn_clicked()
{
    userLevel=1;

    QString newRecord;      //yangmeng 161026 日志实时更新

    //调用静态函数获得当前日志文件名
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29

    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QMessageBox::information(this,tr("错误2"),tr("日志文件打开失败！"),QMessageBox::Ok);
    }
    QTextStream out(&file);
    newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [登录]")+tr("公用账户");//yangmeng 161026 日志字符乱码
    out<<newRecord<<endl;
    file.close();

    emit signal_addRecord(newRecord);

    QDialog::accept();
}

void LoginDialog::on_loginBtn_clicked()
{
    userLevel=0;
    QDialog::accept();  //yangmeng 161021 tiaoshi
    return;

    if(ui->pwdlineEdit->text().trimmed().isEmpty()||ui->usernamelineEdit->text().trimmed().isEmpty())
    {
        QMessageBox::information(this,tr("注意"),tr("请先输入用户名和密码再登录！"),QMessageBox::Ok);
        ui->usernamelineEdit->setFocus();
    }
    else
    {
        QString username = ui->usernamelineEdit->text().trimmed();

        QSqlQuery query("",DBConnection::db);
        query.exec("select password,level from user where account='"+username+"'");
        query.next();
        QString a=query.value(1).toString();
        if(a=="管理员")
        {
             userLevel=0;
        }
        else if(a=="普通用户")
        {
            userLevel=1;
        }
        if(query.value(0).toString()== ui->pwdlineEdit->text().trimmed())
        {
            QString newRecord;      //yangmeng 161026 日志实时更新

            //调用静态函数获得当前日志文件名
            MainWindow::setLogfileName();
            QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29

            if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
            {
                QMessageBox::information(this,tr("错误3"),tr("日志文件打开失败！"),QMessageBox::Ok);
            }
            QTextStream out(&file);
            newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [登录]")+ui->usernamelineEdit->text().trimmed();
            out<<newRecord<<endl;
            file.close();

            emit signal_addRecord(newRecord);

            QDialog::accept();
        }
        else
        {
            QMessageBox::warning(this,tr("用户名或密码错误"),tr("请输入正确的用户名和密码！"),QMessageBox::Ok);
            ui->pwdlineEdit->clear();
            ui->pwdlineEdit->setFocus();
        }
        query.finish();
        query.clear();
    }
}
