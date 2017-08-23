/************************************************************
** 文件名：TopicInfoTypeSupport.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：TopicInfoTypeSupport头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _TopicInfoTYPESUPPORT_H_
#define _TopicInfoTYPESUPPORT_H_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"
#include "MRBasicTypes.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
#include "TopicInfoAgent.h"
class DomainParticipant;

class TopicInfoTypeSupport : public TypeSupport 
{
public:
	//注册主题类型
	static _RETURNCODE_T Register_Type(DomainParticipant* pDomainParticipant, string strTypeName) 
	{
		Agent *pNewAgent = NULL;
		try 
		{
			pNewAgent = new TopicInfoAgent(pDomainParticipant, strTypeName);
		}
		catch (_RETURNCODE_T &Ret) 
		{ 
			if (Ret == RETURNCODE_REGISTER_TYPE_EXISTED) { delete pNewAgent; } 
		}
		return RETURNCODE_OK;
	}   //TopicInfoTypeSupport.h

	//获取TopicInfo主题类型
	static char* Get_Type_Name() 
	{
		return "TopicInfo";
	}  //TopicInfoTypeSupport.h
};

#endif
