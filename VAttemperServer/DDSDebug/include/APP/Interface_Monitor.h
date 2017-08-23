/************************************************************
** �ļ�����Interface_Monitor.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/05/16
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011/8/26
** ��  ����Interface_Monitorͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _INTERFACEMONITOR_H
#define  _INTERFACEMONITOR_H


#include "Interface.h"

/**
* @ ������ط���
*/
void ServStartMonitorServer();    //Interface_Monitor.h

/**
* @ ��ȡ�ڵ�̶�״̬��Ϣ
*/
_RETURNCODE_T ServGetNodeFixedInfo(char* pIPAddress,_NODE_FIXED_INFO &NodeFixedInfo);  //Interface_Monitor.h

/**
* @ ��ȡ�ڵ�ʵʱ״̬��Ϣ
*/
_RETURNCODE_T ServGetNodeRealtimeInfo(char* pIPAddress,_NODE_REALTIME_INFO &NodeRealTimeInfo);   //Interface_Monitor.h
/**
* @ ��ȡ���״̬��Ϣ
*/
_RETURNCODE_T ServGetComponentInfo(char* pIPAddress,string strComponentName,_COMP_GINFO &CompGInfo);  //Interface_Monitor.h

/**
* @ ��ȡ��Ϣ��״̬��Ϣ
*/
_RETURNCODE_T ServGetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicGlobalInfo);  //Interface_Monitor.h

/**
* @ ��ȡ�ڵ�̶���Ϣ�б�
*/
_NODE_FIXED_INFO_SEQ ServGetNodeFixedInfoTXList();  //Interface_Monitor.h

/**
* @ ��ȡ�����Ҫ��Ϣ�б�
*/
_TOPIC_ID_SEQ ServGetTopicIDTXList();   //Interface_Monitor.h

#endif

