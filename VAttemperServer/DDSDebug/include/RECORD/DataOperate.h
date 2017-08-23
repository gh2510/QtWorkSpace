/************************************************************
** 文件名：DataOperate.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-07-11
** 修改人：无
** 日  期：无
** 描  述：DataOperate头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#include "RECORD/sqlite3.h"
#include "MRBasicTypes.h"

//#pragma comment(lib, "F:\\DDS\\debug\\sqlite3.lib")
//#pragma comment(lib, "sqlite3.lib")

class DataOperate
{
public:

/**
* @ DataOperate构造函数
*/
	DataOperate();  //DataOperate.h

	sqlite3* pDB;  //DataOperate.h

/**
* @ 创建DRSRecord数据表
*/
	int CreateTableDR();  //DataOperate.h

/**
* @ 创建RecordContent数据表
*/
	int CreateTableRC();  //DataOperate.h

/**
* @ 创建TypeCode数据表
*/
	int CreateTableTypeCode();  //DataOperate.h

/**
* @ 向DRSRecord表中插入数据
*/
	int InsertALL(_RECORD_INFO_LIST::iterator it);  //DataOperate.h

/**
* @ 向RecordContent表中插入数据
*/
	int InsertContent(list<_RECORD_CONTENT>::iterator it,unsigned long ulSize);  //DataOperate.h

/**
* @ 向TypeCode表中插入数据
*/
	int InsertTypeCode(char * pTopicName,char * pTypeName,char * pTypeCode);  //DataOperate.h

/**
* @ 删除DRSRecord数据表中数据
*/
	int DeleteTableDR();  //DataOperate.h

/**
* @ 删除RecordContent数据表中数据
*/
	int DeleteTableRC();  //DataOperate.h

/**
* @ 删除TypeCode数据表中数据
*/
	int DeleteTableTypeCode();  //DataOperate.h

	static HANDLE hDLOCK;

};