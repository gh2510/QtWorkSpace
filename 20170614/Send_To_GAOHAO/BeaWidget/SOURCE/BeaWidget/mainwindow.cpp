#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QTime>

#include "insertthread.h"
#include "logindialog.h"
#include "usermanage.h"
#include "grammanage.h"

#include "newshowlogdialog.h"
#include "newalarmthreshset.h"
#include "newerrormanage.h"

//Add by Mr.Shang in 2017.02.17,I want debug the new Ui file.
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, QSplashScreen *splash) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignBottom;
    splash->showMessage(QObject::tr("加载主界面..."),topRight, Qt::white);//显示信息

    ui->setupUi(this);
    int w = qApp->desktop()->screen()->width();
    int h = qApp->desktop()->screen()->height();
    this->setGeometry(0,0,w,h);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(QApplication::desktop()->width(),QApplication::desktop()->height());

    ui->widget_title->setFixedSize(this->width(),120);
    ui->widget_show->setFixedSize(this->width(),this->height()-120);
    setWindowIcon(QIcon(":/img/img/title_logo"));

    //指针初始化为NULL，避免析构时出错  yangmeng 161021
    logInit();
    titlewidget = NULL;
    mainview = NULL;
    monitorwidget = NULL;
    gramManage = NULL;
    performance = NULL;
    usermanage = NULL;
    helpw = NULL;

    splash->showMessage(QObject::tr("初始化按钮列表......"),topRight, Qt::white);
    if(titlewidget==NULL){
        titlewidget = new newTiltltWidget(ui->widget_title);    //Shang
    }

    createMainView(splash);
    createMonitor();

    splash->showMessage(QObject::tr("初始化信息链接......"),topRight, Qt::white);
    connect(titlewidget,SIGNAL(turnpage(int)),this,SLOT(indexchanged(int))); //主界面切换
    connect(titlewidget,SIGNAL(minizeWindow()),this,SLOT(minimizeWindow()));
    connect(titlewidget,SIGNAL(closeMainWindow()),this,SLOT(closeMainWindow()));
    connect(titlewidget,SIGNAL(ifAlarmChanged(bool)),this,SLOT(alarmIfWorkChanged(bool)));

    SwitchThread::InitSwitchComInfo();  //初始化共用参数
    titlewidget->turnFirstPage(0);      //Shang
    this->installEventFilter(this);

    splash->showMessage(QObject::tr("加载蜂鸣器报警模块......"),topRight, Qt::white);
    buzzer=new buzzerThread(this);
    connect(this,SIGNAL(buzzerGo()),buzzer,SLOT(slot_buzzerCount()));
    buzzer->start();
    splash->showMessage(QObject::tr("加载完成......"),topRight, Qt::white);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
//    MainFrame::paintEvent(event);
//    QPainter painter(this);mycommunity
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(Qt::white);

}

bool MainWindow::eventFilter( QObject *obj, QEvent *e)
{
    QKeyEvent *qk=static_cast<QKeyEvent *> (e);
    if(e->type()==QEvent::KeyPress)
    {
        if(qk->key()==Qt::Key_Z && (qk->modifiers()==(Qt::ControlModifier | Qt::ShiftModifier)))
        {
            closeMainWindow();
        }
    }
    return QWidget::eventFilter( obj, e);
}
MainWindow::~MainWindow()
{
    if(titlewidget)delete titlewidget;
    if(mainview)delete mainview;
    if(monitorwidget)delete monitorwidget;
    if(gramManage)delete gramManage;
    if(usermanage)delete usermanage;
    if(helpw)delete helpw;
    if(performance)
    {
        delete performance;
        performance = NULL;
    }

}

void MainWindow::indexchanged (int index)
{
    QWidget *widget=NULL;
    switch(index)
    {
    case 0:
        widget = mainview;
        break;
    case 1:
        createMonitor();
        widget = monitorwidget;
        break;
    case 2:
        creatGramManage();
        widget = gramManage;
        break;
    case 3:
        createNewPerformanceSearch();
        widget = performance;
        break;
    case 4:
        if(userLevel==0)// 如果是管理员    开机时自动将所有页面都创建好，以便账户切换 yangmeng 161022
        {
            createUserManage();
            widget = usermanage;
        }
        break;
    }
    ui->stack_widget->setCurrentWidget(widget);
}

