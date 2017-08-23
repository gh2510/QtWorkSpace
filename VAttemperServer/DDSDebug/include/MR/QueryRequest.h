/************************************************************
** �ļ�����QueryRequest.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����QueryRequestͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _QUERYREQUEST_H
#define _QUERYREQUEST_H

#include"mr/MRBasicTypes.h"
class QueryProcessor;
class QueryRequest{
protected:
	//��Ϣ��ѯָ��
	QueryProcessor*  m_pQueryProcessor;

public:
	//��ѯ�Ŀ�ʼʱ��
	struct _TIME_T m_StartTime;
	//��ѯ�Ľ���ʱ��
	struct _TIME_T m_EndTime;
	//��ǰʱ��
	int m_iCurrentSeconds;

private:
	//ʱ����
	_DURATION_T m_Duration;

public:
	//���캯��
	QueryRequest(QueryProcessor* pQueryProcessor, _TIME_T StartTime, _TIME_T EndTime, _DURATION_T Duration)
	{
		m_pQueryProcessor = pQueryProcessor;
		m_StartTime = StartTime;
		m_EndTime = EndTime;
		m_Duration = Duration;
		m_iCurrentSeconds = 0;
	}          //QueryRequest.h
	//��������
	virtual~QueryRequest(){}            //QueryRequest.h
	//ִ�к���
	virtual _RETURNCODE_T Execute() = 0;          ////QueryRequest.h
	//�ж��Ƿ����µ�����
	virtual bool HaveNewRequest() 
	{
		return false;
	};                      //QueryRequest.h

	//��ȡ��ѯ�Ŀ�ʼʱ��
	_TIME_T GetStartTime() 
	{
		return m_StartTime;
	}             //QueryRequest.h

	//��ȡ��ѯ�Ľ���ʱ��
	_TIME_T GetEndTime() 
	{
		return m_EndTime;
	}               //QueryRequest.h

	//��ȡʱ����
	_DURATION_T GetDuration()
	{
		return m_Duration;
	}                    //QueryRequest.h

};
#endif

