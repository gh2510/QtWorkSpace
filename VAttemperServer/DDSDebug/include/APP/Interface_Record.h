/************************************************************
** �ļ�����Interface_Record.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Interface_Recordͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _INTERFACERECORD_H
#define  _INTERFACERECORD_H

#include "Interface.h"

/**
* @ ������¼����
*/
void ServStartRecordServer();    //Interface_Record.h

/**
* @ �رռ�¼����
*/
void ServReleaseRecordServer();   //Interface_Record.h

/**
* @ ��ռ�¼�ı�
*/
_RETURNCODE_T ServRecordEmptyTXT();   //Interface_Record.h

#endif

