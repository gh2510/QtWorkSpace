/************************************************************
** 文件名：CompInfoDWListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-10-05
** 描  述：CompInfoDWListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef CompInfoDWListener_hh
#define CompInfoDWListener_hh

#include "dds/DataWriterListener.h"
class MonitorRecordAgent;

class CompInfoDWListener:public DataWriterListener
{
private:
	//代理指针
	MonitorRecordAgent *m_pAgent;
public:
	//构造函数
	CompInfoDWListener(MonitorRecordAgent* pAgent);   //CompInfoDWListener.h
	//析构函数
	~CompInfoDWListener();   //CompInfoDWListener.h
	//on_offered_deadline_missed，当超过规定的截止期时，相应的处理函数
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pCompInfoDW, 
		const _OFFERED_DEADLINE_MISSED_STATUS& Status);     //CompInfoDWListener.h
};

#endif
