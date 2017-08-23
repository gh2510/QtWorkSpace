/************************************************************
** 文件名：QueryRequest.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 描  述：QueryRequest头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _QUERYREQUEST_H
#define _QUERYREQUEST_H

#include"mr/MRBasicTypes.h"
class QueryProcessor;
class QueryRequest{
protected:
	//信息查询指针
	QueryProcessor*  m_pQueryProcessor;

public:
	//查询的开始时间
	struct _TIME_T m_StartTime;
	//查询的结束时间
	struct _TIME_T m_EndTime;
	//当前时间
	int m_iCurrentSeconds;

private:
	//时间间隔
	_DURATION_T m_Duration;

public:
	//构造函数
	QueryRequest(QueryProcessor* pQueryProcessor, _TIME_T StartTime, _TIME_T EndTime, _DURATION_T Duration)
	{
		m_pQueryProcessor = pQueryProcessor;
		m_StartTime = StartTime;
		m_EndTime = EndTime;
		m_Duration = Duration;
		m_iCurrentSeconds = 0;
	}          //QueryRequest.h
	//析构函数
	virtual~QueryRequest(){}            //QueryRequest.h
	//执行函数
	virtual _RETURNCODE_T Execute() = 0;          ////QueryRequest.h
	//判断是否有新的请求
	virtual bool HaveNewRequest() 
	{
		return false;
	};                      //QueryRequest.h

	//获取查询的开始时间
	_TIME_T GetStartTime() 
	{
		return m_StartTime;
	}             //QueryRequest.h

	//获取查询的结束时间
	_TIME_T GetEndTime() 
	{
		return m_EndTime;
	}               //QueryRequest.h

	//获取时间间隔
	_DURATION_T GetDuration()
	{
		return m_Duration;
	}                    //QueryRequest.h

};
#endif

