#include "helpwidget.h"
#include <QVBoxLayout>
#include <QString>
#include<QDialog>
#include<QDesktopWidget>
#include<QApplication>
HelpWidget::HelpWidget(QWidget *parent) :
    QWidget(parent)
{

   lbl_help=new QLabel();
    QVBoxLayout *main_layout=new QVBoxLayout();
    main_layout->addWidget(lbl_help,Qt::AlignLeft);    
    setLayout( main_layout);
    QString str="";
    str+="1.网络连接断开\n";
    str+="\n";
    str+="   解决方案:  \n";
    str+="             a.检查网线是否拔下或断开，网口灰尘过多\n";
    str+="             b.检查连接设备是否关闭或出现故障\n";
    str+="             c.检查是否网卡驱动出现问题\n";
    str+="\n";
    str+="2.交换机出现网络风暴故障\n";
    str+="\n";
    str+="   解决方案:  \n";
    str+="             网络风暴的原因可能是交换机受到大量的垃圾数据包\n";
    str+="           或者交换机处理器过忙，来不及转发。问题的解决方案\n";
    str+="           就是对进行合理的VLAN划分与广播域划分，以保证交换\n";
    str+="           机的网络安全。\n";
    str+="\n";
    str+="3.交换机端口指示灯不亮\n";
    str+="\n";
    str+="   解决方案: \n";
    str+="             a.查看端口是否没有打开\n";
    str+="             b.检查端口所连接的网线是否端口\n";
    str+="             c.端口灰尘过多，清理端口\n";\
    str+="             d.交换机未接上电源\n";
    str+="\n";
    str+="4.交换机CPU使用率过高\n";
    str+="\n";
    str+="   解决方案: \n";
    str+="             查看交换机任务中接收报文过多的协议类型，并且按照\n";
    str+="           不同类型的协议包，对交换机进行限速处理。\n";
    lbl_help->setText(str);

}


