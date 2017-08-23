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
    //构造函数
    ReaderLocator( _GUID_T ReaderGuid,
				   _LOCATOR_LIST_T UnicastLocatorList,
				   _LOCATOR_LIST_T MulticastLocatorList,
				   StatelessWriter* pStatelessWriter);

    //析构函数
    virtual ~ReaderLocator();

    //获取本ReaderProxy代表的远端订阅端点的GUID
	_GUID_T ReaderGuid() {
		return m_RemoteReaderGuid;
	};

    //获取单播地址
    _LOCATOR_T UnicastLocatorGet() {
        return m_UnicastLocatorList[0];
    }

	_LOCATOR_T MulticastLocatorGet() {
        return m_MulticastLocatorList[0];
    }
    bool UnsentChanges();
	//添加CacheChange对象
    _RETURNCODE_T UnsentChangeAdd(_CACHE_CHANGE* pCacheChange );

	_CACHE_CHANGE* NextUnsentChange();
	void PopNext();

    //是否存在多播地址
    bool MulticastExist() {
        if (m_MulticastLocatorList.size() == 0)
            return false;
        return true;
    }

private:
    //远端订阅端点的GUID
    _GUID_T               m_RemoteReaderGuid;

    //对应的StatelessWriter
    StatelessWriter       *m_pRelatedWriter;

    //远端订阅端单播地址列表
    _LOCATOR_LIST_T       m_UnicastLocatorList;

    //远端订阅端多播地址列表
    _LOCATOR_LIST_T       m_MulticastLocatorList;

	_CACHE_CHANGE_LIST_T  m_UnsentChanges;

    bool                  m_bIsActive;

    //互斥锁 互斥访问m_changesForReader、m_nextRepairTime
#ifdef VXWORKS   //移植
	SEM_ID m_hSemMutex;
#else
	HANDLE m_hSemMutex;
#endif
};

#endif
