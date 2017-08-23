/************************************************************
** 文件名：Interface.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：无
** 日  期：无
** 描  述：Interface头文件
** 版  本：Version 0.1
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
** 函数名：IpCharToInt
** 输  入：pIP
**         pIP--char类型的ip地址
** 输  出：ulNetNumber--转化后的类型
** 功能描述：辅助函数，用于将用户输入的char类型的ip地址转化成long int型
** 全局变量：无
** 调用模块：无
** 作  者：杨猛<635584332@qq.com>
** 日  期：2011-04-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 版  本：Version 0.1
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
