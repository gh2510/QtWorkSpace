/************************************************************
** �ļ�����CompInfoDWListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-10-05
** ��  ����CompInfoDWListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef CompInfoDWListener_hh
#define CompInfoDWListener_hh

#include "dds/DataWriterListener.h"
class MonitorRecordAgent;

class CompInfoDWListener:public DataWriterListener
{
private:
	//����ָ��
	MonitorRecordAgent *m_pAgent;
public:
	//���캯��
	CompInfoDWListener(MonitorRecordAgent* pAgent);   //CompInfoDWListener.h
	//��������
	~CompInfoDWListener();   //CompInfoDWListener.h
	//on_offered_deadline_missed���������涨�Ľ�ֹ��ʱ����Ӧ�Ĵ�����
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pCompInfoDW, 
		const _OFFERED_DEADLINE_MISSED_STATUS& Status);     //CompInfoDWListener.h
};

#endif
