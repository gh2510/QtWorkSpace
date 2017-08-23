/************************************************************
** 文件名：StringDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-16
** 修改人：无
** 日  期：无
** 描  述：StringDataReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_STRINGDATAREADER_H_INCLUDED_
#define _DDS_STRINGDATAREADER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataReader.h"
#include "APP/APP.h"

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class StringDataReader : public DataReader
{
#else
class DDS_DLL StringDataReader : public DataReader
{
#endif
public:
    //构造函数
    StringDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~StringDataReader();

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

    //剪切需要读取的所有数据
    //_RETURNCODE_T Read(_STRING_SEQ& receivedDataSeq, _SAMPLE_INFO_SEQ& infoSeq, long maxSamples);
    _RETURNCODE_T Read(_STRING_SEQ& ReceivedDataSeq, long lMaxSamples);

    //剪切需要读取的下一条数据
    //_RETURNCODE_T Read_Next_Sample(_DDS_STRING* receivedData, _SAMPLE_INFO& sampleInfo);
    _RETURNCODE_T Read_Next_Sample(_DDS_STRING& ReceivedData);

    //用指向DataReader的指针构造StringDataReader对象
    static StringDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(StringDataReader);

private:
	//应用组件的名称
    char *m_pAppName;

};

#endif
