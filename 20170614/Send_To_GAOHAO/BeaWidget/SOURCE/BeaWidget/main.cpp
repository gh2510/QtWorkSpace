#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QTextCodec>
#include <QPixmap>
#include <QSplashScreen>
#include "DDS/netdevice.h"

//定义静态变量，与日志文件名相关
int MainWindow::logCurNum=0;
QString MainWindow::logFileName="log.txt";
QString MainWindow::logPath ;                   //= "/home/";
int MainWindow::logFileNumb = 100;
QString MainWindow::logDate = "20170412";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    NetDevice device;
    if(device.InitDeviceNet()!=0)
    {
        QMessageBox::information(NULL,"提示","初始化DDS网络出错",QMessageBox::Ok);
    }

    if(!DBConnection::createConnection())
         return 0;

    // 加载开机动画
    QPixmap pixmap(":/images/images/main_login.png");
    pixmap.scaled(400,300);
    QSplashScreen splash(pixmap);
    splash.show();
    Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignBottom;
    splash.showMessage(QObject::tr("初始化界面..."),topRight, Qt::white);//显示信息
    app.processEvents();

    userLevel = 0;
    MainWindow window(0,&splash) ;
    window.showFullScreen();

    splash.finish(&window);

    return app.exec();
}

