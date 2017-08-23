#include "switchconfpwd.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include "logindialog.h"
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QSignalMapper>
#include <QMessageBox>
#include <QPalette>
#include <QPainter>
#include <QPen>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QProcess>
#include <fstream>

switchConfPwd::switchConfPwd(telnetManager *telm,QWidget *parent) :
    QWidget(parent)
{
    this->telm=telm;

    stack_layout=new QStackedLayout();

    main_layout = new QVBoxLayout();
    pwdConfLayout = new QHBoxLayout();
    pwdConfLayout1 = new QHBoxLayout();
    pwdChangeLayout = new QVBoxLayout();
    pwdChangeForm = new QHBoxLayout();
    pwdChangeFormLeft = new QVBoxLayout();
    pwdChangeFormRight = new QVBoxLayout();
    pwdChangeFormLeft1 = new QHBoxLayout();
    pwdChangeFormLeft2 = new QHBoxLayout();
    pwdChangeFormLeft3 = new QHBoxLayout();

    pwdConfLayout1->addLayout(pwdChangeLayout);
    pwdChangeLayout->addLayout(pwdChangeForm);
    pwdChangeForm->addLayout(pwdChangeFormLeft);
    pwdChangeForm->addSpacing(40);
    pwdChangeForm->addLayout(pwdChangeFormRight);
    pwdChangeForm->addStretch(0);
    pwdChangeFormLeft->addLayout(pwdChangeFormLeft1);
    //pwdChangeFormLeft->addLayout(pwdChangeFormLeft2);
    //pwdChangeFormLeft->addLayout(pwdChangeFormLeft3);

    main_layout->addStretch(1);
    main_layout->addLayout(pwdConfLayout);
    main_layout->addStretch(1);
    main_layout->addLayout(pwdConfLayout1);
    main_layout->addStretch(5);

    tel_ip = new LabelEdit();
    tel_ip->setLabel(tr("Telnet IP:"));
    tel_ip->setEditReadOnly(false);
    tel_ip->setLabelWidth(80);
    pwdChangeFormLeft1->addWidget(tel_ip,0,Qt::AlignLeft);

    tel_pass = new LabelEdit();
    tel_pass->setLabel(tr("Telnet密码:"));
    tel_pass->setEditReadOnly(false);
    tel_pass->setLabelWidth(80);
    pwdChangeFormLeft2->addWidget(tel_pass,0,Qt::AlignLeft);

    pass = new LabelEdit();
    pass->setLabel(tr("特权密码:"));
    pass->setEditReadOnly(false);
    pass->setLabelWidth(80);
    pwdChangeFormLeft3->addWidget(pass,0,Qt::AlignLeft);

    pwdChangeFormRightBtn = new QPushButton();
    QString style = "QPushButton{";
    style+="border-image: url(:/images/images/button_search.png);";
    style+="border-radius:5px;";
    style+="color: rgb(255, 255, 255);}";
    pwdChangeFormRightBtn->setStyleSheet(style);
    pwdChangeFormRightBtn->setText(tr("登录"));
    pwdChangeFormRightBtn->setFixedWidth(100);
    pwdChangeFormRight->addWidget(pwdChangeFormRightBtn,0,Qt::AlignVCenter);

    main_layout_logined=new QHBoxLayout();
    teled_ip=new QLabel();
    QFont font_t("Times",16);
    teled_ip->setFont(font_t);
    QPalette   pal;
    pal.setColor(QPalette::WindowText, QColor(255,255,255));
    teled_ip->setPalette(pal);
    login_out=new commonButton();
    login_out->setText(tr("退出"));
    login_out->setWidth(100);

    main_layout_logined->addStretch(6);
    main_layout_logined->addWidget(teled_ip,0,Qt::AlignVCenter);
    main_layout_logined->addStretch(2);
    main_layout_logined->addWidget(login_out,0,Qt::AlignVCenter);
    main_layout_logined->addStretch(6);

    connect(pwdChangeFormRightBtn,SIGNAL(clicked()),this,SLOT(login()));
    connect(login_out,SIGNAL(click()),this,SLOT(logout()));

    main_w1=new QWidget();
    main_w1->setLayout(main_layout);

    main_w2=new QWidget();
    main_w2->setLayout(main_layout_logined);

    stack_layout->addWidget(main_w1);
    stack_layout->addWidget(main_w2);
    this->setLayout(stack_layout);
    stack_layout->setCurrentIndex(0);
}

void switchConfPwd::login()
{
    if(userLevel)
    {
        QMessageBox::information(0,"用户权限不足","请使用管理员权限登录!");
        return;
    }
    QString lo_tel_ip = tel_ip->text().trimmed();
    QProcess terminal(0);
    QString command = "/usr/bin/gnome-terminal";
    QStringList args;
    args.append("-x");
    args.append("telnet");
    args.append(lo_tel_ip);
    terminal.execute(command, args);
    terminal.waitForFinished();
//    if(telm!=NULL&&telm->get_tel_status()==0)
//    {
//      QString lo_tel_ip=tel_ip->text().trimmed();
//      QString lo_tel_pass=tel_pass->text().trimmed();
//      QString lo_pass=pass->text().trimmed();
//      int res=telm->connToServerandInit(lo_tel_ip,lo_tel_pass,lo_pass);
//      if(res==-1)
//      {
//          QMessageBox::information(this,"信息错误","登录失败!");
//          return;
//      }
//      teled_ip->setText(tel_ip->text().trimmed()+"在线...");
//      stack_layout->setCurrentIndex(1);

//      //写入日志文件
//      QFile file(MainWindow::logFileName);
//      if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
//      {
//          QMessageBox::information(this,tr("错误"),tr("日志文件打开失败！"),QMessageBox::Ok);
//      }
//      QTextStream out(&file);
//      out<<"["<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<tr("] [Telnet登录]")<<tr("IP")<<lo_tel_ip<<endl;
//      file.close();


//    }

}

void switchConfPwd::logout()
{
    if(telm!=NULL&&telm->get_tel_status()==1)
    {
        telm->close_telnet();

     stack_layout->setCurrentIndex(0);

     //写入日志文件，qhy 2016.11.29
     MainWindow::setLogfileName();
     QFile file(MainWindow::logFileName);

     if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
     {
         QMessageBox::information(0,tr("错误"),tr("日志文件打开失败！"),QMessageBox::Ok);
     }
     QTextStream out(&file);
     out<<"["<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<tr("] [Telnet退出]")<<endl;
     file.close();
    }
}

void switchConfPwd::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.drawLine(rect().topLeft(),rect().topRight());

}

switchConfPwd::~switchConfPwd()
{

}
