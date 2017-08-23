/************************************************************
** �ļ�����ParticipantDataReader.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ParticipantDataReaderͷ�ļ�
** ��  ����Version 0.1
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
    //���캯��
    ParticipantDataReader(TopicDescription* pTopic,
        const _DATA_READER_QOS* pQos,
        DataReaderListener* pListener,
        _STATUS_MASK Mask,
        Subscriber* pSubscriber,
        unsigned long ulCacheLength);

    //��������
    virtual ~ParticipantDataReader();

    //������Ҫ��ȡ����������
    //_RETURNCODE_T read(_STRING_SEQ& receivedDataSeq, _SAMPLE_INFO_SEQ& infoSeq, long maxSamples);
    //_RETURNCODE_T read(_STRING_SEQ& receivedDataSeq, long maxSamples);

    //������Ҫ��ȡ����һ������
    _RETURNCODE_T Read_Next_Sample(_SPDP_DISCOVERED_PARTICIPANT_DATA* pReceivedData);

    //��ָ��DataReader��ָ�빹��StringDataReader����
    static ParticipantDataReader* Narrow(DataReader* pDataReader);

    //����Զ�˵�Participant��Ϣ
    _RETURNCODE_T ReceiveRemoteParticipantData(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    DEF_NARROW_METHOD(ParticipantDataReader);

    ParticipantDataManager *GetParticipantDataManager() 
    {
        return m_pDataManager;
    }

    //���������Լ��Զ��DomainParticipant�Ƿ�����߳�
#ifdef VXWORKS
	int CheckTaskStart();
#else
	HANDLE CheckTaskStart();
#endif

    //����״̬��Ϣ
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

    //ƥ��
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

	void deleteCheckTask() 
    {
//#ifdef VXWORKS
//		if (m_iCheckTaskId != ERROR) 
//        {
//			taskDelete(m_iCheckTaskId);
//		}
//#else
//		if(m_hCheckHandle != NULL)
//        {
//			TerminateThread(m_hCheckHandle, 0);
//			CloseHandle(m_hCheckHandle);
//		}
//#endif
	}

private:
    //Զ��Participant������
    ParticipantDataManager *m_pDataManager;

    //�߳�id
#ifdef VXWORKS
	int m_iCheckTaskId;
#else
	HANDLE m_hCheckHandle;
#endif
};

#endif
