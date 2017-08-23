#include "capturedialog.h"
#include "ui_capturedialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include<QDir>
#include<QDesktopWidget>
#include<QDomDocument>
#include<QMessageBox>
#include<QFile>
#include<fstream>
#include<iostream>
#include<QSqlQuery>
capturedialog::capturedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::capturedialog)
{
    ui->setupUi(this);
    captureThread=new CaptureThread();
    captureThread1 = new CaptureThread(); // gaohao Add 捕获多个镜像口数据

    start=new commonButton(this);
    stop=new commonButton(this);
    close=new commonButton(this);
    start->setText("开始");
    stop->setText("停止");
    close->setText("确定");
    start->setFixedSize(110,30);
    stop->setFixedSize(110,30);
    close->setFixedSize(110,30);

    mainLayout1=new QHBoxLayout;
    mainLayout2=new QHBoxLayout;
    mainLayout1->addWidget(start);
    mainLayout1->addWidget(stop);
    mainLayout2->addStretch(1);
    mainLayout2->addWidget(close);
    mainLayout2->addStretch(1);

    topLayout=new QVBoxLayout;
    topLayout->addLayout(mainLayout1);
    topLayout->addLayout(mainLayout2);

    setFixedSize(QApplication::desktop()->width()*1/4,QApplication::desktop()->height()*1/4);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(26,28,26));  //background color
    //palette.setColor(QPalette::WindowText,QColor("white"));
    this->setPalette(palette);

    setWindowTitle(tr("端口镜像"));
   // setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);
   setLayout(topLayout);
   connect(start,SIGNAL(click()),this,SLOT(slot_start()));
   connect(stop,SIGNAL(click()),this,SLOT(slot_stop()));
   connect(close,SIGNAL(click()),this,SLOT(accept()));
   //connect(okButton, SIGNAL(click()), this, SLOT(accept()));

   setWindowFlags(Qt::Tool|Qt::FramelessWindowHint);        //yangmeng 161030 统一窗口样式
}

capturedialog::~capturedialog()
{
    delete ui;
    if(captureThread) delete captureThread;
     if(captureThread1) delete captureThread1;    // gaohao Add 捕获多个镜像口数据
}

void capturedialog::slot_start()
{
    //从配置文件中读取镜像目录,文件大小和最多存储的文件个数---qhy 2016.11.3
    ifstream file1("imagedir.txt");
    char imagedir[100], ls_filenum[20], ls_filesize[20];
    double  li_filenum, li_filesize;

    file1>>imagedir;    //镜像目录
    file1>>ls_filenum;  //最多存储的文件个数
    file1>>ls_filesize;   //文件大小
    file1.close();
    QString ls_path = QString(QLatin1String(imagedir));
     li_filenum =QString(QLatin1String(ls_filenum)).toDouble();
     li_filesize =QString(QLatin1String( ls_filesize)).toDouble();

    QDir dir(ls_path );
   // QDir dir(currentApplicationpath+"/" + QString(QLatin1String(imagedir)));
    if (!dir.exists())
    {
        dir.mkpath(ls_path);   //从配置文件中读取镜像目录，若目录不存在，创建---qhy 2016.11.3
        //dir.mkpath(currentApplicationpath+"/ImageFile");
    }

    // gaohao Add 读取当前网卡的名称是来自于sz_name.txt
        ifstream file("sz_name.txt");
        char g_szIfName[100];
        char g_szIfName1[100];
        g_szIfName[0] = ';';   //由于可能只有一个网卡接口，给初始值
        g_szIfName1[0] =';';
        file>>g_szIfName;
        file>>g_szIfName1;

        file.close();

        //  从配置文件中读取镜像目录---qhy 2016.11.3  /run/media/root/3625-19EE/ImageFile
        captureThread->setFile(g_szIfName,li_filenum, li_filesize*1024*1024, ls_path);///home/test 文件保存路径改为固定值，不再允许用户设置        //yangmeng 161101 文件路径为1T硬盘
        captureThread->setAdapterID(1);     //yangmeng 161030 设置当前网卡序号为1，以便区分最新记录序号
        captureThread->start();

        // gaohao Add 支持双镜像口
        if (g_szIfName==g_szIfName1 ) return ;  //如果两个网口相同，只起一个线程--qhy 2016.10.26    ls_path
        if (g_szIfName1[0] != ';')  {
            captureThread1->setFile(g_szIfName1,li_filenum, li_filesize*1024*1024,ls_path);///home/test 文件保存路径改为固定值，不再允许用户设置   //yangmeng 161101 文件路径为1T硬盘
            captureThread1->setAdapterID(2);     //yangmeng 161030 设置当前网卡序号为2，以便区分最新记录序号
            captureThread1->start();
        }
        //2016.10.26 qhy update end

       start->setEnabled(false);
       stop->setEnabled(true);
}

void capturedialog::slot_stop()
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

     start->setEnabled(true);
     stop->setEnabled(false);
}

void capturedialog::slot_close()
{
 //  close();
}
