#include "newshowloghistory.h"
#include "ui_newshowloghistory.h"
#include "mainwindow.h"

#include<QTextBrowser>

NewShowLogHistory::NewShowLogHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewShowLogHistory)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height());
    calendar = NULL;
//    this->setFixedSize(QApplication::desktop()->width()*6/7,QApplication::desktop()->height()*6/7);
    connect(ui->query,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->clearTime,SIGNAL(clicked()),this,SLOT(clearDate()));
    connect(ui->starttimeBtn,SIGNAL(clicked()),this,SLOT(showcalendar()));
}

void NewShowLogHistory::search()
{
    QString date_st=ui->starttime->text();    //get the date need to be searched
    //showLog->clear();   //refresh the log area

    //本日日志文件的名称，此时名称还不含序号信息
    //QString startTime = starttime.toString("yyyyMMdd");
    int i ;
    QFile file;

    for(i=0;i<MainWindow::logFileNumb; i++)
    {
        logFile=MainWindow::logPath+QString::number(i)+"_"+ date_st +  "_log.txt";
        qDebug()<<"look for: i="<< i << "   FileName =  "<<logFile;
        file.setFileName(logFile);
        if (file.exists()) { break; }
    }
    if (i==MainWindow::logFileNumb )
    {  //没有找到当前的日志文件
       return;
    }

    file.setFileName(logFile);
    ui->showLog->clear();

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,tr("错误"),tr("日志文件打开失败"),QMessageBox::Ok);
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

void NewShowLogHistory::clearDate()
{
    ui->starttime->clear();
}

void NewShowLogHistory::showcalendar()
{
    if(!calendar)
    {
        calendar = new CalendarDialog();
    }
    calendar->setMinimumSize(400,150);
    calendar->move(QCursor::pos().x()-218,QCursor::pos().y()+ ui->starttimeBtn->height());
    connect(calendar,SIGNAL(checkdate(const QDate&)),this,SLOT(setdate(const QDate&)));
    calendar->show();
}

void NewShowLogHistory::setdate(const QDate &date_checked)
{
    QDate date=date_checked;
    QString datestr=date.toString("yyyy-MM-dd");
    ui->starttime->setText(datestr);
    ui->starttime->setFocus();
    calendar->close();
}

NewShowLogHistory::~NewShowLogHistory()
{
    delete ui;
}
