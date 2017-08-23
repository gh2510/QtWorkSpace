/************************************************************
** �ļ�����Topic.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Topicͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPIC_H_INCLUDED_
#define _DDS_TOPIC_H_INCLUDED_

#include "BasicTypes.h"
#include "dds/TopicDescription.h"

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
