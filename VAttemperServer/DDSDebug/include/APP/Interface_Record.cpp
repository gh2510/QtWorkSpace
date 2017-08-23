/************************************************************
** 文件名：Interface_Record.cpp
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：无
** 日  期：无
** 描  述：向外提供记录服务接口
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#include "Interface_Record.h"
#include "DDS/CReadConfig.h"

#pragma warning(disable:4996)
/************************************************************
** 函数名：ServStartRecordServer
** 输  入：无
** 输  出：无
** 功能描述：开启记录服务
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
void ServStartRecordServer()
{

	InfoProcessor *pProcessor = InfoProcessor::GetInstance();
	if (pProcessor == NULL)		pProcessor = InfoProcessor::CreateInstance();

	//如果已经开启则不再重新开启
	if(pProcessor->m_iFunc == 2 || pProcessor->m_iFunc == 3) return;

	//读配置文件，获取记录的域ID，进行记录
	//被监控的域在开启的时候就必须确定，后面不再更改。
	list<unsigned long> 	DomainIDList;
	_RETURNCODE_T Ret;
	int iRecordDomainCount;
	int iDomainId;	

	//DomainIDList.push_back(3);//测试

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

	DomainIDList.sort();	//排序才能去除重复值
	DomainIDList.unique();	//去除重复值

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
** 函数名：ServReleaseRecordServer
** 输  入：无
** 输  出：无
** 功能描述：关闭记录服务
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
void ServReleaseRecordServer()
{
	InfoProcessor *pProcessor = InfoProcessor::GetInstance();

	//如果已经被关闭则不再重复关闭
	if(pProcessor->m_iFunc == 0 || pProcessor->m_iFunc == 1)return;

	pProcessor->ReleaseInfoProcessorRecord();
	//析构查询处理器
	if(pProcessor->m_iFunc == 0)
	{
		QueryProcessor::DeleteInstance();
		InfoProcessor::DeleteInstance();
	}
	
}

/************************************************************
** 函数名：ServRecordEmptyTXT
** 输  入：无
** 输  出：_RETURNCODE_T，操作结果索引标识
** 功能描述：清空记录服务文件
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-03-05
** 版  本：Version 0.1
*************************************************************/
_RETURNCODE_T ServRecordEmptyTXT()  
{
	QueryProcessor *pQuery = QueryProcessor::GetInstance();
	if(pQuery != NULL)
		return pQuery->RecordEmpty();
	else return RETURNCODE_ERROR;
}


