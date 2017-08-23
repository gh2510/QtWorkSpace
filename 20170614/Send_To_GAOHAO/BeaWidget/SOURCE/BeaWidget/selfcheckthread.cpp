#include "selfcheckthread.h"
#include<QLibrary>
#include<QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/ethtool.h>
#include <sys/sysinfo.h>
#include <sys/statfs.h>


typedef int Status;
typedef struct{
    char devState;  //1:故障 0:正常
    char bBitable;  //0：不含无法诊断的故障 1：含无法诊断的故障
    char bitInfo[4]; //故障码 00：正常 01：故障 11：不能诊断
}DEVINFO,*PDEVINFO;


//Status CM6080bit(int mode,PDEVINFO pDevInfo);


SelfCheckThread::SelfCheckThread(QObject *parent) :
    QThread(parent)
{
    flag=true;
    selfCheck=NULL;
}

SelfCheckThread::~SelfCheckThread()
{
    delete selfCheck;
}

void SelfCheckThread::run()
{
    DEVINFO pp;
    selfCheck=new QLibrary("./libCM6080bit.so");
    selfCheck->load();
    if(!selfCheck->isLoaded())
    {
           return ;
    }
    typedef int (*cmFunction)(int ,PDEVINFO);
    cmFunction check=(cmFunction)selfCheck->resolve("CM6080bit");
    while(flag)
    {

        if(check)
        {
                check(10,&pp);
                if(int(pp.devState)==0)
                    emit sig_selfCheck(0);//0 正常
                else
                     emit sig_selfCheck(1);//1故障
        }
        sleep(10000);

    }
}
