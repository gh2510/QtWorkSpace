#include "newshowlogdialog.h"
#include "ui_newshowlogdialog.h"
#include "mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDir>
#include <fstream>
#include <iostream>
#include <QSqlQuery>
#include <QDate>

NewShowLogDialog::NewShowLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewShowLogDialog)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    setWindowTitle(tr("日志信息"));
    show();
    connect(ui->ok,SIGNAL(clicked()),this,SLOT(refresh()));
//    ui->ok->hide();     //yangmeng 161031 隐藏刷新按钮
}

void NewShowLogDialog::show()
{
    //调用静态函数获得当前日志文件名
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29

    if(!file.open(QIODevice::ReadOnly))
    {
        //QMessageBox::information(this,tr("错误7"),tr("日志文件打开失败"),QMessageBox::Ok);
        return;
    }
    QTextStream in(&file);
    QString temp;
    while(!in.atEnd())
    {
        temp=in.readLine();
        ui->showLog->append(temp);
    }
}

void NewShowLogDialog::refresh()
{
    ui->showLog->clear();
    //调用静态函数获得当前日志文件名
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,tr("错误8"),tr("日志文件打开失败"),QMessageBox::Ok);
        return;
    }
    QTextStream in(&file);
    QString temp;
    while(!in.atEnd())
    {
        temp=in.readLine();
        ui->showLog->append(temp);
    }
}

void NewShowLogDialog::addRecord(QString newRecord)
{
    ui->showLog->append(newRecord);
}

NewShowLogDialog::~NewShowLogDialog()
{
    delete ui;
}


