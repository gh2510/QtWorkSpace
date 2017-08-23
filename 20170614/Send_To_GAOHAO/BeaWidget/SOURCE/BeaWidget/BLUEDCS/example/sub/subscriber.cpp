/**********************************************************
*****************订阅端程序subscriber.cpp ******************
***********************************************************/
#include "subscriber.h"

int counts = 0;
//重载数据接收回调函数
_RETURNCODE_T HelloListener::On_Data_Available(DataReader* dataReader)
{
	_RETURNCODE_T ret = RETURNCODE_OK;

	//安全的类型转换
	myDataDataReader* myDataReader = NULL;
	myDataReader = myDataDataReader::Narrow(dataReader);

	if (myDataReader == NULL) //出错处理
	{
		cout << "Narrow failed at On_Data_Available of HelloListener" << endl;
		return -1;
	}

	//获取用户数据
	myData data;
	ret = myDataReader->Read_Next_Sample(data);

	if (ret != RETURNCODE_OK) //出错处理
	{
		return -1;
	}

	counts++;

	cout<<"Received "<< data.x<<" "<<data.y<<" "<<data.color<<" times = "<<counts<<endl; //显示接收到的数据

	return RETURNCODE_OK;
}

_RETURNCODE_T HelloListener2::On_Data_Available(DataReader* dataReader)
{
	_RETURNCODE_T ret = RETURNCODE_OK;

	//安全的类型转换
	myDataDataReader* myDataReader = NULL;
	myDataReader = myDataDataReader::Narrow(dataReader);

	if (myDataReader == NULL) //出错处理
	{
		cout << "Narrow failed at On_Data_Available of HelloListener" << endl;
		return -1;
	}

	//获取用户数据
	myData data;
	ret = myDataReader->Read_Next_Sample(data);

	if (ret != RETURNCODE_OK) //出错处理
	{
		return -1;
	}

	cout<<"Received Hello listener "<< data.x<<" "<<data.y<<" "<<data.color<<endl; //显示接收到的数据

	return RETURNCODE_OK;
}

//程序主函数
int main()
{
	_RETURNCODE_T ret;
	DataReader *dataReader = NULL;
	DataReader *dataReader2 = NULL;

	//将接收端组件加入数据域
	ret = DomainInit(domainId,compName);

	if (ret != RETURNCODE_OK) //出错处理
	{
		cout<<"Domain:"<<domainId<<" Init failed"<<endl;
		return 0;
	}

	//初始化QoS策略，使用尽力而为的传输
	_DATA_READER_QOS *qos = new _DATA_READER_QOS();
	qos->Reliability.Kind = BEST_EFFORT;

	//创建订阅者并绑定回调函数
	HelloListener *listener = NULL;
	//HelloListener2 *listener2 = NULL;

	int counTopic = 0;
//	while(1)
//	{
//		if (counTopic == 1)
//		{
//			listener = new HelloListener(0);
//			dataReader = CreateDataReader(compName, domainId, topicName2, "myData", listener, qos);
//			counTopic--;
//		}
//		else
//		{
//			listener = new HelloListener(0);
//			dataReader = CreateDataReader(compName, domainId, topicName, "myData", listener, qos);
//			counTopic++;
//		}
//
//		if (dataReader == NULL) //出错处理
//		{
//			cout<<"Create Data Reader failed"<<endl;
//			DomainRelease(domainId);
//			return 0;
//		}
//
//		//cout<<"Press any button to exit..."<<endl;
//	/*while(1)
//	{*/
//		sleep(2);
//		ret = DeleteDataReader(dataReader);
//		if (ret == RETURNCODE_DELETEDATAREADER_OK)
//		{
//			cout<<"Delete DataReader OK"<<endl;
//			dataReader = NULL;
//			sleep(2);
//		}
//		else
//		{
//			cout<<"Delete DataReader error"<<endl;
//			break;
//		}
//	}

	listener = new HelloListener(0);
	dataReader = CreateDataReader(compName, domainId, topicName, "myData", listener, qos);

	//listener2 = new HelloListener2(0);
	//dataReader2 = CreateDataReader(compName, domainId, topicName2, "myData", listener2, qos);

	if (dataReader == NULL)
		//|| dataReader2 == NULL) //出错处理
	{
		cout<<"Create Data Reader failed"<<endl;
		DomainRelease(domainId);
		return 0;
	}

		//cout<<"Press any button to exit..."<<endl;
	while(1)
	{
		sleep(200);
//		ret = DeleteDataReader(dataReader);
//		if (ret == RETURNCODE_DELETEDATAREADER_OK)
//		{
//			cout<<"Delete DataReader OK"<<endl;
//			dataReader = NULL;
//			sleep(2);
//		}
//		else
//		{
//			cout<<"Delete DataReader error"<<endl;
//			break;
//		}
	}

//	int a;
//	cin >> a;

	//订阅者不再进行数据订阅，安全退出
	DeleteDataReader(dataReader);

	//安全退出数据域
	DomainRelease(domainId);


	return 0;
}
