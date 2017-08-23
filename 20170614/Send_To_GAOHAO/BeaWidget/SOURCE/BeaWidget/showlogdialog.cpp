#include "showlogdialog.h"
#include "ui_showlogdialog.h"
#include "mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QPalette>
#include<QDesktopWidget>
#include<QDir>
#include <fstream>
#include <iostream>
#include<QSqlQuery>
#include<QDate>

ShowLogDialog::ShowLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowLogDialog)
{
    ui->setupUi(this);
    mainLayout=new QVBoxLayout(this);
    hMain=new  QHBoxLayout(this);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(26,28,26));  //background color
    palette.setColor(QPalette::WindowText,QColor("white"));
    this->setPalette(palette);
    setWindowTitle(tr("日志信息"));
    //this->setFixedSize(QApplication::desktop()->height()*4/5,QApplication::desktop()->height()*4/5);
    this->setFixedSize(QApplication::desktop()->width()*6/7,QApplication::desktop()->height()*6/7);     //yangmeng 161031 调整界面布局
    showLog=new QTextBrowser(this);

    ok=new commonButton(this);
    ok->setText("刷新");
   // ok->setFixedSize();
    mainLayout->addWidget(showLog);             //yangmeng 161101
    //    mainLayout->addWidget(ok);                //yangmeng 161031 隐藏刷新按钮
     //  hMain->addStretch(10);                             //yangmeng 161031 调整界面布局
        hMain->addLayout(mainLayout);
    //    hMain->addStretch(10);                            //yangmeng 161031 调整界面布局
    //      hMain->setMargin(10);                           //yangmeng 161031 调整界面布局
        show();
        connect(ok,SIGNAL(click()),this,SLOT(refresh()));
        ok->hide();     //yangmeng 161031 隐藏刷新按钮

        //从配置文件中读取日志目录,文件大小和最多存储的文件个数---qhy 2016.11.3
//        std::ifstream file1("logconfig.txt");
//        char ls_logdir[100];
//        file1>>ls_logdir;    //log目录
//        file1.close();
//        currentNum=0;
//        QString ls_path =QDir::currentPath() + QString(QLatin1String(ls_logdir));
//        QString startTime = QDate::currentDate().toString("yyyymmdd");
//        MainWindow::logFileName=ls_path+QString::number(currentNum)+ "_"+ startTime +  "_log" +".txt";
}

ShowLogDialog::~ShowLogDialog()
{
    delete ui;
    if(ok)delete ok;
    if(showLog)delete showLog;
    if(mainLayout)delete mainLayout;
}


void ShowLogDialog::addRecord(QString newRecord)      //  //yangmeng 161026 日志实时更新
{
    showLog->append(newRecord);
}

void ShowLogDialog::show()
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
        showLog->append(temp);
    }
}

void ShowLogDialog::refresh()//点击按钮刷新
{
    showLog->clear();
    //调用静态函数获得当前日志文件名
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,tr("错误8"),tr("日志文件打开失败"),QMessageBox::Ok);
        return;
    }
    QTextStream in(&file);
    QString temp;
    while(!in.atEnd())
    {
        temp=in.readLine();
        showLog->append(temp);

    }
}


