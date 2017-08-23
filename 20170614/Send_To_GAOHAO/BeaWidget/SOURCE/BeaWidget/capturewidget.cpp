#include "capturewidget.h"
#include "ui_capturewidget.h"
#include <QDir>
#include <QDesktopWidget>
#include <QDomDocument>
#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QApplication>
#include "logindialog.h"
#include <fstream>
#include <iostream>

capturewidget::capturewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::capturewidget)
{
    ui->setupUi(this);

    //setStyleSheet("font-size:15px;color:white;font-family:'wenquanyi'");
    captureThread=new CaptureThread();
    captureThread1 = new CaptureThread(); // gaohao Add 捕获多个镜像口数据

   QPalette   pal;
   pal.setColor(QPalette::WindowText, QColor(255,255,255));
  // ui->label->setPalette(pal);
   ui->label_2->setPalette(pal);
   setFixedSize(QApplication::desktop()->width()*4/6,QApplication::desktop()->height()*4/6);
   ui->tableView->horizontalHeader()->setStyleSheet
        ("QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "stop:0 #03A5A4, stop: 0.5 #0E5D6A, stop:1 #03A5A4);"
        "color: white;padding-left: 4px;border: 1px solid #6c6c6c;}"
        "QHeaderView::section:checked{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #3C5037, stop: 0.5 #436252, stop:1 #3C5037);}");
//   ui->pushButton_set->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
//                          " color: white;   border-radius: 10px;  border: 1px groove gray;"
//                                       "border-style: outset;}"
//                                      "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
//                                      "QPushButton:pressed{background-color:rgb(37, 60, 65);"
//                          " border-style: outset; }"
//                                     "QPushButton:disabled{color:gray;}");
//   ui->pushButton_set->setFixedSize(80,30);

   ui->pushButton_start->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                          " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                       "border-style: outset;}"
                                      "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                      "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                          " border-style: outset; }"
                                       "QPushButton:disabled{color:gray;}");
   ui->pushButton_start->setFixedSize(80,30);

   ui->pushButton_stop->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                          " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                       "border-style: outset;}"
                                      "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                      "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                          " border-style: outset; }"
                                      "QPushButton:disabled{color:gray;}");
   ui->pushButton_stop->setFixedSize(80,30);

   ui->pushButton_reset->setStyleSheet("QPushButton{background-color:rgb(37,60,65);"
                          " color: white;   border-radius: 10px;  border: 1px groove gray;"
                                       "border-style: outset;}"
                                      "QPushButton:hover{background-color:rgb(12,92,104); color: white;}"
                                      "QPushButton:pressed{background-color:rgb(37, 60, 65);"
                          " border-style: outset; }"
                                       "QPushButton:disabled{color:gray;}");
   ui->pushButton_reset->setFixedSize(80,30);
   switchTableModel=new myStandardItemModel();
   switchTableModel->clear();

   ui->tableView->setModel(switchTableModel);
   ui->tableView->sortByColumn (0,Qt::AscendingOrder);
   ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
   ui->tableView->horizontalHeader()->setStretchLastSection(true);
   ui->tableView->verticalHeader ()->setVisible (false);
   ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
   //ui->tableView->setFixedHeight(QApplication::desktop()->height()*3/4);
   ui->tableView->setAutoFillBackground (true);


   switchTableModel->setHorizontalHeaderItem(0,new QStandardItem(tr("序号")));
   switchTableModel->setHorizontalHeaderItem(1,new QStandardItem(tr("数据分类")));
   switchTableModel->setHorizontalHeaderItem(2,new QStandardItem(tr("选择")));
   ui->tableView->setColumnWidth(0,30);
   ui->tableView->setColumnWidth(1,100);
   ui->tableView->setColumnWidth(2,30);
   ui->tableView->setModel(switchTableModel);
   ui->pushButton_stop->setEnabled(false);
   ui->spinBox_num->setValue(100);
   ui->spinBox_size->setValue(10);

   // gaohao 隐藏部分控件显示，只显示控制的部分
   ui->label_2->hide();
   ui->line_2->hide();
   ui->label_3->hide();
   ui->label_4->hide();
   ui->label_5->hide();
   ui->pushButton_reset->hide();
   ui->tableView->hide();
   ui->spinBox_num->hide();
   ui->spinBox_size->hide();
   if(userLevel)//普通用户不可修改
       {
       ui->spinBox_num->setEnabled(false);
       ui->spinBox_size->setEnabled(false);
   }
   initTabel();
}

