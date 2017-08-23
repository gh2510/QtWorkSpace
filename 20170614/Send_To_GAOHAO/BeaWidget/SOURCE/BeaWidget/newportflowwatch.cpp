#include "newportflowwatch.h"
#include "ui_newportflowwatch.h"
#include "connection.h"

#include <QTabWidget>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>

//QWidget* tabWidgets[20];  // gaohao Add 维护当前创建的tab对象

NewPortFlowWatch::NewPortFlowWatch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewPortFlowWatch)
{
    ui->setupUi(this);
    setFixedSize(parent->width(),parent->height()*9/10);
    ui->widget->setFixedSize(this->width(),this->height());
    ui->tabWidget->setFixedSize(this->width(),this->height()*9.8/10);

    pages<<ui->page0<<ui->page1<<ui->page2<<ui->page3
        <<ui->page4<<ui->page5<<ui->page6<<ui->page7<<ui->page8<<ui->page9;
    for (int i =0;i<10;i++)
    {
       pageName<<ui->tabWidget->tabText(i);
    }
    initWidget();

}

void NewPortFlowWatch::initWidget()
{
    int pageIndex = 0;      //lys Tab页索引值
    for(int k=0;k<SWITCHNUM;k=k+6)
    {
        QVBoxLayout *mainlayout=new QVBoxLayout();//每6个端口设置一个布局
//        QWidget  * portWidget=new QWidget();
        for(int i=k;i<k+6&&i<SWITCHNUM;i++)
        {
            QHBoxLayout *hlayout=new QHBoxLayout();
           hlayout->addWidget(&port[i],0,Qt::AlignLeft|Qt::AlignVCenter);
           port[i].setcurrentportnumber(i);
           i++;
           hlayout->addWidget(&port[i],0,Qt::AlignLeft|Qt::AlignVCenter);
           port[i].setcurrentportnumber(i);
           i++;
           hlayout->addWidget(&port[i],0,Qt::AlignVCenter);
           port[i].setcurrentportnumber(i);
           mainlayout->addLayout(hlayout);

        }
        pages.at(pageIndex)->setLayout(mainlayout);
        pageIndex++;

//        tabWidgets[k/6] = portWidget; // gaohao Add 记录当前创建的对象
    }
}

void NewPortFlowWatch::refresh_port()
{
    for(int i=0;i<SWITCHNUM;i++)
    {
        port[i].init_plot();
    }
}

void NewPortFlowWatch::slot_setswitchnum(QString name)
{
    current_switch_name=name;
     /* gaohao Hideport
    for(int i=0;i<SWITCHNUM;i++)
    {
        if(i%6==0)
        {
            tabWidget->setTabEnabled(i/6, true);
            tabWidget->setTabText(i/6,QString::number(i+1)+"~"+QString::number(i+6));
        }
        port[i].setCurrentSwitchNumber(current_switch_name);
        port[i].setVisible(true);
    }
    */
    QSqlQuery query("",DBConnection::db);;
    query.prepare ("select remark from switch where name = ?");
    query.bindValue(0, name);
    query.exec();
    query.next();
    int portCnt = query.value(0).toInt();
    query.finish();
    // gaohao Add 为避免不存在端口的显示 首先隐藏所有内容
    ui->tabWidget->clear();
    for(int i = 0; i < portCnt; ++i)
    {
        if(i%6==0)
        {
            ui->tabWidget->setTabEnabled(i/6, true);
            if(6*(portCnt/6)<portCnt)       //yangmeng 161025
            {
                if(i+6>portCnt)
                {
//                    ui->tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(portCnt)+"  " );//portCnt 改为i+6  sunmnegyun2016.10.25
                    ui->tabWidget->addTab(pages.at(i/6),pageName.at(i/6));
                }
                else
                {
//                    ui->tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(i+6)+"  " );
                    ui->tabWidget->addTab(pages.at(i/6),pageName.at(i/6));
                }
            }
            else
            {
                if(i+6>portCnt)
                {
//                    tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(portCnt)+"  " );//portCnt 改为i+6  sunmnegyun2016.10.25
                    ui->tabWidget->addTab(pages.at(i/6),pageName.at(i/6));
                }

                else
                {
//                    tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(i+6)+"  " );
                    ui->tabWidget->addTab(pages.at(i/6),pageName.at(i/6));
                }

            }
            ui->tabWidget->setVisible(true); // gaohao Add
        }
        port[i].setCurrentSwitchNumber(current_switch_name);
        port[i].setVisible(true);
    }
    //yangmeng 161025
    if(portCnt%6 != 0)
    {
        for(int i=0; i<(6*(portCnt/6+1)-portCnt);i++)
        {
            port[portCnt+i].setVisible(false);
            qDebug()<<"port ID = "<<i;
        }
    }
    ui->tabWidget->setCurrentIndex(0);
}

void NewPortFlowWatch::slot_updateData(QString name, int portnum, double cpuusage, double memusage)
{
    port[portnum].updateData(name,cpuusage,memusage);
}

NewPortFlowWatch::~NewPortFlowWatch()
{
    delete ui;
    if(pages.count()>0)
    {
        pages.clear();
    }
    if(pageName.count()>0)
    {
        pageName.clear();
    }
}
