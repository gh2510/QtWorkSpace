/************************************************************
** 文件名：Interface_Record.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：无
** 日  期：无
** 描  述：Interface_Record头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _INTERFACERECORD_H
#define  _INTERFACERECORD_H

#include "Interface.h"

/**
* @ 开启记录服务
*/
void ServStartRecordServer();    //Interface_Record.h

/**
* @ 关闭记录服务
*/
void ServReleaseRecordServer();   //Interface_Record.h

/**
* @ 清空记录文本
*/
_RETURNCODE_T ServRecordEmptyTXT();   //Interface_Record.h

#endif

