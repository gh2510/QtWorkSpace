/************************************************************
** �ļ�����CompInfoDRListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-10-05
** ��  ����CompInfoDRListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _COMPINFODRLISTENER_H
#define _COMPINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class CompInfoDRListener:public DataReaderListener
{
private:
	//������ָ��
	InfoProcessor *m_pProcessor;
public:
	//���캯��
	CompInfoDRListener(InfoProcessor *pProcessor);   //CompInfoDRListener.h
	//��������
	~CompInfoDRListener();   //CompInfoDRListener.h
	//���ݵ���ʱ���������ݵĺ���
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);   //CompInfoDRListener.h
};

#endif