//创建设备监控界面
void MainWindow::createMainView(QSplashScreen *splash)
{
    if(!mainview)
    {
        mainview = new MainView(ui->widget_show,splash);
        connect(mainview->st->topview,SIGNAL(signal_update()),mainview->switchmanage,SLOT(slot_init()));
        connect(mainview->switchmanage,SIGNAL(signal_update()),mainview->st->topview,SLOT(slot_init()));//插入删除交换机拓扑图重绘
        connect(mainview->st->topview,SIGNAL(signal_disconnected(QString)),this,SLOT( warningDisconnnected(QString)));//交换机连线断开告警

        Qt::Alignment topRight = Qt::AlignLeft | Qt::AlignBottom;
        splash->showMessage(QObject::tr("加载设备监控界面......"),topRight, Qt::white);
        ui->stack_widget->addWidget(mainview);
    }
}


//创建实时管理界面
void MainWindow::createMonitor()
{
    if(!monitorwidget)
    {
        monitorwidget=new MonitorWidget(ui->widget_show);   //实时管理
        connect(mainview->st->topview,SIGNAL(signal_update()),monitorwidget,SLOT(slot_init_widget()));
        connect(mainview->switchmanage,SIGNAL(signal_update()),monitorwidget,SLOT(slot_init_widget())); //插入删除交换机流量监控图重绘
        connect(monitorwidget,SIGNAL(sig_warningToTop(QString,QString,QString)),
                this,SLOT(warningdeal(QString,QString,QString)));//告警处理，包括蜂鸣器响和插入数据库--qhy
        connect(monitorwidget,SIGNAL(sig_warningToTop(QString,QString,QString)),
                mainview->st->topview,SLOT(slot_setAlarmSwitch(QString,QString,QString)));//告警处理，在拓扑图上更新交换机的状态
        connect(monitorwidget,SIGNAL(sig_setNormal(QString)),mainview->st->topview,SLOT(slot_setNormalSwitch(QString)));//交换机自动恢复
        connect(monitorwidget,SIGNAL(sig_portStatus(QString,int ,int)),
                mainview->st->alarmtableview,SLOT(slot_portStatus(QString,int ,int)));//单个交换机信息表的状态灯更新
        connect(monitorwidget,SIGNAL(sig_portStatus(QString,int ,int)),
                mainview->st,SLOT(slot_portStatus(QString,int ,int)));//常显的核心交换机的状态灯更新
        connect(monitorwidget,SIGNAL(sig_portStatus(QString,int ,int)),
                mainview->st->topview,SLOT(slot_portStatus(QString,int ,int)));//拓扑图连线更新
        connect(monitorwidget,SIGNAL(sig_version(QString,QString)),
                mainview->st->alarmtableview,SLOT(slot_version(QString,QString)));//版本信息查询更新
        ui->stack_widget->addWidget(monitorwidget);
        creatGramManage();
    }
}

//创建统计管理界面
void MainWindow::creatGramManage()
{
    if(!gramManage)
    {
        gramManage=new GramManage(ui->widget_show);         //统计管理
        connect(gramManage,SIGNAL(signal_cancelWarning(QString)),
                mainview->st->topview,SLOT(slot_setNormalSwitch(QString)));//告警处理完毕恢复正常
        //yangmeng 161026 日志实时更新
        connect(&dlg,SIGNAL(signal_addRecord(QString)),gramManage->logDialog,SLOT( addRecord(QString)));//用户登录信息日志实时更新
        connect(this,SIGNAL(signal_addRecord(QString)),gramManage->logDialog,SLOT( addRecord(QString)));//告警信息日志实时更新
        connect(mainview->st,SIGNAL(signal_addRecord(QString)),gramManage->logDialog,SLOT( addRecord(QString)));//核心交换机端口状态日志实时更新
        createMonitor();
        for (int i=0;i<monitorwidget->swi_thread_list.size();i++)//
        {
            connect(monitorwidget->swi_thread_list.at(i),SIGNAL(sig_alarm(QString)),mainview->st->alarmtableview,SLOT(slot_sig_alarm(QString)));
            // gaohao Add 建立阈值编辑与线程队列直接的关联
            connect(gramManage->alarmthreshset,SIGNAL(alarmSet(QString,int,int,double)),monitorwidget->swi_thread_list.at(i),SLOT(alarmSet(QString,int,int,double)));
            connect(gramManage->alarmthreshset,SIGNAL(alarmDel(QString,int,int)),monitorwidget->swi_thread_list.at(i),SLOT(alarmDel(QString,int,int)));
            connect(gramManage->alarmthreshset,SIGNAL(alarmAdd(QString,int,int,double)),monitorwidget->swi_thread_list.at(i),SLOT(alarmAdd(QString,int,int,double)));     //yangmeng 161101
        }
        ui->stack_widget->addWidget(gramManage);
    }
}

