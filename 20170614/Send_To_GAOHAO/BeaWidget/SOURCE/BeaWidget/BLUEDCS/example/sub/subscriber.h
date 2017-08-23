/**********************************************************
*****************订阅端程序subscriber.h ******************
***********************************************************/
#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

#include "DDS_API.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#define compName	"DDSTest"		//应用组件名
#define domainId	11			//数据域
#define topicName	"myDataTest"	//主题名
#define topicName2	"myDataTest2"	//主题名
using namespace std;

class HelloListener : public DataReaderListener
{
public:
	HelloListener(long num)
	{
		receiveCount = num;
	}

	_RETURNCODE_T On_Data_Available(DataReader* dataReader);

	long receiveCount;

};

class HelloListener2 : public DataReaderListener
{
public:
	HelloListener2(long num)
	{
		receiveCount = num;
	}

	_RETURNCODE_T On_Data_Available(DataReader* dataReader);

	long receiveCount;

};
#endif
