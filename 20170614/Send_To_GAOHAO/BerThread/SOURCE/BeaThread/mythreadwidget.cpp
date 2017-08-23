#include "mythreadwidget.h"
#include "ui_mythreadwidget.h"

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

MyThreadWidget::MyThreadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyThreadWidget)
{
    ui->setupUi(this);
    this->setGeometry(QApplication::desktop()->width()/2-200,
                      QApplication::desktop()->height()/2-150,400,300);
    myudp = NULL;
    myudp = new MyUdpRecv();
    connect(myudp,SIGNAL(emitRecvUdp(int)),this,SLOT(dealUDP(int)) );

    captureThread=new CaptureThread();
    captureThread1 = new CaptureThread(); // gaohao Add 捕获多个镜像口数据
    ui->plainTextEdit->setReadOnly(true);

}

//处理UDP 信息 Shang-2017.02.27
void MyThreadWidget::dealUDP(int udptype)
{
    if(udptype == 1)
    {
        ui->plainTextEdit->insertPlainText(QString("Recv the UDP start signal: %1\n").arg(udptype));
        slot_start();
    }
    else if(udptype == 0)
    {
        ui->plainTextEdit->insertPlainText(QString("Recv the UDP stop signal: %1\n").arg(udptype));
        slot_stop();
    }
}

void MyThreadWidget::slot_start()
{
    //从配置文件中读取镜像目录,文件大小和最多存储的文件个数---qhy 2016.11.3
    //从配置文件中读取镜像目录---qhy 2016.11.3  /run/media/root/3625-19EE/ImageFile
    ifstream file1("imagedir.txt");
    char imagedir[100], ls_filenum[20], ls_filesize[20];
    double  li_filenum, li_filesize;
    file1>>imagedir;        //镜像目录
    file1>>ls_filenum;      //最多存储的文件个数
    file1>>ls_filesize;     //文件大小
    file1.close();
    QString ls_path = QString(QLatin1String(imagedir));
    li_filenum =QString(QLatin1String(ls_filenum)).toDouble();
    li_filesize =QString(QLatin1String( ls_filesize)).toDouble();

    QDir dir(ls_path );
    if (!dir.exists())
    {
        dir.mkpath(ls_path);   //从配置文件中读取镜像目录，若目录不存在，创建---qhy 2016.11.3
    }

    //读取sz_name.xml文件
    char g_szIfName_1[100];
    char g_szIfName_2[100];
    char g_szLogFileFlag_1[100];
    char g_szLogFileFlag_2[100];
    memset(g_szIfName_1,0,100);
    memset(g_szIfName_2,0,100);
    memset(g_szLogFileFlag_1,0,100);
    memset(g_szLogFileFlag_2,0,100);
    QDomDocument doc;
    QFile file_x("sz_name.xml");
    QString error = "";
    int row = 0, column = 0;
    if (!file_x.open(QIODevice::ReadOnly)) return;
    if(!doc.setContent(&file_x, false, &error, &row, &column)){
        qDebug() << "parse file failed:" << row << "---" << column <<":" <<error;
        file_x.close();
        return ;
    }
    file_x.close();

    int index=1;
    QDomElement root = doc.documentElement();
    QDomNode node = root.firstChildElement();
    while(!node.isNull())
    {
       QDomElement element = node.toElement();
       if(!element.isNull())
       {
           if (element.tagName() == "log")
           {
                if (element.hasAttribute("net"))
                {
                    QString net = element.attributeNode("net").value();
                    char *data = net.toUtf8().data();
                    if(index == 1)
                    {
                        memcpy(g_szIfName_1,data,net.size());
                    }
                    else if(index == 2)
                    {
                        memcpy(g_szIfName_2,data,net.size());
                    }
                }
                if (element.hasAttribute("name"))
                {
                    QString net = element.attributeNode("name").value();
                    char *data = net.toUtf8().data();
                    memcpy(g_szLogFileFlag_1,data,net.size());
                    if(index == 1)
                    {
                        memcpy(g_szLogFileFlag_1,data,net.size());
                    }
                    else if(index == 2)
                    {
                        memcpy(g_szLogFileFlag_2,data,net.size());
                    }
                }
                index++;
           }
       }
       node = node.nextSibling();
    }
    qDebug()<<"读配置文件："<<g_szIfName_1<<g_szLogFileFlag_1<<g_szIfName_2<<g_szLogFileFlag_2;
    //

    ///home/test 文件保存路径改为固定值，不再允许用户设置
    /// //yangmeng 161101 文件路径为1T硬盘
    captureThread->setFile(g_szIfName_1,li_filenum, li_filesize*1024*1024, ls_path);
    captureThread->setAdapterID(1);     //yangmeng 161030 设置当前网卡序号为1，以便区分最新记录序号
    captureThread->setLogFileFlag(g_szLogFileFlag_1);
    captureThread->start();

    // gaohao Add 支持双镜像口
    if(strcmp(g_szIfName_1,g_szIfName_2) == 0)
    {
        return ;//如果两个网口相同，只起一个线程--qhy 2016.10.26    ls_path
    }
    if (g_szIfName_2[0] != ';')
    {
        ///home/test 文件保存路径改为固定值，不再允许用户设置   //yangmeng 161101 文件路径为1T硬盘
        captureThread1->setFile(g_szIfName_2,li_filenum, li_filesize*1024*1024,ls_path);
        captureThread1->setAdapterID(2);     //yangmeng 161030 设置当前网卡序号为2，以便区分最新记录序号
        captureThread1->setLogFileFlag(g_szLogFileFlag_2);
        captureThread1->start();
    }
}

void MyThreadWidget::slot_stop()
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

}

MyThreadWidget::~MyThreadWidget()
{
    if(myudp)
    {
    delete myudp;
    myudp=NULL;
    }
    if(captureThread)
    {
    delete captureThread;
    captureThread=NULL;
    }
    if(captureThread1)
    {
     delete captureThread1;    // gaohao Add 捕获多个镜像口数据
     captureThread1=NULL;
    }
    delete ui;
}
