/************************************************************
** 文件名：DynamicDataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-03-30
** 修改人：无
** 日  期：无
** 描  述：DynamicDataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DYNAMICDATAWRITER_H_INCLUDED_
#define _DDS_DYNAMICDATAWRITER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"

class Topic;
class DataWriterListener;
class Publisher;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DynamicDataWriter : public DataWriter 
{
#else
class DDS_DLL DynamicDataWriter : public DataWriter 
{
#endif
public:
    //构造函数
    DynamicDataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~DynamicDataWriter();

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
    _RETURNCODE_T Write(char* pData, unsigned long ulLen);

    //用指向DataWriter的指针构造StringDataWriter对象
    static DynamicDataWriter* Narrow(DataWriter* pDataWriter);

    DEF_NARROW_METHOD(DynamicDataWriter);

private:
#ifdef _APP_FAULT_TOLERANT_
    //是否需要容错处理
    bool m_bFtEnable;
#endif
    //应用组件的名称
    char *m_pAppName;

};

#endif
