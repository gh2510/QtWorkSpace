/************************************************************
** 文件名：TopicDescription.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：杨猛<635584332@qq.com>
** 日  期：2010-01-18
** 描  述：TopicDescription头文件
** 版  本：Version 0.1
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
    //主题名
    string m_strName;
    //主题类型名
    string m_strTypeName;
    //指向主题所属的域参与者的指针
    DomainParticipant* m_pRelatedParticipant;

public:
    TopicDescription(string strTopicName, string strTypeName, DomainParticipant* pRelatedParticipant);
    virtual ~TopicDescription(){};

    //获取主题名
    string Get_Name()
    {
        return m_strName;
    }

    //获取主题类型名
    string Get_Type_Name()
    {
        return m_strTypeName;
    }

	//用于ContentFilteredTopic
	virtual string GetRealName()
    {
		return NULL;
	}

	virtual string GetRealTypeName()
    {
		return NULL;
	}

    //获取TopicDescription所属的DomainParticipant的指针
    DomainParticipant* Get_Participant()
    {
        return m_pRelatedParticipant;
    }

     //将本Topic的m_name,m_typeName与topicName，typeName作比较
    virtual bool Equal(string strTopicName, string strTypeName)
    {
        return false;
    }
};

#endif
