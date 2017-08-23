/************************************************************
** �ļ�����TopicDescription.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����ϣ
** ��  �ڣ�2010-01-18
** ��  ����TopicDescriptionͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPICDESCRIPTION_H_INCLUDED_
#define _DDS_TOPICDESCRIPTION_H_INCLUDED_

#include <string>
#include "dds/DomainEntity.h"

class DomainEntity;
class DomainParticipant;

using std::string;

class TopicDescription : public DomainEntity
{
private:
    //������
    string m_strName;
    //����������
    string m_strTypeName;
    //ָ������������������ߵ�ָ��
    DomainParticipant* m_pRelatedParticipant;

public:
    TopicDescription(string strTopicName, string strTypeName, DomainParticipant* pRelatedParticipant);
    virtual ~TopicDescription(){};

    //��ȡ������
    string Get_Name()
    {
        return m_strName;
    }

    //��ȡ����������
    string Get_Type_Name()
    {
        return m_strTypeName;
    }

	//����ContentFilteredTopic
	virtual string GetRealName()
    {
		return NULL;
	}

	virtual string GetRealTypeName()
    {
		return NULL;
	}

    //��ȡTopicDescription������DomainParticipant��ָ��
    DomainParticipant* Get_Participant()
    {
        return m_pRelatedParticipant;
    }

     //����Topic��m_name,m_typeName��topicName��typeName���Ƚ�
    virtual bool Equal(string strTopicName, string strTypeName)
    {
        return false;
    }
};

#endif
