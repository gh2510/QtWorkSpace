#include "datalistener.h"
#include <QDebug>
#include <DDS/netdevice.h>

//时统信息
_RETURNCODE_T TimeStateInfo_Listener::On_Data_Available(DataReader *pDataReader)
{
    TimeStateInfoDataReader *myDataReader = NULL;
    _RETURNCODE_T ret;
    TimeStateInfo TimeStateInfoObj;
    myDataReader = TimeStateInfoDataReader::Narrow(pDataReader);
    if(myDataReader==NULL)
    {
        return -1;
    }
    ret = myDataReader->Read_Next_Sample(TimeStateInfoObj);
    if(ret!=RETURNCODE_OK)
    {
        return -1;
    }
    NetDevice::getNetDevice()->RecvTimeStateInfo(TimeStateInfoObj);
    return RETURNCODE_OK;
}
