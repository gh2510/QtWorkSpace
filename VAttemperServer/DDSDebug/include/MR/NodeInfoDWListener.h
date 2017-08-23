/************************************************************
** �ļ�����NodeInfoDWListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����NodeInfoDWListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef NodeInfoDWListener_hh
#define NodeInfoDWListener_hh

#include "dds/DataWriterListener.h"
class MonitorRecordAgent;

class NodeInfoDWListener:public DataWriterListener
{
private:
	//����ָ��
	MonitorRecordAgent *m_pAgent;
public:
	//���캯��
	NodeInfoDWListener(MonitorRecordAgent* pAgent);               //NodeInfoDWListener.h
	//��������
	~NodeInfoDWListener();                    //NodeInfoDWListener.h
	//on_offered_deadline_missed���������涨�Ľ�ֹ��ʱ����Ӧ�Ĵ�����
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pNodeInfoDW, 
		const _OFFERED_DEADLINE_MISSED_STATUS& Status);                     //NodeInfoDWListener.h
};
#endif
