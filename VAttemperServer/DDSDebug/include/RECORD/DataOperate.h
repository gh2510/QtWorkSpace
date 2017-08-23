/************************************************************
** �ļ�����DataOperate.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-07-11
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataOperateͷ�ļ�
** ��  ����Version 0.1
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
* @ DataOperate���캯��
*/
	DataOperate();  //DataOperate.h

	sqlite3* pDB;  //DataOperate.h

/**
* @ ����DRSRecord���ݱ�
*/
	int CreateTableDR();  //DataOperate.h

/**
* @ ����RecordContent���ݱ�
*/
	int CreateTableRC();  //DataOperate.h

/**
* @ ����TypeCode���ݱ�
*/
	int CreateTableTypeCode();  //DataOperate.h

/**
* @ ��DRSRecord���в�������
*/
	int InsertALL(_RECORD_INFO_LIST::iterator it);  //DataOperate.h

/**
* @ ��RecordContent���в�������
*/
	int InsertContent(list<_RECORD_CONTENT>::iterator it,unsigned long ulSize);  //DataOperate.h

/**
* @ ��TypeCode���в�������
*/
	int InsertTypeCode(char * pTopicName,char * pTypeName,char * pTypeCode);  //DataOperate.h

/**
* @ ɾ��DRSRecord���ݱ�������
*/
	int DeleteTableDR();  //DataOperate.h

/**
* @ ɾ��RecordContent���ݱ�������
*/
	int DeleteTableRC();  //DataOperate.h

/**
* @ ɾ��TypeCode���ݱ�������
*/
	int DeleteTableTypeCode();  //DataOperate.h

	static HANDLE hDLOCK;

};