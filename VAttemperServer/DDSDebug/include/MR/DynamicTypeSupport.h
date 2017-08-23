/************************************************************
** 文件名：DynamicTypeSupport.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-24
** 描  述：DynamicTypeSupport头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DynamicTYPESUPPORT_H_
#define _DynamicTYPESUPPORT_H_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
#include "DynamicAgent.h"
class DomainParticipant;

class DynamicTypeSupport : public TypeSupport 
{
public:
	//static char* m_typeName;
	//注册主题类型
	static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName) 
	{
		//const char* CCtypeName = strTypeName.c_str();
		//char* CtypeName = new char[strlen(CCtypeName)+1];
		//strcpy(m_typeName, CtypeName);
		Agent *pNewAgent = NULL;
		try 
		{
			pNewAgent = new DynamicAgent(pDomainParticipant, strTypeName);
		}
		catch (_RETURNCODE_T &Ret) 
		{ 
			if (Ret == RETURNCODE_REGISTER_TYPE_EXISTED) { delete pNewAgent; } 
		}
		return RETURNCODE_OK;
	}   //DynamicTypeSupport.h

	//获取Dynamic主题类型,此函数无用，
	//static char* get_type_name() { return "Dynamic";}
};

#endif
