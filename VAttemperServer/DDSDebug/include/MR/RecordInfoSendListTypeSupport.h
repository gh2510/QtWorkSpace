/************************************************************
** �ļ�����RecordInfoSendListTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-24
** �޸��ˣ���
** ��  �ڣ���
** ��  ����RecordInfoSendListTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/


#ifndef _RecordInfoSendListTYPESUPPORT_H_
#define _RecordInfoSendListTYPESUPPORT_H_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
#include "RecordInfoSendListAgent.h"
class DomainParticipant;

class RecordInfoSendListTypeSupport : public TypeSupport 
{
public:
	//ע����������
	static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName) 
	{
		Agent *pNewAgent = NULL;
		try 
		{
			pNewAgent = new RecordInfoSendListAgent(pDomainParticipant, strTypeName);
		}
		catch (_RETURNCODE_T &Ret) 
		{ 
			if (Ret == RETURNCODE_REGISTER_TYPE_EXISTED) 
			{ 
				delete pNewAgent; 
			} 
		}
		return RETURNCODE_OK;
	}                   //RecordInfoSendListTypeSupport.h

	//��ȡRecordInfoSendList��������
	static char* Get_Type_Name() 
	{
		return "RecordInfoSendList";
	}                  //RecordInfoSendListTypeSupport.h
};

#endif
