#include "switchconfquery.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QSignalMapper>
#include "labelcombox.h"

#include "commonbutton.h"
#include <QPalette>
#include <QScrollBar>

#include "Telnet/telnetmanager.h"
switchConfQuery::switchConfQuery(telnetManager *teml,QWidget *parent) :
    QWidget(parent)
{
    this->telm=teml;


    QVBoxLayout *main_layout = new QVBoxLayout();
    QHBoxLayout *sinfoSearchLayout1 = new QHBoxLayout();
    QHBoxLayout *sinfoSearchLayout2 = new QHBoxLayout();
    QHBoxLayout *sinfoResLayout = new QHBoxLayout();

    main_layout->addStretch(1);
    main_layout->addLayout(sinfoSearchLayout1,0);
    main_layout->addStretch(1);
    main_layout->addLayout(sinfoSearchLayout2,0);
    main_layout->addStretch(5);
    main_layout->addLayout(sinfoResLayout,0);
    main_layout->addStretch(5);



    queryCon = new LabelEdit();
    queryCon->setLabel(tr("输入:"));
    queryCon->setEditReadOnly(false);
    commonButton *clearQuery = new commonButton();
    clearQuery->setText(tr("清空查询结果"));
    clearQuery->setWidth(100);
    commonButton *queryPushBtn = new commonButton();
    queryPushBtn->setText(tr("查询"));
    queryPushBtn->setWidth(100);
    sinfoSearchLayout2->addWidget(queryCon,0,Qt::AlignHCenter);
    sinfoSearchLayout2->addSpacing(40);
    sinfoSearchLayout2->addWidget(queryPushBtn,0,Qt::AlignHCenter);

    sinfoSearchLayout2->addStretch(0);
    sinfoSearchLayout2->addWidget(clearQuery,0,Qt::AlignRight);


    textEdit = new QTextEdit();
    textEdit->setStyleSheet("background-color:rgb(200,200,200)");
    //textedit设置滚动条
    textEdit->setFixedWidth(700);
    textEdit->setMinimumHeight(400);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximumHeight());
    textEdit->setLineWrapMode(QTextEdit::NoWrap);
    sinfoResLayout->addWidget(textEdit,0,Qt::AlignHCenter);
   // connect(queryPushBtn,SIGNAL(click()),this,SLOT(queryBtn()));
    bool flag = true;
    this->setLayout(main_layout);

    if(teml)
    {
        connect(telm,SIGNAL(readServer(QString)),this,SLOT(readServer(QString)));
        connect(telm,SIGNAL(signal_discon()),this,SLOT(slot_socket_err()));
        connect(telm,SIGNAL(signal_error()),this,SLOT(slot_socket_err()));

    }
      connect(queryPushBtn,SIGNAL(click()),this,SLOT(queryBtn()));
      connect(clearQuery,SIGNAL(click()),this,SLOT(clearTextEdit()));
}

void switchConfQuery::slot_socket_err()//error处理
{

}
 void switchConfQuery::readServer(QString txt_recv)
 {
     this->textEdit->append(txt_recv);
 }
 void switchConfQuery::queryBtn()
  {
     if(telm)
     {
         this->telm->set_read_mode(1);
         QString queryCond = queryCon->text();
         this->telm->query(queryCond);
     }
  }

void switchConfQuery::clearTextEdit(){
    textEdit->setText("");
}



switchConfQuery::~switchConfQuery()
{

}
