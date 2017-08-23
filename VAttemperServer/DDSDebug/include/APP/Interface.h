/************************************************************
** �ļ�����Interface.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Interfaceͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _INTERFACE_H
#define  _INTERFACE_H

#ifdef VXWORKS
#include "inetLib.h"
#else
#pragma  comment(lib, "Ws2_32.lib")
#include <Windows.h>
#endif

#include "mr/MRBasicTypes.h"
#include "mr/MRReturnCode.h"
#include "mr/MonitorRecordAgent.h"
#include "mr/QueryProcessor.h"
#include "mr/InfoProcessor.h"

#include <iostream>
using std::cout;
using std::endl;



/************************************************************
** ��������IpCharToInt
** ��  �룺pIP
**         pIP--char���͵�ip��ַ
** ��  ����ulNetNumber--ת���������
** �����������������������ڽ��û������char���͵�ip��ַת����long int��
** ȫ�ֱ�������
** ����ģ�飺��
** ��  �ߣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-26
** �޸��ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-08-26
** ��  ����Version 0.1
*************************************************************/
#ifdef VXWORKS  
inline unsigned long  IpCharToInt(char *pIP)
{
	struct in_addr InetAddress;
	if(inet_aton(pIP,&InetAddress) == OK)	
    {
		return htonl(InetAddress.s_addr);
	}
	return 0;
}
#else
inline unsigned long  IpCharToInt(char *pIP)                //Interface.h
{
	unsigned long ulNetNumber=inet_addr (pIP); 
	return htonl(ulNetNumber);
}
#endif



#endif
