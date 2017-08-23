#include "recvinfo.h"
#include "datalistener.h"

RecvInfo::RecvInfo()
{
}

//订阅信息
long RecvInfo::DDSSubscriber()
{
    DataReader *dataReader = NULL;

    TimeStateInfoDataReaderObj = NULL;
    TimeStateInfo_Listener *TimeStateInfoListener = new TimeStateInfo_Listener;
    dataReader = CreateDataReader(
                "",
               1,
                "TimeStateInfo",
                "TimeStateInfo",
                TimeStateInfoListener,
                NULL);
    if(dataReader == NULL)
    {
        cout<<"Create TimeStateInfo DataReader failed"<<endl;
        DomainRelease(1);
        return -1;
    }
    TimeStateInfoDataReaderObj = TimeStateInfoDataReader::Narrow(dataReader);
    if(TimeStateInfoDataReaderObj == NULL)
    {
        DeleteDataReader(TimeStateInfoDataReaderObj);
        DomainRelease(1);
        return -1;
    }
    return 0;
}

RecvInfo::~RecvInfo()
{
    if(TimeStateInfoDataReaderObj ==NULL)
    {
        DeleteDataReader(TimeStateInfoDataReaderObj);
        DomainRelease(1);
    }
}
