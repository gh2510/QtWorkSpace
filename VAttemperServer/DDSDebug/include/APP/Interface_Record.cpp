/************************************************************
** �ļ�����Interface_Record.cpp
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ���������ṩ��¼����ӿ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#include "Interface_Record.h"
#include "DDS/CReadConfig.h"

#pragma warning(disable:4996)
/************************************************************
** ��������ServStartRecordServer
** ��  �룺��
** ��  ������
** ����������������¼����
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
void ServStartRecordServer()
{

	InfoProcessor *pProcessor = InfoProcessor::GetInstance();
	if (pProcessor == NULL)		pProcessor = InfoProcessor::CreateInstance();

	//����Ѿ������������¿���
	if(pProcessor->m_iFunc == 2 || pProcessor->m_iFunc == 3) return;

	//�������ļ�����ȡ��¼����ID�����м�¼
	//����ص����ڿ�����ʱ��ͱ���ȷ�������治�ٸ��ġ�
	list<unsigned long> 	DomainIDList;
	_RETURNCODE_T Ret;
	int iRecordDomainCount;
	int iDomainId;	

	//DomainIDList.push_back(3);//����

#ifdef VXWORKS
	char* pPath = "/ata0a/DDS/ddsconfig.conf";
#else
	char* pPath = "./common/ddsconfig.conf";
#endif

	CReadConfig* pConfigReader = new CReadConfig;

	Ret = pConfigReader->GetConfigInt("RecordDomainCount", "RecordDomainCount", &iRecordDomainCount, pPath);
	if (Ret != RETURNCODE_OK || iRecordDomainCount <= 0) 
	{
		return;
	}
	for(int I = 0; I < iRecordDomainCount; I ++)
	{
		char szDomainIdtemp[50];
		sprintf( szDomainIdtemp, "RecordDomain[%d]", I);
		Ret = pConfigReader->GetConfigInt("RecordDomainCount", szDomainIdtemp, &iDomainId, pPath);
		if (Ret != RETURNCODE_OK) 
		{
			return;
		}
		DomainIDList.push_back((unsigned long)iDomainId);
	}

	DomainIDList.sort();	//�������ȥ���ظ�ֵ
	DomainIDList.unique();	//ȥ���ظ�ֵ

	list<string> TopicRecordName;
	int iRecordTopicCount;
	char szTopicName[100];

	Ret = pConfigReader->GetConfigInt("RecordTopicCount", "RecordTopicCount", &iRecordTopicCount, pPath);
	if (Ret != RETURNCODE_OK) 
	{
		return;
	}
	for(int J = 0; J < iRecordTopicCount; J ++)
	{
		char szTopicNametemp[100];
		sprintf(szTopicNametemp, "RecordTopic[%d]", J);
		Ret = pConfigReader->GetConfigStr("RecordTopicCount", szTopicNametemp, szTopicName, sizeof(szTopicName), pPath);
		if (Ret != RETURNCODE_OK)
		{
			return;
		}
		string strTopic(szTopicName);
		TopicRecordName.push_back(strTopic);
	}

	pProcessor->StartInfoProcessorRecord(DomainIDList, TopicRecordName);

	cout<<"StartInfoProcessorRecord successfull..."<<endl;
}


/************************************************************
** ��������ServReleaseRecordServer
** ��  �룺��
** ��  ������
** �����������رռ�¼����
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
void ServReleaseRecordServer()
{
	InfoProcessor *pProcessor = InfoProcessor::GetInstance();

	//����Ѿ����ر������ظ��ر�
	if(pProcessor->m_iFunc == 0 || pProcessor->m_iFunc == 1)return;

	pProcessor->ReleaseInfoProcessorRecord();
	//������ѯ������
	if(pProcessor->m_iFunc == 0)
	{
		QueryProcessor::DeleteInstance();
		InfoProcessor::DeleteInstance();
	}
	
}

/************************************************************
** ��������ServRecordEmptyTXT
** ��  �룺��
** ��  ����_RETURNCODE_T���������������ʶ
** ������������ռ�¼�����ļ�
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����Version 0.1
*************************************************************/
_RETURNCODE_T ServRecordEmptyTXT()  
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->RecordEmpty();
	else return RETURNCODE_ERROR;
}


