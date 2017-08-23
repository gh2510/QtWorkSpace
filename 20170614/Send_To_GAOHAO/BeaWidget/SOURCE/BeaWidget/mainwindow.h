#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QPoint>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QObject>
#include "content_widget.h"
#include "newtiltltwidget.h"
#include "mainframe.h"
#include "defcommon.h"
#include "mainview.h"
#include "switchmanage.h"
#include "usermanage.h"
#include "monitorwidget.h"
#include "alarmmanage.h"
#include "grammanage.h"
#include <QApplication>
#include <QDesktopWidget>
#include "helpwidget.h"

#include"buzzerthread.h"
#include "newperformancesearch.h"
#include <QSplashScreen>

namespace Ui {
class MainWindow;
}

#include"logindialog.h" //yangmeng 161026 日志实时更新

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,QSplashScreen *splash=0);
    static void setLogfileName();
    void logInit();
    ~MainWindow();
protected:
    bool eventFilter( QObject *obj, QEvent *e);
signals:
    void signal_indexchange(int index);
    void sig_warningToTop(QString switchName,QString value);   //qhy 2016.11.12
    void buzzerGo();
    void signal_addRecord(QString); //yangmeng 161026 日志实时更新
public slots:
    void closeMainWindow();
    void minimizeWindow();
    void indexchanged(int index);
    void warningdeal(QString switchName,QString alarmType,QString portSpeed);    // -- qhy 2016.11.12
    void warningDisconnnected(QString switches);
    void alarmIfWorkChanged(bool);

private:
    virtual void paintEvent(QPaintEvent *event);
    QPoint mouse_point;  //distance of mouse's tracing
    bool mouse_press;    // judge the mouse whether press down

    newTiltltWidget *titlewidget;
    class MainView *mainview;
    MonitorWidget *monitorwidget;
    class GramManage *gramManage;
    NewPerformanceSearch *performance;
    class UserManage *usermanage;
    HelpWidget *helpw;
    buzzerThread *buzzer;

    void changeUser(bool);  //改变用户角色 yangmeng161022
    Ui::MainWindow *ui;
    void createMainView(QSplashScreen *splash=0);
    void createMonitor();
    void creatGramManage();
    void createNewPerformanceSearch();
    void createUserManage();


public:
     class LoginDialog dlg;   //yangmeng 161026 日志实时更新
     static int logCurNum;    //当前日志的序号
     static QString logDate;  //当前日志的日期
     static int logFileNumb;  //最大可记录的日志文件数量
     static QString logPath;   //日志路径，不含文件名
     static QString logFileName;    //日志文件名，定义为静态变量，每次开机取得 qhy 2016.11.24
};

#endif // MAINWINDOW_H
