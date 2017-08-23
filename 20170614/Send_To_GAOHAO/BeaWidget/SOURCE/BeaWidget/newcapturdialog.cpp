#include "newcapturdialog.h"
#include "ui_newcapturdialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDir>
#include <QDesktopWidget>
#include <QDomDocument>
#include <QMessageBox>
#include <QFile>
#include <fstream>
#include <iostream>
#include <QSqlQuery>

NewCapturDialog::NewCapturDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCapturDialog)
{
    ui->setupUi(this);
    capturIp = QHostAddress("127.0.0.1");
    capturPort = 13999;
    captureThread=new CaptureThread();
    captureThread1 = new CaptureThread(); // gaohao Add 捕获多个镜像口数据

    ui->start->setFixedSize(110,30);
    ui->stop->setFixedSize(110,30);
    ui->close->setFixedSize(110,30);

    this->setFixedSize(QApplication::desktop()->width()*1/4,QApplication::desktop()->height()*1/4);
    this->setWindowTitle(tr("端口镜像"));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(slot_start()));
    connect(ui->stop,SIGNAL(clicked()),this,SLOT(slot_stop()));
    connect(ui->close,SIGNAL(clicked()),this,SLOT(accept()));

//    this->setWindowFlags(Qt::FramelessWindowHint);        //yangmeng 161030 统一窗口样式
    setWindowFlags(Qt::Tool|Qt::WindowCloseButtonHint);
}

NewCapturDialog::~NewCapturDialog()
{
    delete ui;
    if(captureThread) delete captureThread;
    if(captureThread1) delete captureThread1;    // gaohao Add 捕获多个镜像口数据
}

void NewCapturDialog::slot_start()
{
    /*
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
    memset(g_szIfName,0,100);
    memset(g_szIfName1,0,100);
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
    if(strcmp(g_szIfName,g_szIfName1)==0)
    {
        return;
    }  //如果两个网口相同，只起一个线程--qhy 2016.10.26    ls_path

    if (g_szIfName1[0] != ';')  {
        captureThread1->setFile(g_szIfName1,li_filenum, li_filesize*1024*1024,ls_path);///home/test 文件保存路径改为固定值，不再允许用户设置   //yangmeng 161101 文件路径为1T硬盘
        captureThread1->setAdapterID(2);     //yangmeng 161030 设置当前网卡序号为2，以便区分最新记录序号
        captureThread1->start();
    }
//    //2016.10.26 qhy update end
    */

    //Shang chang this code.
    //Now ,We use UDP to have message,this function move to the other application,we emit the udp message to the application.
    sendUDPSocket(1);

    ui->start->setEnabled(false);
    ui->stop->setEnabled(true);
}

void NewCapturDialog::slot_stop()
{
    /*
//    captureThread->stop();
//    captureThread->terminate();
//    if(captureThread) delete captureThread;
//    captureThread=NULL;
//    captureThread=new CaptureThread();

//    // gaohao Add 支持多个镜像口
//    captureThread1->stop();
//    captureThread1->terminate();
//    if(captureThread1) delete captureThread1;
//    captureThread1=NULL;
//    captureThread1=new CaptureThread();
    */

    sendUDPSocket(0);

    ui->start->setEnabled(true);
    ui->stop->setEnabled(false);
}

void NewCapturDialog::sendUDPSocket(int type)
{
    getTargetIp();
    QUdpSocket myudp;
    int udptype = type;
    QByteArray datagram;
    QDataStream out(&datagram,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out<<udptype;
    myudp.writeDatagram(datagram,capturIp,capturPort);
}

// 获取端口镜像备份IP地址
void  NewCapturDialog::getTargetIp()
{
    ifstream file("captur.txt");
    char ip[50], port[20];
    file>>ip;        //ip
    file>>port;      //port
    file.close();

    capturIp = QString(QLatin1String(ip));
    capturPort = QString(QLatin1String(port)).toInt();
}

void NewCapturDialog::slot_close()
{
}
