/************************************************************
** �ļ�����APP.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-10
** �޸��ˣ���
** ��  �ڣ���
** ��  ����APPͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _GLOBAL_APP_H_INCLUDED_
#define _GLOBAL_APP_H_INCLUDED_

//#define _APP_DATA_RECORD_
//#define _APP_SERVICE_MONITOR_
//#define _APP_FAULT_TOLERANT_

//�ݴ�
#ifdef _APP_FAULT_TOLERANT_
#include "APP/FTInterface.h"
#endif

//���ݼ�¼
#ifdef _APP_DATA_RECORD_
#include "APP/Interface_Record.h"
#endif

//��ط���
#ifdef _APP_SERVICE_MONITOR_
#include "APP/Interface_Monitor.h"
#endif

#endif
