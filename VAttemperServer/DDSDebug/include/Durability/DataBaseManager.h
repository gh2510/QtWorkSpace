/************************************************************
** �ļ�����DataBaseManager.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-03-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataBaseManagerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _API_HISTORICDATABASEMANAGER_H_INCLUDED_
#define _API_HISTORICDATABASEMANAGER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

#ifdef VXWORKS  //��ֲ
 #include <semLib.h>
#else
#include "Windows.h"
#endif

#pragma warning(disable:4251)

struct _HISTORIC_DATA
{
	unsigned long ulDomainId;
	char* pTopic_name;
	char* pType_name; 
	_ENTITY_QOS Qos; 
	unsigned long ulDatalen;
	char* pData; 
};

#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
class DataBaseManager 
{
#else
class DDS_DLL DataBaseManager 
{
#endif
public:
	//��ȡDataBaseManager����ָ��
    static DataBaseManager* Get_Instance();

	//��������
	static _RETURNCODE_T SaveData(_HISTORIC_DATA* pHistoricData);

	//�������
	_RETURNCODE_T GetData(unsigned long ulDomainId, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

	//����Ƿ��������
	bool CheckData(unsigned long ulDomainId, _DISCOVERED_READER_DATA* pDiscoveredReaderData);

private:
	DataBaseManager();
	~DataBaseManager();
    static DataBaseManager* m_pInstance;
	static vector<_HISTORIC_DATA*> m_DataList;

#ifdef VXWORKS  
	static _RETURNCODE_T HistoricDataStoreRun(void);
#else
	static DWORD WINAPI HistoricDataStoreRun(void);
#endif

	//������
#ifdef VXWORKS   //��ֲ
	static SEM_ID m_hSemMutex;
#else
	static HANDLE m_hSemMutex;
#endif

	//��ʷ���ݴ洢β�������߳�/�����
#ifdef VXWORKS  
	int m_hTaskId;
#else
	HANDLE m_hTaskId;
#endif

};

#endif
