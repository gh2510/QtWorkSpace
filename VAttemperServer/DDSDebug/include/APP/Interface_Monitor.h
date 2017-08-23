/************************************************************
** 文件名：Interface_Monitor.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011/05/16
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011/8/26
** 描  述：Interface_Monitor头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _INTERFACEMONITOR_H
#define  _INTERFACEMONITOR_H


#include "Interface.h"

/**
* @ 开启监控服务
*/
void ServStartMonitorServer();    //Interface_Monitor.h

/**
* @ 获取节点固定状态信息
*/
_RETURNCODE_T ServGetNodeFixedInfo(char* pIPAddress,_NODE_FIXED_INFO &NodeFixedInfo);  //Interface_Monitor.h

/**
* @ 获取节点实时状态信息
*/
_RETURNCODE_T ServGetNodeRealtimeInfo(char* pIPAddress,_NODE_REALTIME_INFO &NodeRealTimeInfo);   //Interface_Monitor.h
/**
* @ 获取组件状态信息
*/
_RETURNCODE_T ServGetComponentInfo(char* pIPAddress,string strComponentName,_COMP_GINFO &CompGInfo);  //Interface_Monitor.h

/**
* @ 获取信息流状态信息
*/
_RETURNCODE_T ServGetDataStreamInfo(string strTopicName,unsigned long ulDomainId,_TOPIC_GLOBAL_INFO &TopicGlobalInfo);  //Interface_Monitor.h

/**
* @ 获取节点固定信息列表
*/
_NODE_FIXED_INFO_SEQ ServGetNodeFixedInfoTXList();  //Interface_Monitor.h

/**
* @ 获取主题简要信息列表
*/
_TOPIC_ID_SEQ ServGetTopicIDTXList();   //Interface_Monitor.h

#endif

