/************************************************************
** 文件名：DataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-17
** 修改人：杨猛
** 日  期：2011-03-05
** 描  述：DataReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAREADER_H_INCLUDED_
#define _DDS_DATAREADER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DomainEntity.h"

#ifdef KYLIN
#include <semaphore.h>
#endif

class DataReaderListener;
class Reader;
class Subscriber;
class TopicDescription;
class HistoryCache;
class Discovery;
class DomainParticipant;
class Participant;

#if defined(VXWORKS) || defined(_DDS_LIB_FILE) || defined(KYLIN)
class DataReader : public DomainEntity {
#else
class DDS_DLL DataReader : public DomainEntity 
{
#endif
protected:
    //所属于的订阅者
    Subscriber* m_pRelatedSubscriber;

    //用于创建本发布端的TopicDescription的指针
    TopicDescription* m_pRelatedTopic;

    //pListener监听的DataReader通讯状态变化
    _STATUS_MASK m_Mask;

    ////记录实例信息的列表
    //_SAMPLE_INFO_SEQ m_infoSeq;

    //SequenceNumber队列
    _SEQ_NUM_TO_HANDLE m_SeqNumtoHandle;

    //缓冲区大小
    unsigned long m_ulCacheLength;

    //缓冲区地址
    HistoryCache* m_pHistoryCache;

    //指向对应Reader的指针
    Reader* m_pRelatedReader;

    //保存接收过的实例标识InstanceHandle与instance信息的对应关系
    //InstanceMap_DR m_ReceivedInstance;

    //请求的Deadline未满足的状态
    //_REQUESTED_DEADLINE_MISSED_STATUS m_RequestedDeadlineMissedStatus;

	//用于判断匹配是否完成的信号量
#ifdef WIN32
	HANDLE m_hMatchSemaphore;
#elif KYLIN
	sem_t m_hMatchSemaphore;
#endif
public:
    DataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);    //DataReader.h
    //DataReader(DataReader& dataReader);
    virtual ~DataReader();

    //绑定应用组件
    virtual _RETURNCODE_T AppSet(const char *pAppName)      //DataReader.h
    {
        return RETURNCODE_OK;
    }

    //发送本DataReader的信息 用于发现
    virtual _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status);//DataReader.h

	//2013-09-27 hjy modify 用于发送删除内置的三个DataWriter信息
	virtual _RETURNCODE_T SendBuildinDataReaderDeleteInfo(_ENTITY_STATUS_T Status);

    //匹配
    virtual _RETURNCODE_T Match();  //DataReader.h

    //设置QoS
    virtual _RETURNCODE_T SetQos(const _DATA_READER_QOS* pQos);//DataReader.h
    // 
    //获取QoS
    virtual _DATA_READER_QOS* GetQos()          //DataReader.h
    {
        return (_DATA_READER_QOS*)m_pQos;
    }

    //返回属于的DomainParticipant
    DomainParticipant *GetDomainParticipant (); //DataReader.h

    //设置监听器
    virtual _RETURNCODE_T SetListener(DataReaderListener* pListener, _STATUS_MASK Mask);//DataReader.h

    //获取监听器
    virtual DataReaderListener* GetListener()   //DataReader.h
    {
        return (DataReaderListener*)m_pListener;
    }

    //获取DataReader相关的主题描述
    virtual TopicDescription* GetTopic()        //DataReader.h
    {
        return m_pRelatedTopic;
    }

    //返回所属订阅者
    virtual Subscriber* GetSubscriber()         //DataReader.h
    {
        return m_pRelatedSubscriber;
    }

    //获取对应的Reader
    virtual Reader* GetRelatedReader()          //DataReader.h
    {
        return m_pRelatedReader;
    }

    //获取缓冲区大小
    virtual unsigned long GetCacheLength()      //DataReader.h
    {
        return m_ulCacheLength;
    }

    //获取掩码
    virtual _STATUS_MASK GetMask()              //DataReader.h
    {
        return m_Mask;
    }

    //获取缓冲区地址
    virtual HistoryCache* GetHistoryCache()     //DataReader.h
    {
        return m_pHistoryCache;
    }

    //数据到达通知
    virtual _RETURNCODE_T DataReceive(_SEQUENCE_NUMBER_T SeqNum, _INSTANCE_HANDLE_T Handle);//DataReader.h

    ////删除实例信息
    //virtual _RETURNCODE_T deleteSampleInfo(_SEQUENCE_NUMBER_T SeqNum);

    //超时调用
    virtual _RETURNCODE_T DeadlineMissed(const _REQUESTED_DEADLINE_MISSED_STATUS& Status);  //DataReader.h

    //读数据
    _RETURNCODE_T ReadCache(char*& pMyDataValue, unsigned long& ulLeng, _INSTANCE_HANDLE_T& Handle, _CHANGE_KIND_T& Kind);//DataReader.h

    _RETURNCODE_T ReadCache(char*& pMyDataValue, unsigned long& ulLeng, _INSTANCE_HANDLE_T& Handle, _CHANGE_KIND_T& Kind, _SEQUENCE_NUMBER_T &Seq);//DataReader.h

    //_RETURNCODE_T readInstanceCache(char*& pMyDataValue, unsigned long& ulLeng, _CHANGE_KIND_T& Kind, _SEQUENCE_NUMBER_T seq);

    _CACHE_CHANGE *GetChange(_SEQUENCE_NUMBER_T SeqNum);    //DataReader.h

    _RETURNCODE_T RemoveChange(_SEQUENCE_NUMBER_T SeqNum);    //DataReader.h

    _RETURNCODE_T GetInstanceState(_INSTANCE_HANDLE_T Handle, InstanceStateKind& InstanceState);    //DataReader.h

	void MatchComplete();
	void WaitForMatch(int iNum);

    DEF_NARROW_METHOD(DataReader);
};

#endif
