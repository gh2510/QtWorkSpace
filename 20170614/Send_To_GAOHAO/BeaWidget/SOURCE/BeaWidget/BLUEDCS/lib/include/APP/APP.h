/************************************************************
** 文件名：APP.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-10
** 修改人：无
** 日  期：无
** 描  述：APP头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _GLOBAL_APP_H_INCLUDED_
#define _GLOBAL_APP_H_INCLUDED_

//#define _APP_DATA_RECORD_
//#define _APP_SERVICE_MONITOR_
//#define _APP_FAULT_TOLERANT_

//容错
#ifdef _APP_FAULT_TOLERANT_
#include "APP/FTInterface.h"
#endif

//数据记录
#ifdef _APP_DATA_RECORD_
#include "APP/Interface_Record.h"
#endif

//监控服务
#ifdef _APP_SERVICE_MONITOR_
#include "APP/Interface_Monitor.h"
#endif

#endif