//创建离线查询界面
void MainWindow::createNewPerformanceSearch()
{
    if(!performance)
    {
        performance = new NewPerformanceSearch(ui->widget_show);    //离线查询
        ui->stack_widget->addWidget (performance);
    }
}

//创建用户管理界面
void MainWindow::createUserManage()
{
    if(userLevel==0)// 如果是管理员    开机时自动将所有页面都创建好，以便账户切换 yangmeng 161022
    {
        if(!usermanage)
        {
            usermanage=new UserManage(ui->widget_show);//用户管理
            connect(usermanage,SIGNAL(signal_addRecord(QString)),gramManage->logDialog,SLOT( addRecord(QString)));//用户管理操作信息日志实时更新
            ui->stack_widget->addWidget(usermanage);
        }
    }
}

void MainWindow::warningdeal(QString switchName, QString alarmType, QString portSpeed)   //增加一个参数，记录端口速率  , QString portSpeed---qhy
{

    QString newRecord;      //yangmeng 161026 日志实时更新"log.txt"

    //调用静态函数获得当前日志文件名
    MainWindow::setLogfileName();
    QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29
    if(alarmType=="交换机不可达")   //return;//交换机不可达暂不插入数据库，写入日志文件--2016.11.25
   {        
        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QMessageBox::information(this,tr("错误4"),tr("日志文件打开失败！"),QMessageBox::Ok);
        }
        QTextStream out(&file);
        newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [告警]")+switchName+"不可达";
        out<<newRecord<<endl;
        file.close();
        emit signal_addRecord(newRecord);
        return;
    }
    QSqlQuery query("",DBConnection::db);;
    query.prepare("select  count(*)  from alarmcurrent where name =?  and alarmtype=? and  isdeal='否'");
    query.bindValue(0,switchName);
    query.bindValue(1,alarmType);
    query.exec();
    query.next();

    int num=query.value(0).toInt();
    if(num>0)
    {
        query.prepare("delete   from alarmcurrent where name =?  and  alarmtype=?");
        query.bindValue(0,switchName);
        query.bindValue(1,alarmType);
        query.exec();
    }
        query.prepare("insert into alarmcurrent (alarmtype,starttime,isdeal,name,value)  values(?,?,?,?,?)");   //add value-qhy   2016.11.12
        query.bindValue(0,alarmType);
        query.bindValue(1,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.bindValue(2,"否");
        query.bindValue(3,switchName);        
        query.bindValue(4,portSpeed);  //记录当前告警的参数值  qhy   2016.11.12
       // query.bindValue(4,portSpeed);    //add value-qhy
        query.exec();

        query.prepare("insert into alarm (alarmtype,starttime,isdeal,name,value)  values(?,?,?,?,?)");   //add value-qhy    2016.11.12
        query.bindValue(0,alarmType);
        query.bindValue(1,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.bindValue(2,"否");
        query.bindValue(3,switchName);
        query.bindValue(4,portSpeed);  //记录当前告警的参数值  qhy   2016.11.12
        query.exec();
       // query.bindValue(4,portSpeed);    //add value-qhy

        if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
        {
            QMessageBox::information(this,tr("错误5"),tr("日志文件打开失败！"),QMessageBox::Ok);
        }
        QTextStream out(&file);
        newRecord = "["+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+tr("] [告警]")+switchName+alarmType;
        out<<newRecord<<endl;
        file.close();

        emit signal_addRecord(newRecord);

    query.finish();
    query.clear();
    //emit sig_warningToTop(switchName);//加上交换机不可达后无效

    //蜂鸣器报警改放在线程中
   emit buzzerGo();
}

void MainWindow::warningDisconnnected(QString switches)//交换机连接断开告警
{
    //蜂鸣器报警改放在线程中
    emit buzzerGo();
}

//时间戳双击修改蜂鸣器工作与否
void MainWindow::alarmIfWorkChanged(bool ifWork)
{
    qDebug()<<"mainwindow value:"<<ifWork;
    buzzer->setIfAlarm(ifWork);
}

//关机按钮响应处理原来为选择确定/取消，现在改为选择“关机”或“切换账户” yangmeng161022
void MainWindow::closeMainWindow()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle(tr("提示"));
    msgBox.setText(tr("请选择操作"));
     QPushButton *changeUserButton = msgBox.addButton(tr("切换用户"), QMessageBox::ActionRole);
     QPushButton *shutdownButton = msgBox.addButton(tr("关机"), QMessageBox::ActionRole);
     QPushButton *abortButton = msgBox.addButton(tr("取消"), QMessageBox::ActionRole);
     msgBox.exec();

     int selectBut = 0;

     if (msgBox.clickedButton() == changeUserButton)    //切换用户
     {
         selectBut = 0;
     }
     else if (msgBox.clickedButton() == shutdownButton) //关机
     {
         selectBut = 1;
     }
     else                                               //取消
     {
         selectBut = 2;
     }

     switch(selectBut)
      {
     case 0:        //切换用户
         {
               this->hide();
               dlg.move((QApplication::desktop()->width()-dlg.width())/2,(QApplication::desktop()->height()-dlg.height())/2);
               if(dlg.exec()==QDialog::Accepted)       //切换账户 yangmeng161022
               {
                   changeUser(userLevel);
                   this->showFullScreen();
                   titlewidget->initWidgetShow();
               }
          }
          break;
     case 1:        //关机
         {
             this->close();
             db_sqlite.commit();
             //写入日志文件
             //QFile file("log.txt");

             //调用静态函数获得当前日志文件名
             MainWindow::setLogfileName();
             QFile file(MainWindow::logFileName);   //修改结束，qhy 2016.11.29
            //修改，qhy 2016.11.12

             if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
             {
                 QMessageBox::information(this,tr("错误6"),tr("日志文件打开失败！"),QMessageBox::Ok);
             }
             QTextStream out(&file);
             out<<"["<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<tr("] [当前用户退出]")<<endl;
             file.close();

             this->close();
             //system("shutdown -P 0");
              break;
         }
      default:      //取消
          break;
      }

}

