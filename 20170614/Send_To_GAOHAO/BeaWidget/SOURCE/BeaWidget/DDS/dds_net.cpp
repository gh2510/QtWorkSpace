#include "dds_net.h"
#include <QMetaType>

DDS_Net::DDS_Net()
{
    ddsRecv = NULL;
    ddsSend =NULL;
}

//初始化设备的DDS网络链接
long DDS_Net::InitDDSNet()
{
    long ret = 0;
#ifdef DDS_API_INCLUDE
    qRegisterMetaType<TimeStateInfo>("TimeStateInfo");
    ret = DomainInit(1,"");
    if(ret != 0)
    {
        cout<<"DomainInit  1 failed"<<endl;
        return -2;
    }
    ddsRecv = new RecvInfo();
    ret = ddsRecv->DDSSubscriber();
    if(ret == 0)
    {
        ddsSend = new SendInfo();
        ret = ddsSend->DDSPublisher();
    }
#endif
    return ret;
}

//释放DDS网络资源
void DDS_Net::ReleaseDDSNet()
{
#ifdef DDS_API_INCLUDE
    if(ddsRecv)
    {
        delete ddsRecv;
        ddsRecv = NULL;
    }
    if(ddsSend)
    {
        delete ddsSend;
        ddsSend =NULL;
    }
#endif
}

//发送时统信息
_RETURNCODE_T DDS_Net::sendTimeStateInfo(TimeStateInfo info)
{
    _RETURNCODE_T ret=0;
    ret = ddsSend->TimeStateInfoDataWriterObj->Write(info);
    return ret;
}

//析构方法
DDS_Net::~DDS_Net()
{
    ReleaseDDSNet();
}

