/************************************************************
** 文件名：NodeInfoDWListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：NodeInfoDWListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef NodeInfoDWListener_hh
#define NodeInfoDWListener_hh

#include "dds/DataWriterListener.h"
class MonitorRecordAgent;

class NodeInfoDWListener:public DataWriterListener
{
private:
	//代理指针
	MonitorRecordAgent *m_pAgent;
public:
	//构造函数
	NodeInfoDWListener(MonitorRecordAgent* pAgent);               //NodeInfoDWListener.h
	//析构函数
	~NodeInfoDWListener();                    //NodeInfoDWListener.h
	//on_offered_deadline_missed，当超过规定的截止期时，相应的处理函数
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pNodeInfoDW, 
		const _OFFERED_DEADLINE_MISSED_STATUS& Status);                     //NodeInfoDWListener.h
};
#endif