void MainWindow::minimizeWindow()
{
    this->showMinimized();
}

//改变用户角色 yangmeng 161022
void MainWindow::changeUser(bool userType)
{
    if(userType==0)// 如果是管理员
    {
        //用户管理功能添加
        if(!usermanage)
        {
           createUserManage();
        }
        else
        {
            ui->stack_widget->addWidget (usermanage);
        }
        mainview->switchmanage->setManageBtnVisible(true);  //Shang
        gramManage->errorManage->setManageBtnVisible(true);
    }
    else
    {
        //用户管理功能屏蔽
        if(usermanage)
        {
            ui->stack_widget->removeWidget(usermanage);
            usermanage->hide();
        }
        mainview->switchmanage->setManageBtnVisible(false); //Shang
        gramManage->errorManage->setManageBtnVisible(false);
    }
    titlewidget->changeUser();  //顶部按钮栏模式切换
    mainview->changeUser(); //主界面模式切换
    titlewidget->turnFirstPage(0);  //Shang

}

//设置日志文件名
void MainWindow::setLogfileName()
{
    QString startTime = QDate::currentDate().toString("yyyy-MM-dd");
    if (startTime!=MainWindow::logDate) {   //现在的日期与静态变量中保存的日志日期不同，意味着需要一个新的日志文件名

        MainWindow::logDate = startTime;  //保存本日的日期信息
        int i ;
        QFile file;
        for(i=0;i<MainWindow::logFileNumb; i++) {
            MainWindow::logFileName=MainWindow::logPath+QString::number(i)+"_"+ startTime +  "_log.txt";
            file.setFileName(MainWindow::logFileName);
            if (file.exists()) { break; }
        }
        if (i==MainWindow::logFileNumb ) {  //没有找到当前的日志文件
            MainWindow::logCurNum = (MainWindow::logCurNum+1) % MainWindow::logFileNumb ;
            MainWindow::logFileName=MainWindow::logPath+QString::number(MainWindow::logCurNum)+"_"+ startTime +  "_log.txt";
            QByteArray temp1=("rm  -f  " + MainWindow::logPath+ QString::number(MainWindow::logCurNum)+ "_*.*").toLatin1();  //此序号文件如果存在，删除旧的，再写新的
            qDebug()<<"FileName =  "<<MainWindow::logFileName;
            char  *ch1=temp1.data();
            system(ch1);
            //回填当前日志序号
            QSqlQuery  query("",DBConnection::db);
            query.prepare("update sysdict  set value = ?  where attr='当前日志序号' ");
            query.bindValue(0, QString::number(MainWindow::logCurNum));
            query.exec();
            query.finish();
        }
    }
 }

