#ifndef _RTPS_STATELESSWRITER_INCLUDED_H
#define _RTPS_STATELESSWRITER_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Writer.h"
#include "rtps/Message.h"

class RequestScheduler;
class ReaderProxy;

class StatelessWriter : public Writer{
public:
    //���캯��
    StatelessWriter(_GUID_T Guid,
        _LOCATOR_LIST_T     UnicastLocatorList,
        _LOCATOR_LIST_T     MulticastLocatorList,
        const _DATA_WRITER_QOS*    pQos,
        HistoryCache*     pHistoryCache,
        DataWriter*       pDataWriter,
        RequestScheduler  **pScheduleList);

    //��������
    virtual ~StatelessWriter();

    //���ȶ��г�ʼ��
    _RETURNCODE_T ScheduleListInit();

    //���ƥ��Ķ��Ķ�
	_RETURNCODE_T ReaderLocatorAdd( ReaderLocator* pReaderLocator);

    //ɾ��ƥ�䶩�Ķ�
    _RETURNCODE_T ReaderLocatorRemove( ReaderLocator* pReaderLocator);

	//��ѯƥ��Ķ��Ķ�
    ReaderLocator* MatchedLocatorLookup( _GUID_T AReaderGuid );

    //����Ƿ�����Deadline QoS
    _RETURNCODE_T DeadlineCheck();

    //�������ݷ��� ��DDSDataWriter����
    _RETURNCODE_T DataSend(_CACHE_CHANGE *pNewChange);


	//������ 2013-09-04 �޸�
	int GetMatchDataReaderNum()
	{
		return m_MatchedLocatorList.size();
	}

    //����Data����
    _RETURNCODE_T DataMessageGet( char** pMessage,_MESSAGE_LENGTH_LIST_T* pLengthList, _CACHE_CHANGE *pCacheChange, ReaderLocator *pReaderLocator);

    //����Data�ಥ����
    _RETURNCODE_T DataMessageMultiGet(char** pMessage, _MESSAGE_LENGTH_LIST_T* pLengthList, _CACHE_CHANGE *pSendChange);

    RequestScheduler** GetScheduleList()
	{ 
		return m_pScheduleList;
	}
	_READER_LOCATOR_LIST* GetLocatorList() 
	{ 
		return &m_MatchedLocatorList; 
	}


#ifdef VXWORKS 
	SEM_ID GetMutex() 
	{ 
		return m_hSemMutex; 
	}
#else
	HANDLE GetMutex() 
	{ 
		return m_hSemMutex; 
	}
#endif

    _RETURNCODE_T DataSendFinish(_SEQUENCE_NUMBER_T Seq);

	//�Ƿ��ȡ�ಥ
	bool IsMulticast();

	//���ݷ�Ƭ
	_RETURNCODE_T DataIntoFrag(char** pFrags, _MESSAGE_LENGTH_LIST_T* pFragsLengthList, _CACHE_CHANGE* pSendChange, _ENTITYID ReaderID);

private:
    
	_READER_LOCATOR_LIST m_MatchedLocatorList;
    //������ ������ʶ���ΪProxy
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
