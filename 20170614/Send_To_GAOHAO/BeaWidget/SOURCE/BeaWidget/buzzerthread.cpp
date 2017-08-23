#include "buzzerthread.h"
#include "stdio.h"
#include "sys/io.h"
#include <QDebug>

#define FREQ (600)//蜂鸣器参数

buzzerThread::buzzerThread(QObject *parent) :
    QThread(parent)
{
    ifAlarm = true;
    count=1;
}

void buzzerThread::run()
{
//    while(1)
//    {
//        if(count>0)
//        {
//            if(ifAlarm)
//            {
//                //蜂鸣器报警// 虚拟机下会闪退

//                int bit = 0;
//                iopl(3);  //修改端口权限，3及以上使之可以读写
//                printf("0\n");
//                outb(0xb6,0x43);   //outb( data, port )向端口输出8bit的数据
//                printf("1\n");
//                outb((FREQ & 0xff),0x42);  //FREQ为蜂鸣器的振动频率
//                outb(((FREQ >> 8) & 0xff),0x42);
//                bit=inb(0x61);
//                outb((3|bit),0x61);   //打开计算机的扬声器
//                usleep(1000*1000);
//                outb((0xfc & bit),0x61);   //关闭扬声器？待确定
//                iopl(0);    //修改端口为默认权限，0：不可以读写

//                mutex.lock();
//                count=count-1;
//                mutex.unlock();
//            }

//        }
//        msleep(1);
    //    }
}

void buzzerThread::slot_buzzerCount()
{
    mutex.lock();
    count=1;
    mutex.unlock();
}

//LYS-set if alarm 蜂鸣器报警
void buzzerThread::setIfAlarm(bool value)
{
    ifAlarm = value;
}

