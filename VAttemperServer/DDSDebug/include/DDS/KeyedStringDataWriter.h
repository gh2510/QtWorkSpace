/************************************************************
** 文件名：KeyedStringDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-20
** 修改人：无
** 日  期：无
** 描  述：KeyedStringDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_KEYEDSTRINGDATAWRITER_H_INCLUDED_
#define _DDS_KEYEDSTRINGDATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "mr/MRBasicTypes.h"
#include "DDS/DataWriter.h"
#include "dds/KeyedString.h"
#include "APP/APP.h"

class Topic;
class DataWriterListener;
class Publisher;

class KeyedStringDataWriter : public DataWriter
{
public:
    //构造函数
    KeyedStringDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~KeyedStringDataWriter ();

    //绑定应用组件
    _RETURNCODE_T AppSet(const char *pAppName);

#ifdef _APP_FAULT_TOLERANT_
    //容错设置
    _RETURNCODE_T FaultTolerantSet();
#endif

#ifdef _APP_FAULT_TOLERANT_
    //容错判断
    bool FaultTolerantJudge();
#endif

#ifdef _APP_DATA_RECORD_
	//记录数据发送接收
	_RETURNCODE_T RecordData(_SEQUENCE_NUM SeqNum);
#endif

#ifdef _APP_SERVICE_MONITOR_
	//记录监控信息
	_RETURNCODE_T MonitorService(_TOPIC_STATUS Status);
#endif

    //写数据
    _RETURNCODE_T Write(KEYED_STRING Data, _INSTANCE_HANDLE_T Handle);

    //用指向DataWriter的指针构造StringDataWriter对象
    static KeyedStringDataWriter* Narrow(DataWriter* pDataWriter);

    DEF_NARROW_METHOD(KeyedStringDataWriter);

    //注册实例
    _INSTANCE_HANDLE_T Register_Instance(KEYED_STRING Instance);

    //注销实例
    _RETURNCODE_T Unregister_Instance(KEYED_STRING Instance, _INSTANCE_HANDLE_T Handle);

    //取键值
    _RETURNCODE_T Get_Key_Value(_KEYED_STRING_KEY_HOLDER& Key_holder, _INSTANCE_HANDLE_T Handle);

    //查询实例
    _INSTANCE_HANDLE_T Lookup_Instance(KEYED_STRING Instance);

    //删除实例
    _RETURNCODE_T Dispose(KEYED_STRING Instance, _INSTANCE_HANDLE_T Handle);

private:
#ifdef _APP_FAULT_TOLERANT_
    //是否需要容错处理
    bool m_bFtEnable;
#endif
    //应用组件的名称
    char *m_pAppName;

    //InstanceHandle到keyholder的映射
    _INSTANCE_HANDLE_TO_KEY_HOLDER m_InstanceHandletoKeyHolder;

};

#endif
