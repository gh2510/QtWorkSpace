/************************************************************
** �ļ�����NodeInfoDRListener.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-27
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-24
** ��  ����NodeInfoDRListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _NODEINFODRLISTENER_H
#define _NODEINFODRLISTENER_H

#include "dds/DataReaderListener.h"
class InfoProcessor;
class NodeInfoDRListener:public DataReaderListener
{
private:
	//������ָ��
	InfoProcessor *m_pProcessor;
public:
	//���캯��
	NodeInfoDRListener(InfoProcessor *pProcessor);                 //NodeInfoDRListener.h
	//��������
	~NodeInfoDRListener();                        //NodeInfoDRListener.h
	//���ݵ���ʱ���������ݵĺ���
	_RETURNCODE_T  On_Data_Available(DataReader* pDataReader);             //NodeInfoDRListener.h
};

#endif
