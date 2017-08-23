/************************************************************
** 文件名：ParticipantDataReader.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：ParticipantDataReader头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_PARTICIPANTDATAREADER_H_INCLUDED_
#define _DDS_PARTICIPANTDATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DataReader.h"

class ParticipantDataManager;

class ParticipantDataReader : public DataReader 
{
public:
    //构造函数
    ParticipantDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //析构函数
    virtual ~ParticipantDataReader();

    //剪切需要读取的所有数据
    //_RETURNCODE_T read(_STRING_SEQ& receivedDataSeq, _SAMPLE_INFO_SEQ& infoSeq, long maxSamples);
    //_RETURNCODE_T read(_STRING_SEQ& receivedDataSeq, long maxSamples);

    //剪切需要读取的下一条数据
    _RETURNCODE_T Read_Next_Sample(_SPDP_DISCOVERED_PARTICIPANT_DATA* pReceivedData);

    //用指向DataReader的指针构造StringDataReader对象
    static ParticipantDataReader* Narrow(DataReader* pDataReader);

    //接收远端的Participant信息
    _RETURNCODE_T ReceiveRemoteParticipantData(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    DEF_NARROW_METHOD(ParticipantDataReader);

    ParticipantDataManager *GetParticipantDataManager() 
    {
        return m_pDataManager;
    }

    //启动周期性检查远端DomainParticipant是否存活的线程
#if defined  VXWORKS || defined KYLIN
	int CheckTaskStart();
#else
	HANDLE CheckTaskStart();
#endif

    //发送状态信息
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		if (Status == CREATION)
		{
			//cout<<"ppppppppppppppppppppppppppppppp"<<endl;
			return RETURNCODE_OK;
		}
		else if (Status == DELETION)
		{
			//cout<<"qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"<<endl;
			return RETURNCODE_OK;
		}
		else
			return RETURNCODE_OK;
    }

	//_RETURNCODE_T SendDeleteInfo(_ENTITY_STATUS_T Status) 
	//{
	//	DomainParticipant* pDomainParticipant = this->GetDomainParticipant();
	//	Discovery* pDiscovery= pDomainParticipant->GetRelatedDiscovery();
	//	return pDiscovery->SendPublicationData(this, Status);
	//}

    //匹配
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

	void deleteCheckTask() 
    {
#ifdef VXWORKS
		if (m_iCheckTaskId != ERROR) 
        {
			taskDelete(m_iCheckTaskId);
		}
#elif WIN32
		if(m_hCheckHandle != NULL)
        {
			TerminateThread(m_hCheckHandle, 0);
			CloseHandle(m_hCheckHandle);
		}
#elif KYLIN
		if (m_hCheck_create_ret == 0)
		{
			pthread_cancel(m_hCheckthread);
		}
#endif
	}

private:
    //远端Participant的数据
    ParticipantDataManager *m_pDataManager;

    //线程id
#if defined VXWORKS
	int m_iCheckTaskId;
#elif WIN32
	HANDLE m_hCheckHandle;
#elif KYLIN
	pthread_t m_hCheckthread;
	int m_hCheck_create_ret;
#endif
};

#endif
