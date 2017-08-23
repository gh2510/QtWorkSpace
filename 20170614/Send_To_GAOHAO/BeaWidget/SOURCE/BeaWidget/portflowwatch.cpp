#include "portflowwatch.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QSqlQuery>
#include "connection.h"

QWidget* tabWidgets[20];  // gaohao Add 维护当前创建的tab对象

PortFlowWatch::PortFlowWatch(QWidget *parent) :
    QWidget(parent)
{
    int wi=parent->width();
    int hi=parent->height();
    setFixedSize(wi,hi);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(17,63,61));  //background color
    palette.setColor(QPalette::WindowText,QColor("white"));
    setPalette(palette);
    tabWidget=NULL;
    initWidget();
}
PortFlowWatch::~PortFlowWatch()
{
    if(tabWidget) delete tabWidget;
}
void PortFlowWatch::initWidget()
{
    int wi=QApplication::desktop()->width();
    int hi=QApplication::desktop()->height();

    if(tabWidget !=NULL)
        delete tabWidget;
    tabWidget=new QTabWidget(this);
    tabWidget->setFixedHeight (hi*5/6);
    tabWidget->setFocusPolicy(Qt::NoFocus);
    tabWidget->setDocumentMode(true);
    tabWidget->setStyleSheet(
                "QTabBar::tab{ background: #77ac98; color: white; padding: 10px;border: 2px solid; } "
                "QTabBar::tab:selected { background: #007d65; white:red;font-size:12px;font-weight:bold;}"
                "QTabBar::tab:!selected {margin-top: 5px;}"
                );

    for(int k=0;k<SWITCHNUM;k=k+6)
    {
        QVBoxLayout *mainlayout=new QVBoxLayout();//每6个端口设置一个布局
        QWidget  * portWidget=new QWidget();
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
        portWidget->setLayout(mainlayout);
        tabWidget->addTab(portWidget, "  " +QString::number(k+1)+"~"+QString::number(k+6)+ "  " );

        tabWidgets[k/6] = portWidget; // gaohao Add 记录当前创建的对象
    }


}

void PortFlowWatch::slot_setswitchnum(QString name)
{
    current_switch_name=name;
     /* gaohao Hide
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
    tabWidget->clear();
    for(int i = 0; i < portCnt; ++i)
    {
        if(i%6==0){
            tabWidget->setTabEnabled(i/6, true);
            //tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(i+6)+"  " );
            if(6*(portCnt/6)<portCnt)       //yangmeng 161025
            {
                if(i+6>portCnt)
                tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(portCnt)+"  " );//portCnt 改为i+6  sunmnegyun2016.10.25
                else
                      tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(i+6)+"  " );
            }
            else
            {
                if(i+6>portCnt)
                tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(portCnt)+"  " );//portCnt 改为i+6  sunmnegyun2016.10.25
                else
                      tabWidget->addTab(tabWidgets[i/6], "  " + QString::number(i+1)+"~"+QString::number(i+6)+"  " );

            }
            tabWidget->setVisible(true); // gaohao Add
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
    tabWidget->setCurrentIndex(0);
}

void PortFlowWatch::slot_updateData(QString name,int portnum,double cpuusage,double memusage)//in，out
{

          port[portnum].updateData(name,cpuusage,memusage);

}
void PortFlowWatch::refresh_port()
{
    for(int i=0;i<SWITCHNUM;i++)
    {
        port[i].init_plot();
    }
}