//qhy 2016.11.30
/*  修改:
 1. 每天产生一个日志文件，文件名格式为：序号_日期_log.txt;
 2. 日志文件的存放目录从logconfig.txt读取；
 3. 日志文件的最大个数由logconfig.txt读取，超过则自动删除，序号覆盖；
  */
//从配置文件中读取日志目录,文件大小和最多存储的文件个数
void MainWindow::logInit()
{
    int currentNum;

    ifstream file1("logconfig.txt");

    char ls_logdir[100], ls_filenum[20];
    long  li_filenum;

    file1>>ls_logdir;    //log目录
    file1>>ls_filenum;  //最多存储的文件个数

    file1.close();
    QString ls_path = QString(QLatin1String(ls_logdir));
    logPath = ls_path;   //记录日志目录名称，静态变量
    qDebug()<< " Log Path : " << ls_path;
    li_filenum =QString(QLatin1String(ls_filenum)).toLong();
    logFileNumb = li_filenum;   //记录日志文件最大个数，静态变量

    QDir dir( ls_path);   //日志目录为当前运行目录下，配置文件指定的子目录
    if (!dir.exists())
    {
        dir.mkpath(ls_path);
    }

     //从数据表读取前一天的日志序号
    QSqlQuery  query("",DBConnection::db);
    query.exec("select value from sysdict where attr='当前日志序号' ");
    if (!query.next()) {
        currentNum=0 ;
        }else {
       currentNum = query.value(0).toInt() ;
       }
    logCurNum = currentNum; //记录当前日志的序号

    //本日日志文件的名称，此时名称还不含序号信息
   QString startTime = QDate::currentDate().toString("yyyy-MM-dd");
   logDate = startTime;  //保存本日的日期信息
   int i ;
   QFile file;


   for(i=0;i<li_filenum; i++) {
       logFileName=ls_path+QString::number(i)+"_"+ startTime +  "_log.txt";
       file.setFileName(logFileName);
        if (file.exists()) { break; }
   }
   if (i==li_filenum ) {  //没有找到当前的日志文件
       currentNum = (currentNum+1) % li_filenum ;
       logFileName=ls_path+QString::number(currentNum)+"_"+ startTime +  "_log.txt";
       QByteArray temp1=("rm  -f  " + ls_path + QString::number(currentNum)+ "_*.*").toLatin1();  //此序号文件如果存在，删除旧的，再写新的
       qDebug()<<"FileName xx=  "<<logFileName;
       char  *ch1=temp1.data();
       system(ch1);
       }

   if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
   {
       QMessageBox::information(NULL,QObject::tr("错误1"),QObject::tr("日志文件打开失败！"),QMessageBox::Ok);
   }
   QTextStream out(&file);
   out<<"["<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<QObject::tr("] [登录]")<<QObject::tr("公用账户")<<endl;     //yangmeng 161026 日志字符乱码
   file.close();

   //回填当前日志序号
   query.prepare("update sysdict  set value = ?  where attr='当前日志序号' ");
   query.bindValue(0, QString::number(currentNum));
   query.exec();
   query.finish();
   query.clear();

}
