/************************************************************
** 文件名：KeyedStringDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-20
** 修改人：无
** 日  期：无
** 描  述：KeyedStringDataReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRINGDATAREADER_H_INCLUDED_
#define _DDS_KEYEDSTRINGDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "mr/MRBasicTypes.h"
#include "DDS/DataReader.h"
#include "dds/KeyedString.h"
#include "APP/APP.h"


class KeyedStringDataReader : public DataReader
{
public:
    //构造函数
    KeyedStringDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~KeyedStringDataReader();

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
    _RETURNCODE_T Read(_KEYED_STRING_SEQ& ReceivedDataSeq, _SAMPLE_INFO_SEQ& InfoSeq, long lMaxSamples);

    //剪切需要读取的下一条数据
    _RETURNCODE_T Read_Next_Sample(KEYED_STRING* pReceivedData, _SAMPLE_INFO& SampleInfo);

    //用指向DataReader的指针构造StringDataReader对象
    static KeyedStringDataReader* Narrow(DataReader* pDataReader);

    DEF_NARROW_METHOD(KeyedStringDataReader);

    //剪切需要读取的所有实例数据
    _RETURNCODE_T Read_Instance(_KEYED_STRING_SEQ& ReceivedDataSeq,
        _SAMPLE_INFO_SEQ & InfoSeq,
        _INSTANCE_HANDLE_T Handle,
        long lMaxSamples);

    //剪切需要读取的下一个实例的所有数据
    _RETURNCODE_T Read_Next_Instance(_KEYED_STRING_SEQ& ReceivedDataSeq,
        _SAMPLE_INFO_SEQ & InfoSeq,
        _INSTANCE_HANDLE_T Previous_handle,
        long lMaxSamples);

    //查询实例
    _INSTANCE_HANDLE_T Lookup_Instance(KEYED_STRING Instance);

    //取键值
    _RETURNCODE_T Get_Key_Value(_KEYED_STRING_KEY_HOLDER& Key_holder, _INSTANCE_HANDLE_T Handle);

private:
	//应用组件的名称
    char *m_pAppName;

    //InstanceHandle到keyholder的映射
    _INSTANCE_HANDLE_TO_KEY_HOLDER m_InstanceHandletoKeyHolder;

};

#endif
