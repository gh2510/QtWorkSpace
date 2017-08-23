#ifndef RTPS_READERLOCATOR_INCLUDED_H
#define RTPS_READERLOCATOR_INCLUDED_H

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "rtps/Message.h"

#ifdef VXWORKS
#include <semLib.h>
#else
#include "Windows.h"
#endif

class StatelessWriter;
class HistoryCache;

class ReaderLocator{
public:
    //���캯��
    ReaderLocator( _GUID_T ReaderGuid,
				   _LOCATOR_LIST_T UnicastLocatorList,
				   _LOCATOR_LIST_T MulticastLocatorList,
				   StatelessWriter* pStatelessWriter);

    //��������
    virtual ~ReaderLocator();

    //��ȡ��ReaderProxy�����Զ�˶��Ķ˵��GUID
	_GUID_T ReaderGuid() {
		return m_RemoteReaderGuid;
	};

    //��ȡ������ַ
    _LOCATOR_T UnicastLocatorGet() {
        return m_UnicastLocatorList[0];
    }

	_LOCATOR_T MulticastLocatorGet() {
        return m_MulticastLocatorList[0];
    }
    bool UnsentChanges();
	//���CacheChange����
    _RETURNCODE_T UnsentChangeAdd(_CACHE_CHANGE* pCacheChange );

	_CACHE_CHANGE* NextUnsentChange();
	void PopNext();

    //�Ƿ���ڶಥ��ַ
    bool MulticastExist() {
        if (m_MulticastLocatorList.size() == 0)
            return false;
        return true;
    }

private:
    //Զ�˶��Ķ˵��GUID
    _GUID_T               m_RemoteReaderGuid;

    //��Ӧ��StatelessWriter
    StatelessWriter       *m_pRelatedWriter;

    //Զ�˶��Ķ˵�����ַ�б�
    _LOCATOR_LIST_T       m_UnicastLocatorList;

    //Զ�˶��Ķ˶ಥ��ַ�б�
    _LOCATOR_LIST_T       m_MulticastLocatorList;

	_CACHE_CHANGE_LIST_T  m_UnsentChanges;

    bool                  m_bIsActive;

    //������ �������m_changesForReader��m_nextRepairTime
#ifdef VXWORKS   //��ֲ
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