capturewidget::~capturewidget()
{
    delete ui;
    if(captureThread) delete captureThread; 
     if(captureThread1) delete captureThread1;    // gaohao Add 捕获多个镜像口数据


}

void capturewidget::initTabel()
{
    QFile file("image.xml");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(this," 错误","打开配置文件失败",QMessageBox::Ok);
        return;
    }
    QDomDocument domDocument;
    QString errorMsg="no error";
    int errorLine=0;
    int errorColumn=0;
    if(!domDocument.setContent(&file,&errorMsg,&errorLine,&errorColumn))
    {
        QMessageBox::information(this,"读取配置文件失败",tr(" 第%1行，第%2列：\n%3").arg(errorLine).arg(errorColumn).arg(errorMsg),QMessageBox::Ok);
         return;
    }
    QDomElement root = domDocument.documentElement();
    if(root.tagName()=="Switch")
    {
        QDomNode node=root.firstChild();//port
        int Num=root.childNodes().size();
        typeCount=Num;
        QDomElement element=node.firstChildElement();
        int itemCount=0;
        while(Num)
        {
            switchTableModel->setItem(itemCount,0,new QStandardItem(element.text()));
            element=element.nextSiblingElement();
            switchTableModel->setItem(itemCount,1,new QStandardItem(element.text()));


            QStandardItem *deal=new QStandardItem();
            deal->setCheckable(true);
            deal->setCheckState(Qt::Unchecked);
            deal->setTextAlignment(Qt::AlignCenter);

            switchTableModel->setItem(itemCount,2,deal);
            node=node.nextSibling();
            element=node.firstChildElement();

            itemCount++;
            Num--;
        }
    }
}

void capturewidget::on_pushButton_set_clicked()
{
   for(int i=0;i<typeCount;i++)
   {
       switchTableModel->item(i,2)->setCheckState(Qt::Unchecked);
   }
}

void capturewidget::on_pushButton_start_clicked()
{
//    QString currentApplicationpath=QDir::currentPath();
//    QDir dir(currentApplicationpath+"/ImageFile");
//    if(!dir.exists())
//    {
//        dir.mkpath(currentApplicationpath+"/ImageFile");
//    }

//    // gaohao Add 读取当前网卡的名称是来自于sz_name.txt
//        ifstream file("sz_name.txt");
//        char g_szIfName[100];
//        char g_szIfName1[100];
//        file>>g_szIfName;
//        file>>g_szIfName1;
//        //qDebug()<<"sdf"<<g_szIfName1;
//        file.close();

//     captureThread->setFile(g_szIfName,ui->spinBox_num->text().toDouble(),ui->spinBox_size->text().toDouble()*1024*1024,"ImageFile");///home/test 文件保存路径改为固定值，不再允许用户设置
//     captureThread->start();

//     // gaohao Add 支持双镜像口
//     captureThread1->setFile(g_szIfName1,ui->spinBox_num->text().toDouble(),ui->spinBox_size->text().toDouble()*1024*1024,"ImageFile");///home/test 文件保存路径改为固定值，不再允许用户设置
//     captureThread1->start();

//     ui->pushButton_start->setEnabled(false);
//     ui->pushButton_reset->setEnabled(false);
//     ui->pushButton_stop->setEnabled(true);
//     ui->spinBox_num->setEnabled(false);
//     ui->spinBox_size->setEnabled(false);
}

void capturewidget::on_pushButton_stop_clicked()
{
    captureThread->stop();
    captureThread->terminate();
     if(captureThread) delete captureThread;
     captureThread=NULL;
     captureThread=new CaptureThread();

     // gaohao Add 支持多个镜像口
       captureThread1->stop();
       captureThread1->terminate();
        if(captureThread1) delete captureThread1;
        captureThread1=NULL;
        captureThread1=new CaptureThread();

     ui->pushButton_start->setEnabled(true);
     ui->pushButton_stop->setEnabled(false);
     ui->pushButton_reset->setEnabled(true);
     ui->spinBox_num->setEnabled(true);
     ui->spinBox_size->setEnabled(true);
}

void capturewidget::on_pushButton_reset_clicked()
{
    ui->spinBox_num->setValue(100);
    ui->spinBox_size->setValue(10);

}
