#include "sendinfo.h"

SendInfo::SendInfo()
{
}

//发布信息
long SendInfo::DDSPublisher()
{
    TimeStateInfodataWriter = CreateDataWriter(
                "",
                1,
                "TimeStateInfo",
                "TimeStateInfo",
                NULL,
                NULL);
    if(TimeStateInfodataWriter == NULL)
    {
        cout<<"Create TimeStateInfodataWriter failed"<<endl;
        DeleteDataWriter(TimeStateInfodataWriter);
        DomainRelease(1);
        return -1;
    }
    TimeStateInfoDataWriterObj = TimeStateInfoDataWriter::Narrow(TimeStateInfodataWriter);
    if(TimeStateInfoDataWriterObj ==NULL)
    {
        cout<<"Narrow failed"<<endl;
        DeleteDataWriter(TimeStateInfodataWriter);
        DomainRelease(1);
        return -1;
    }
    return 0;
}
