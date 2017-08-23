/**********************************************************
*****************发布端程序publisher.cpp*******************
***********************************************************/
#include "DDS_API.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#define compName	"DDSTest"   //组件名
#define domainId	11          //数据域
#define topicName	"myDataTest" //主题名
#define topicName2	"myDataTest2" //主题名
using namespace std;

//程序主函数
int main()
{
	_RETURNCODE_T ret;

	//将发送端组件加入数据域
	ret = DomainInit(domainId,compName);

	if (ret != RETURNCODE_OK) //出错处理
	{
		cout<<"Domain: "<<domainId <<" Init failed"<<endl;
		return 0;
	}

	//应用组件QoS设置
	_DATA_WRITER_QOS *qos = new _DATA_WRITER_QOS();
	qos->Reliability.Kind = BEST_EFFORT;

	//创建发布者
	DataWriter * dataWriter = NULL;
	DataWriter * dataWriter2 = NULL;
	dataWriter = CreateDataWriter(compName,domainId, topicName, "myData", NULL, qos);
	//dataWriter2 = CreateDataWriter(compName,domainId, topicName2, "myData", NULL, qos);
	if (dataWriter == NULL)
		//|| dataWriter2 == NULL) //出错处理
	{
		cout<<"Create Data Writer failed"<<endl;
		DomainRelease(domainId);
		return 0;
	}

	//安全的类型转换
	myDataDataWriter *myDataTypeDataWriter = NULL;
	myDataTypeDataWriter = myDataDataWriter::Narrow(dataWriter);

	//myDataDataWriter *myDataTypeDataWriter2 = NULL;
	//myDataTypeDataWriter2 = myDataDataWriter::Narrow(dataWriter2);

	if (myDataTypeDataWriter == NULL)
		//|| myDataTypeDataWriter2 == NULL) //出错处理
	{
		cout<<"myDataDataWriter Narrow failed"<<endl;
		DeleteDataWriter(dataWriter);
		DomainRelease(domainId);
		return 0;
	}

	/*_SEND_SOCKET_LIST m_RequestList;
	int* temp = (int*)&m_RequestList;
	*temp = 0x12345678;*/


	//定义用户数据
	myData data;
	data.x = 2;
	data.y = 4;
	data.color = "heheheheh";
//	data.color = new char[30];
//	data.x=100;
//	data.y=100;
//	data.color[0] = 'a';		//获取用户数据
//	data.color[1] = 'b';
//	data.color[2] = 'c';
//	data.color[3] = '\0';

	//cout<<"Please enter the point and color you want to send,such as 3 4 red"<<endl;
	while(1)
	{
		sleep(2);
		//data.x=100;
		//data.y=100;
		//data.color="red";		//获取用户数据

//		data.a += 0.1;

		//将用户输入的数据调用Write接口发送
		ret = myDataTypeDataWriter->Write(data);

		if (ret != RETURNCODE_OK) //出错处理
		{
			cout <<"myDataTypeDataWriter Write error: " << ret << endl;
		}
//		ret = myDataTypeDataWriter2->Write(data);
//
//		if (ret != RETURNCODE_OK) //出错处理
//		{
//			cout <<"myDataTypeDataWriter2 Write error: " << ret << endl;
//		}
	}

	//安全删除dataWriter
	DeleteDataWriter(dataWriter);

	//安全退出数据域
	DomainRelease(domainId);

	system("PAUSE");
	//delete data.color;

	return 0;
}
