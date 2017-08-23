/************************************************************
** 文件名：DataWriter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：DataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAWRITER_H_INCLUDED_
#define _DDS_DATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DomainEntity.h"



class DataWriterListener;
class Writer;
class Publisher;
class Topic;
class HistoryCache;
class DomainEntity;
class Discovery;
class DomainParticipant;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE) || defined(KYLIN)
class DataWriter : public DomainEntity {
#else
class DDS_DLL DataWriter : public DomainEntity 
{
#endif
protected:
    //绑定的主题的指针
    Topic* m_pRelatedTopic;

    //pListener监听的DataWriter通讯状态变化
    _STATUS_MASK m_Mask;

    //所属于的发布者
    Publisher* m_pRelatedPublisher;

    //缓冲区地址
    HistoryCache* m_pHistoryCache;

    //指向对应Writer的指针
    Writer* m_pRelatedWriter;

    //保存注册过的实例标识InstanceHandle与instance信息的对应关系
    //InstanceMap_DW m_registeredInstance;

    //提供的Deadline未满足的状态
    //_OFFERED_DEADLINE_MISSED_STATUS m_OfferedDeadlineMissedStatus;

	//用于判断匹配是否完成的信号量
#ifdef WIN32
	HANDLE m_hMatchSemaphore;
#elif KYLIN
	sem_t m_hMatchSemaphore;
#endif
public:
    DataWriter(Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);
    //DataWriter(DataWriter& pDataWriter);
    virtual ~DataWriter();

	//绑定应用组件
	virtual _RETURNCODE_T AppSet(const char *pAppName)
    {
        return RETURNCODE_OK;
    }

    //发送本DataWriter的信息 用于发现
    virtual _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status);

	//2013-09-27 hjy modify 用于发送删除内置的三个DataWriter信息
	virtual _RETURNCODE_T SendDeleteInfo(_ENTITY_STATUS_T Status);

    //匹配
    virtual _RETURNCODE_T Match();

    //设置DataWriterListener
    virtual _RETURNCODE_T SetListener(DataWriterListener* pListener, _STATUS_MASK Mask);

    //获取DataWriterListener
    virtual DataWriterListener* GetListener() 
    {
        return (DataWriterListener*)m_pListener;
    }

    //返回属于的DomainParticipant
    DomainParticipant *GetDomainParticipant ();

    //设置QoS
    virtual _RETURNCODE_T SetQos(const _DATA_WRITER_QOS* pQos);

    //获取QoS
    virtual _DATA_WRITER_QOS* GetQos()
    {
        return (_DATA_WRITER_QOS *)m_pQos;
    }

    //获取此DataWriter相关联的主题
    virtual Topic* GetTopic() 
    {
        return m_pRelatedTopic;
    }

    //获取本DataWriter所属于的发布者
    virtual Publisher* GetPublisher() 
    {
        return m_pRelatedPublisher;
    }

    //获取对应的Writer
    virtual Writer* GetRelatedWriter()
    {
        return m_pRelatedWriter;
    }

    //获取掩码
    virtual _STATUS_MASK GetMask() 
    {
        return m_Mask;
    }

    //获取缓冲区地址
    virtual HistoryCache* GetHistoryCache() 
    {
        return m_pHistoryCache;
    }

    //写数据完毕后通知结束
    virtual _RETURNCODE_T WriteFinished(_SEQUENCE_NUMBER_T SeqNum);

    //超时调用
    virtual _RETURNCODE_T DeadlineMissed(const _OFFERED_DEADLINE_MISSED_STATUS& Status);

    _RETURNCODE_T WriteToCache(char* pData,int iSize, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle);

    _RETURNCODE_T WriteToCache(char* pData,int iSize, _CHANGE_KIND_T Kind, _INSTANCE_HANDLE_T Handle, _SEQUENCE_NUMBER_T &SeqNum);

	void MatchComplete();
	void WaitForMatch(int iNum);

    DEF_NARROW_METHOD(DataWriter);
};

#endif
