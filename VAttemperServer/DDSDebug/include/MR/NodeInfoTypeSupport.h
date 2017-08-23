/************************************************************
** �ļ�����NodeInfoTypeSupport.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-24
** ��  ����NodeInfoTypeSupportͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _NodeInfoTYPESUPPORT_H_
#define _NodeInfoTYPESUPPORT_H_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
#include "NodeInfoAgent.h"
class DomainParticipant;

class NodeInfoTypeSupport : public TypeSupport 
{
public:
	//ע��ڵ�״̬��Ϣ��������
	static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName) 
	{
		Agent *pNewAgent = NULL;
		try 
		{
			pNewAgent = new NodeInfoAgent(pDomainParticipant, strTypeName);
		}
		catch (_RETURNCODE_T &Ret) 
		{ 
			if (Ret == RETURNCODE_REGISTER_TYPE_EXISTED) 
			{ 
				delete pNewAgent; 
			} 
		}
		return RETURNCODE_OK;
	}                           //NodeInfoTypeSupport.h

	//��ȡ�ڵ�״̬��Ϣ��������
	static char* Get_Type_Name()
	{ 
		return "NodeInfo";
	}                               //NodeInfoTypeSupport.h
};

#endif
