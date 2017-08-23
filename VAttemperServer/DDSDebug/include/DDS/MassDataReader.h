//大数据
/************************************************************
** 文件名：MassDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2013-07-22
** 修改人：无
** 日  期：无
** 描  述：MassDataReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_MASSDATAREADER_H_INCLUDED_
#define _DDS_MASSDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataReader.h"
#include "APP/APP.h"

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class MassDataReader : public DataReader
{
#else
class DDS_DLL MassDataReader : public DataReader
{
#endif
public:
    //构造函数
    MassDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~MassDataReader();

	//绑定应用组件
	_RETURNCODE_T AppSet(const char *pAppName);

#ifdef _APP_DATA_RECORD_
	//记录数据发送接收
	_RETURNCODE_T RecordData(_SEQUENCE_NUM SeqNum);
#endif
	
#ifdef _APP_SERVICE_MONITOR_
	//记录监控信息
	_RETURNCODE_T MonitorService(_TOPIC_STATUS Status);
#endif


    //剪切需要读取的下一条数据
    //_RETURNCODE_T Read_Next_Sample(_DDS_STRING* receivedData, _SAMPLE_INFO& sampleInfo);

	_RETURNCODE_T ReceiveData(char *Data,unsigned long len);
    _RETURNCODE_T Read_Next_Sample(char *&ReceivedData, unsigned long &len);
	_RETURNCODE_T DataNotify(_GUID_T writerID,unsigned long DataNum);
	_RETURNCODE_T Read_Next_Data(char *&ReceivedData, unsigned long &len);

    //用指向DataReader的指针构造MassDataReader对象
    static MassDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(MassDataReader);

private:
	//应用组件的名称
    char *m_pAppName;
	_MASS_FRAGMENT_DATA_LIST_T m_FragmentDataList;
	_MASS_DATA_LIST_T m_DataList;

};

#endif
