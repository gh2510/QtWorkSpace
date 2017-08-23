/************************************************************
** 文件名：Topic.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：Topic头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPIC_H_INCLUDED_
#define _DDS_TOPIC_H_INCLUDED_

#include "BasicTypes.h"
#include "dds/TopicDescription.h"
#ifdef KYLIN
#include <string.h>
#endif
class DomainParticipant;

class Topic : public TopicDescription
{
public:
    Topic(string strTopicName, string strTypeName, DomainParticipant* pRelatedParticipant);

	string GetRealName()
	{
		return Get_Name();
	}

	string GetRealTypeName()
	{
		return Get_Type_Name();
	}

	bool Equal(string strTopicName, string strTypeName)
    {
        if (strcmp((Get_Name()).c_str(), strTopicName.c_str()) == 0 && strcmp((Get_Type_Name()).c_str(), strTypeName.c_str()) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual ~Topic() {}
};

#endif
