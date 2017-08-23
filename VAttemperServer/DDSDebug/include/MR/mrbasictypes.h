/************************************************************
** 文件名：mrbasictypes.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-08-26
** 修改人：杨猛<635584332@qq.com>
** 日  期：2011-10-05
** 描  述：mrbasictypes头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#include "dds/Cdr.h"
#include "BasicTypes.h"
#include "MRReturnCode.h"

#include<map>
#include<list>
#include<string>

using std::map;
using std::string;
using std::list;

#ifndef MRBasicTypes_hh
#define MRBasicTypes_hh
const unsigned int MAXUNKNOWNSECOND = 10;

const unsigned int TYPENAME_LENG = 50;
const unsigned int RECORDCONTENT_LENG = 500;
const unsigned int COMPNAME_LENG = 50;
const unsigned int TOPICNAME_LENG = 50;
const unsigned int HOSTNAME_LENG = 50;
const unsigned int TYPECODE_LENG = 1024;


#ifndef timestamp_t_defined
#define timestamp_t_defined

struct _TIMESTAMP_T
{
	_TIMESTAMP_T(){}

	_TIMESTAMP_T(const _TIMESTAMP_T  &IDL_s)
	{
		lSecond = IDL_s.lSecond;
		ulNanosec = IDL_s.ulNanosec;
	}

	~_TIMESTAMP_T(){}

	_TIMESTAMP_T& operator= (const _TIMESTAMP_T &IDL_s)
	{
		if (this == &IDL_s) return *this;
		lSecond = IDL_s.lSecond;
		ulNanosec = IDL_s.ulNanosec;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutLong(lSecond);
		cdr->PutULong(ulNanosec);
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetLong(lSecond);
		cdr->GetULong(ulNanosec);
	}

	long lSecond;
	unsigned long ulNanosec;

};

#endif

//_NODE_INFO
/*struct _NODE_INFO {
//主机IP地址
unsigned long ulIpAddress;
//主机名
char* pHostName;
//CPU占用率
float fCpuOccupPercentage;
//内存占用率
float fMemOccupPercentage;
//时间戳
_TIMESTAMP_T Timestamp;
};*/

#ifndef NodeInfo_defined
#define NodeInfo_defined

struct _NODE_INFO 
{
	_NODE_INFO(){pHostName = new char[HOSTNAME_LENG];
}

	_NODE_INFO(const _NODE_INFO  &IDL_s)
	{
		pHostName = new char[HOSTNAME_LENG];
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostName, HOSTNAME_LENG, IDL_s.pHostName);
		fCpuOccupPercentage = IDL_s.fCpuOccupPercentage;
		fMemOccupPercentage = IDL_s.fMemOccupPercentage;
		Timestamp = IDL_s.Timestamp;
	}

	~_NODE_INFO()
	{
#ifdef VXWORKS
		cout<<"before delete........"<<endl;
		if (pHostName!=NULL)
		{
			delete[] pHostName;
			pHostName = NULL;
		}
		cout<<"after delete........"<<endl;
#else
	  delete[] pHostName;
#endif
	}

	_NODE_INFO& operator= (const _NODE_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostName, HOSTNAME_LENG, IDL_s.pHostName);
		fCpuOccupPercentage = IDL_s.fCpuOccupPercentage;
		fMemOccupPercentage = IDL_s.fMemOccupPercentage;
		Timestamp = IDL_s.Timestamp;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutULong(ulIpAddress);
		cdr->PutString(pHostName);
		cdr->PutFloat(fCpuOccupPercentage);
		cdr->PutFloat(fMemOccupPercentage);
		Timestamp.Marshal(cdr);
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetULong(ulIpAddress);
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pHostName,HOSTNAME_LENG,IDL_str);
			//pHostName = IDL_str;
		}
		cdr->GetFloat(fCpuOccupPercentage);
		cdr->GetFloat(fMemOccupPercentage);
		Timestamp.UnMarshal(cdr);
	}

	unsigned long ulIpAddress;
	char* pHostName;
	float fCpuOccupPercentage;
	float fMemOccupPercentage;
	_TIMESTAMP_T Timestamp;

};

#endif

//组件状态
/*enum _COMP_STATUS { COMPALIVE , COMPINDETERMINATE , COMPDEAD , IDL_ENUM_CompStatus = 99999 };
//_COMP_INFO
struct _COMP_INFO {
//主机IP地址
unsigned long ulIpAddress;
//主机名
char* pHostname;
//应用组件名称
char* pCompName;
//主任务ID号
unsigned long ulTaskId;
//主任务优先级
unsigned long ulPriority;
//应用组件状态
_COMP_STATUS CompStatus;
//时间戳
_TIMESTAMP_T Timestamp;
};*/


#ifndef CompInfo_defined
#define CompInfo_defined

enum _COMP_STATUS { COMPALIVE, COMPINDETERMINATE, COMPDEAD, IDL_ENUM_CompStatus = 99999 };

struct _COMP_INFO 
{
	_COMP_INFO()
	{
		pHostname = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG];
	}

	_COMP_INFO(const _COMP_INFO  &IDL_s)
	{
		pHostname = new char[HOSTNAME_LENG];
		pCompName = new char[COMPNAME_LENG];
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostname, HOSTNAME_LENG,IDL_s.pHostname);
		strcpy_s(pCompName, COMPNAME_LENG,IDL_s.pCompName);
		ulTaskId = IDL_s.ulTaskId;
		ulPriority = IDL_s.ulPriority;
		CompStatus = IDL_s.CompStatus;
		Timestamp = IDL_s.Timestamp;
		ulCpuPrecentage = IDL_s.ulCpuPrecentage;
		ulPhysicalMemoryUsage = IDL_s.ulPhysicalMemoryUsage;
		ulVirtualMemoryUsage = IDL_s.ulVirtualMemoryUsage;
	}

	~_COMP_INFO()
	{
 #ifdef VXWORKS
		delete[] pCompName; 
		delete[] pHostname;
 #else
		delete[] pCompName; 
		delete[] pHostname;
#endif
	}

	_COMP_INFO& operator= (const _COMP_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostname, HOSTNAME_LENG,IDL_s.pHostname);
		strcpy_s(pCompName, COMPNAME_LENG,IDL_s.pCompName);
		ulTaskId = IDL_s.ulTaskId;
		ulPriority = IDL_s.ulPriority;
		CompStatus = IDL_s.CompStatus;
		Timestamp = IDL_s.Timestamp;
		ulCpuPrecentage = IDL_s.ulCpuPrecentage;
		ulPhysicalMemoryUsage = IDL_s.ulPhysicalMemoryUsage;
		ulVirtualMemoryUsage = IDL_s.ulVirtualMemoryUsage;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutULong(ulIpAddress);
		cdr->PutString(pHostname);
		cdr->PutString(pCompName);
		cdr->PutULong(ulTaskId);
		cdr->PutULong(ulPriority);
		cdr->PutULong(CompStatus);
		cdr->PutULong(ulCpuPrecentage);
		cdr->PutULong(ulPhysicalMemoryUsage);
		cdr->PutULong(ulVirtualMemoryUsage);
		Timestamp.Marshal(cdr);
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetULong(ulIpAddress);
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pHostname, HOSTNAME_LENG,IDL_str);
			//pHostname = IDL_str;
		}
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pCompName,COMPNAME_LENG,IDL_str);
			//pCompName = IDL_str;
		}
		cdr->GetULong(ulTaskId);
		cdr->GetULong(ulPriority);
		{
			unsigned long l;
			cdr->GetULong(l);
			CompStatus = (_COMP_STATUS)l;
		}
		cdr->GetULong(ulCpuPrecentage);
		cdr->GetULong(ulPhysicalMemoryUsage);
		cdr->GetULong(ulVirtualMemoryUsage);
		Timestamp.UnMarshal(cdr);
	}


	unsigned long ulIpAddress;
	char* pHostname;
	char* pCompName;
	unsigned long ulTaskId;
	unsigned long ulPriority;
	_COMP_STATUS CompStatus;
	_TIMESTAMP_T Timestamp;
	//fengjiaqi
	unsigned long ulCpuPrecentage;
	unsigned long ulPhysicalMemoryUsage;
	unsigned long ulVirtualMemoryUsage;

};

#endif

//主题状态
/*enum _TOPIC_STATUS { PUBLISHED , SUBSCRIBED , STOPPUBLISH , STOPSUBSCRIBE , IDL_ENUM_TopicStatus = 99999 };
//_TOPIC_INFO
struct _TOPIC_INFO {
//主机IP地址
unsigned long ulIpAddress;
//主机名
char* pHostname;
//应用组件名
char* pCompName;
//域ID
unsigned long ulDomainId;
//主题名
char* pName;
//类型名
char* pTypeName;
//主题状态
_TOPIC_STATUS TopicStatus;
//时间戳
_TIMESTAMP_T Timestamp;
};
*/


#ifndef TopicInfo_defined
#define TopicInfo_defined

enum _TOPIC_STATUS { PUBLISHED, SUBSCRIBED, STOPPUBLISH, STOPSUBSCRIBE, IDL_ENUM_TopicStatus = 99999 };

struct _TOPIC_INFO 
{
	_TOPIC_INFO(){
		pHostname = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG]; 
		pName = new char[TOPICNAME_LENG];
		pTypeCode = new char[TYPECODE_LENG];  //sunfei
		pTypeName = new char[TYPENAME_LENG];
	}
	~_TOPIC_INFO()
	{
		delete [] pHostname;
		delete [] pCompName;
		delete [] pName;
		delete [] pTypeName;
		delete [] pTypeCode;  //sunfei
	}

	_TOPIC_INFO(const _TOPIC_INFO  &IDL_s)
	{
		pTypeName = new char[TYPENAME_LENG];
		pHostname = new char[HOSTNAME_LENG];
		pName = new char[TOPICNAME_LENG];
		pCompName = new char[COMPNAME_LENG];
		pTypeCode = new char[TYPECODE_LENG];   //sunfei
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostname,HOSTNAME_LENG, IDL_s.pHostname);
		strcpy_s(pCompName,COMPNAME_LENG,IDL_s.pCompName);
		ulDomainId = IDL_s.ulDomainId;
		strcpy_s(pName,TOPICNAME_LENG, IDL_s.pName);
		strcpy_s(pTypeName,TYPENAME_LENG, IDL_s.pTypeName);
		TopicStatus = IDL_s.TopicStatus;
		Timestamp = IDL_s.Timestamp;
		iKind = IDL_s.iKind;
		strcpy_s(pTypeCode,TYPECODE_LENG,IDL_s.pTypeCode);  //sunfei
	}


	_TOPIC_INFO& operator= (const _TOPIC_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostname, HOSTNAME_LENG, IDL_s.pHostname);
		strcpy_s(pCompName, COMPNAME_LENG, IDL_s.pCompName);
		ulDomainId = IDL_s.ulDomainId;
		strcpy_s(pName, TOPICNAME_LENG, IDL_s.pName);
		strcpy_s(pTypeName,TYPENAME_LENG, IDL_s.pTypeName);
		TopicStatus = IDL_s.TopicStatus;
		Timestamp = IDL_s.Timestamp;
		iKind = IDL_s.iKind;
		strcpy_s(pTypeCode,TYPECODE_LENG,IDL_s.pTypeCode);   //sunfei
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutULong(ulIpAddress);
		cdr->PutString(pHostname);
		cdr->PutString(pCompName);
		cdr->PutULong(ulDomainId);
		cdr->PutString(pName);
		cdr->PutString(pTypeName);
		cdr->PutULong(TopicStatus);
		cdr->PutULong(iKind);
		cdr->PutString(pTypeCode);//sunfei
		Timestamp.Marshal(cdr);
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetULong(ulIpAddress);
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pHostname,HOSTNAME_LENG,IDL_str);
			//pHostname = IDL_str;
		}
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pCompName,COMPNAME_LENG, IDL_str);
			//pCompName = IDL_str;
		}
		cdr->GetULong(ulDomainId);
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			pName = IDL_str;
		}
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			pTypeName = IDL_str;
		}
		{
			unsigned long l;
			cdr->GetULong(l);
			TopicStatus = (_TOPIC_STATUS)l;
		}
		{
			unsigned long l;
			cdr->GetULong(l);
			iKind = l;
		}
		//sunfei
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pTypeCode,TYPENAME_LENG,IDL_str);     
		}
		Timestamp.UnMarshal(cdr);
	}


	unsigned long ulIpAddress;
	char* pHostname;
	char* pCompName;
	unsigned long ulDomainId;
	char* pName;
	char* pTypeName;
	char* pTypeCode;   //sunfei
	_TOPIC_STATUS TopicStatus;
	_TIMESTAMP_T Timestamp;
	int iKind;       //用于判断是监控还是记录 0是监控，1是记录，2是监控记录

};

#endif

//_COMP_SIMPLE_INFO
struct _COMP_SIMPLE_INFO
{
	_COMP_SIMPLE_INFO()
	{
		pHostName = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG]; 
	}
	~_COMP_SIMPLE_INFO()
	{
		delete []pHostName;
		delete []pCompName;
	}

	_COMP_SIMPLE_INFO(const _COMP_SIMPLE_INFO &IDL_s)
	{
		pHostName = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG]; 
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostName ,HOSTNAME_LENG, IDL_s.pHostName);
		strcpy_s(pCompName, COMPNAME_LENG, IDL_s.pCompName);
	}

	//主机地址
	unsigned long ulIpAddress;
	//主机名
	char* pHostName;
	//应用组件名称
	char* pCompName;
	_COMP_SIMPLE_INFO& operator= (const _COMP_SIMPLE_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ulIpAddress = IDL_s.ulIpAddress;
		strcpy_s(pHostName ,HOSTNAME_LENG, IDL_s.pHostName);
		strcpy_s(pCompName, COMPNAME_LENG, IDL_s.pCompName);
		return *this;
	}

	bool operator == (const _COMP_SIMPLE_INFO&right) const 
	{
		if(( ulIpAddress==right.ulIpAddress)&&(strcmp(pCompName,right.pCompName)==0)&&(strcmp(pHostName,right.pHostName)==0))
			return true;
		else 
			return false;
	}
	bool operator != (const _COMP_SIMPLE_INFO&right) const 
	{
		if(*this == right)
			return false;
		else
			return true;
	}

};
//CompSimpleInfoList_t
typedef list<_COMP_SIMPLE_INFO> CompSimpleInfoList_t; 

////全局状态信息

//_NODE_FIXED_INFO
struct _NODE_FIXED_INFO
{
	//主机地址
	unsigned long ulIpAddress;
	//主机名
	string strHostName;
};

//_NODE_GLOBAL_INFO
struct _NODE_GLOBAL_INFO
{
	//节点基本信息
	_NODE_INFO NodeInfo;
	//组件名列表
	list<string> CompNameList;
};

//_COMP_ID
struct _COMP_ID
{
public:
	unsigned long ulIP;
	string strCompName;


	//重载运算符 <
	bool operator < (const _COMP_ID&right) const 
	{
		if ((this->ulIP < right.ulIP) )
		{
			return true;
		}
		else if (this->ulIP > right.ulIP) 
		{
			return false;
		}
		else if (this->strCompName >= right.strCompName) 
		{
			return false;
		}
		else 
		{
			return true;
		}
	}
	bool operator == (const _COMP_ID&right) const 
	{
		if(( ulIP==right.ulIP)&&(strCompName==right.strCompName))
			return true;
		else 
			return false;
	}
	bool operator != (const _COMP_ID&right) const 
	{
		if(*this == right)
			return false;
		else
			return true;
	}

};

//_COMP_GINFO
struct _COMP_GINFO
{
	_COMP_GINFO()
	{
		pHostName = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG];
	}
	~_COMP_GINFO()
	{
		delete []pHostName;
		delete []pCompName;
	}
	_COMP_GINFO(const _COMP_GINFO  &IDL_s)
	{
		pHostName = new char[HOSTNAME_LENG]; 
		pCompName = new char[COMPNAME_LENG]; 
		strcpy_s(pCompName,COMPNAME_LENG,IDL_s.pCompName);
		strcpy_s(pHostName,HOSTNAME_LENG,IDL_s.pHostName);
		ulIpAddress = IDL_s.ulIpAddress;
		ulPriority = IDL_s.ulPriority;
		ulTaskId =IDL_s.ulTaskId;
		Timestamp = IDL_s.Timestamp;
		CompStatus = IDL_s.CompStatus;
		ulCpuPrecentage = IDL_s.ulCpuPrecentage;
		ulPhysicalMemoryUsage = IDL_s.ulPhysicalMemoryUsage;
		ulVirtualMemoryUsage = IDL_s.ulVirtualMemoryUsage;
		//fengjiaq
		//PublishedTopics = IDL_s.PublishedTopics;
		//SubscribedTopics = IDL_s.SubscribedTopics;
		list<string>::const_iterator iter = IDL_s.PublishedTopics.begin();
		while(iter != IDL_s.PublishedTopics.end())
		{
			PublishedTopics.push_back(*iter);
			iter++;
		}
		iter = IDL_s.SubscribedTopics.begin();
		while(iter != IDL_s.SubscribedTopics.end())
		{
			SubscribedTopics.push_back(*iter);
			iter++;
		}

	}


	_COMP_GINFO& operator= (const _COMP_GINFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		strcpy_s(pCompName,COMPNAME_LENG,  IDL_s.pCompName);
		strcpy_s(pHostName,HOSTNAME_LENG, IDL_s.pHostName);
		ulIpAddress = IDL_s.ulIpAddress;
		ulPriority = IDL_s.ulPriority;
		ulTaskId =IDL_s.ulTaskId;
		Timestamp = IDL_s.Timestamp;
		CompStatus = IDL_s.CompStatus;
		//PublishedTopics = IDL_s.PublishedTopics;
		//SubscribedTopics = IDL_s.SubscribedTopics;
		//fengjiaqi
		ulCpuPrecentage = IDL_s.ulCpuPrecentage;
		ulPhysicalMemoryUsage = IDL_s.ulPhysicalMemoryUsage;
		ulVirtualMemoryUsage = IDL_s.ulVirtualMemoryUsage;
		list<string>::const_iterator iter = IDL_s.PublishedTopics.begin();
		while(iter != IDL_s.PublishedTopics.end())
		{
			PublishedTopics.push_back(*iter);
			iter++;
		}
		iter = IDL_s.SubscribedTopics.begin();
		while(iter != IDL_s.SubscribedTopics.end())
		{
			SubscribedTopics.push_back(*iter);
			iter++;
		}
		return *this;

	}

	unsigned long ulIpAddress;
	char* pHostName;
	char* pCompName;
	unsigned long ulTaskId;
	unsigned long ulPriority;
	_COMP_STATUS CompStatus;
	_TIMESTAMP_T Timestamp;

	list<string> PublishedTopics;
	list<string> SubscribedTopics;

	unsigned long ulCpuPrecentage;
	unsigned long ulPhysicalMemoryUsage;
	unsigned long ulVirtualMemoryUsage;
};

//_TOPIC_ID
struct _TOPIC_ID
{	
	//topic szName
	string strTopicName;
	//domainID
	unsigned long ulDomainId;
	//重载运算符 <
	bool operator < (const _TOPIC_ID&right) const 
	{
		if ((this->ulDomainId < right.ulDomainId) )
		{
			return true;
		}
		else if (this->ulDomainId > right.ulDomainId) 
		{
			return false;
		}
		else if (this->strTopicName >= right.strTopicName)
		{
			return false;
		}
		else 
		{
			return true;
		}
	}
	bool operator == (const _TOPIC_ID&right) const 
	{
		if(( ulDomainId==right.ulDomainId)&&(strTopicName==right.strTopicName))
			return true;
		else 
			return false;
	}
	bool operator != (const _TOPIC_ID&right) const 
	{
		if(*this == right)
			return false;
		else
			return true;
	}
};
struct _TOPIC_GLOBAL_INFO
{
	_TOPIC_GLOBAL_INFO()
	{
		pName = new char[TOPICNAME_LENG];
		pTypeName = new char[TYPENAME_LENG];
		pTypeCode = new char[TYPECODE_LENG];   //by sunfei
	}
	~_TOPIC_GLOBAL_INFO()
	{
		delete[]pName;
		delete[]pTypeName;   //sunfei
		delete[]pTypeCode;
		PubStatics.clear();
		SubStatics.clear();
	}
	_TOPIC_GLOBAL_INFO(const _TOPIC_GLOBAL_INFO  &IDL_s)
	{
		pName = new char[TOPICNAME_LENG]; 
		pTypeName = new char[TYPENAME_LENG]; 
		pTypeCode = new char[TYPECODE_LENG];   //sunfei
		strcpy_s(pName, TOPICNAME_LENG, IDL_s.pName);
		strcpy_s(pTypeName, TYPENAME_LENG, IDL_s.pTypeName);   
		strcpy_s(pTypeCode, TYPECODE_LENG, IDL_s.pTypeCode);  //sunfei


		ulDomainId = IDL_s.ulDomainId;
		PublicationList = IDL_s.PublicationList;
		SubscriptionList = IDL_s.SubscriptionList;
		//fengjiaqi
		PubStatics.insert(IDL_s.PubStatics.begin(),IDL_s.PubStatics.end());
		SubStatics.insert(IDL_s.SubStatics.begin(),IDL_s.SubStatics.end());
	}


	_TOPIC_GLOBAL_INFO& operator= (const _TOPIC_GLOBAL_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		strcpy_s(pName, TOPICNAME_LENG, IDL_s.pName);
		strcpy_s(pTypeName, TYPENAME_LENG,  IDL_s.pTypeName);
		strcpy_s(pTypeCode, TYPECODE_LENG, IDL_s.pTypeCode);  //sunfei
		ulDomainId = IDL_s.ulDomainId;
		PublicationList = IDL_s.PublicationList;
		SubscriptionList = IDL_s.SubscriptionList;
		//fengjiaqi
		PubStatics.insert(IDL_s.PubStatics.begin(),IDL_s.PubStatics.end());
		SubStatics.insert(IDL_s.SubStatics.begin(),IDL_s.SubStatics.end());
		return *this;

	}
	//主题名
	char* pName;
	//主题类型
	char* pTypeName;	
	//域ID
	unsigned long ulDomainId;
	//发布者信息列表
	CompSimpleInfoList_t PublicationList;
	//订阅者信息列表
	CompSimpleInfoList_t SubscriptionList;

	//Sunfei
	//类型信息
	char* pTypeCode;

	//fengjiaqi
	//用于统计这个主题的发布组件对应的统计信息
	map<_COMP_ID,long> PubStatics;
	//用于统计这个主题的订阅组件对应的统计信息
	map<_COMP_ID,long> SubStatics;
};

typedef _NODE_GLOBAL_INFO _NODE_REALTIME_INFO;
typedef map<unsigned long,_NODE_GLOBAL_INFO> _NODE_GINFO_MAP_T;
typedef map<_COMP_ID,_COMP_GINFO> _COMP_GINFO_MAP_T;
typedef map<_TOPIC_ID,_TOPIC_GLOBAL_INFO> _TOPIC_GLOBAL_INFO_MAP_T;

class CMonitorNodeFixDlg;
class CMonitorNodeRealtimeDlg;
class CMonitorComDlg; 
class CMonitorStreamDlg;


typedef _RETURNCODE_T (*HandleNodeFixedInfoFp)(CMonitorNodeFixDlg *nodeFDlg, _NODE_FIXED_INFO* nodeFixedData);
typedef _RETURNCODE_T (*HandleNodeRealtimeInfoFp)(CMonitorNodeRealtimeDlg *nodeFDlg, _NODE_REALTIME_INFO * nodeRealtimeData);
typedef _RETURNCODE_T (*HandleCompInfoFp)(CMonitorNodeRealtimeDlg *compDlg,_COMP_GINFO  *compData);
typedef _RETURNCODE_T (*HandleDataStreamInfoFp)(CMonitorStreamDlg *dataStreamDlg,_TOPIC_GLOBAL_INFO * topicGData);
class QueryRequest;
typedef list<QueryRequest *> _QUERY_REQUEST_LIST_T;

/////////////////////////////////////////////////////////////////////数据记录
//序列号结构
/*struct _SEQUENCE_NUM {
long high;
unsigned long low;
};*/
#ifndef SequenceNum_defined
#define SequenceNum_defined

struct _SEQUENCE_NUM 
{
	_SEQUENCE_NUM(){}

	_SEQUENCE_NUM(const _SEQUENCE_NUM  &IDL_s)
	{
		lHigh = IDL_s.lHigh;
		ulLow = IDL_s.ulLow;
	}

	~_SEQUENCE_NUM(){}

	_SEQUENCE_NUM& operator= (const _SEQUENCE_NUM &IDL_s)
	{
		if (this == &IDL_s) return *this;
		lHigh = IDL_s.lHigh;
		ulLow = IDL_s.ulLow;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutLong(lHigh);
		cdr->PutULong(ulLow);
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetLong(lHigh);
		cdr->GetULong(ulLow);
	}

	long lHigh;
	unsigned long ulLow;

};

#endif

//动作类型
/*enum _ACTION_KIND { PUBLISH, SUBSCRIBE, PUBLISHSTOP, SUBSCRIBESTOP, SEND, RECEIVE, IDL_ENUM_ActionKind = 99999 };
//数据记录结构
struct _RECORD_INFO{
//动作类型
_ACTION_KIND ActionKind;
//组件名
char* pCompName;
//域ID
unsigned long ulDomainId;
//主机IP地址
unsigned long ulIpAddress;
//时间戳
_TIMESTAMP_T Timestamp;
//主题名
char* pTopicName;
//序列号
_SEQUENCE_NUM Seqnum;
};*/

enum _ACTION_KIND { PUBLISH, SUBSCRIBE, PUBLISHSTOP, SUBSCRIBESTOP, SEND, RECEIVE, IDL_ENUM_ActionKind = 99999 };

#ifndef RecordInfo_defined
#define RecordInfo_defined

struct _RECORD_INFO 
{
	_RECORD_INFO()
	{
		pCompName=new char[COMPNAME_LENG ];
		pTopicName=new char[TOPICNAME_LENG ];
	}

	_RECORD_INFO(const _RECORD_INFO  &IDL_s)
	{
		pTopicName = new char[TOPICNAME_LENG];
		pCompName = new char[COMPNAME_LENG];
		ActionKind = IDL_s.ActionKind;
		strcpy_s(pCompName, COMPNAME_LENG, IDL_s.pCompName);
		ulDomainId = IDL_s.ulDomainId;
		ulIpAddress = IDL_s.ulIpAddress;
		Timestamp = IDL_s.Timestamp;
		strcpy_s(pTopicName , TOPICNAME_LENG, IDL_s.pTopicName);
		Seqnum = IDL_s.Seqnum;
	}

	~_RECORD_INFO()
	{
		delete [] pTopicName;
		delete [] pCompName;

	}

	_RECORD_INFO& operator= (const _RECORD_INFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ActionKind = IDL_s.ActionKind;
		strcpy_s(pCompName ,COMPNAME_LENG, IDL_s.pCompName);
		ulDomainId = IDL_s.ulDomainId;
		ulIpAddress = IDL_s.ulIpAddress;
		Timestamp = IDL_s.Timestamp;
		strcpy_s(pTopicName, TOPICNAME_LENG,IDL_s.pTopicName);
		Seqnum = IDL_s.Seqnum;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		cdr->PutULong(ActionKind);
		cdr->PutString(pCompName);
		cdr->PutULong(ulDomainId);
		cdr->PutULong(ulIpAddress);
		Timestamp.Marshal(cdr);
		cdr->PutString(pTopicName);
		Seqnum.Marshal(cdr);
	}

	void UnMarshal(CDR *cdr)
	{
		{
			unsigned long l;
			cdr->GetULong(l);
			ActionKind = (_ACTION_KIND)l;
		}
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			strcpy_s(pCompName, COMPNAME_LENG, IDL_str);
			//pCompName = IDL_str;
		}
		cdr->GetULong(ulDomainId);
		cdr->GetULong(ulIpAddress);
		Timestamp.UnMarshal(cdr);
		{
			char *IDL_str;
			cdr->GetString(IDL_str);
			pTopicName = IDL_str;
		}
		Seqnum.UnMarshal(cdr);
	}

	_ACTION_KIND ActionKind;
	char* pCompName;
	unsigned long ulDomainId;
	unsigned long ulIpAddress;
	_TIMESTAMP_T Timestamp;
	char* pTopicName;
	_SEQUENCE_NUM Seqnum;

};

#endif

//数据记录链表，用于临时存储数据记录
typedef list<_RECORD_INFO> _RECORD_INFO_LIST;

//数据状态信息列表，用于临时存储数据记录
/*typedef sequence<_RECORD_INFO> _RECORD_INFO_SEQ;*/

#ifndef _IDL_SEQUENCE_RecordInfo_defined
#define _IDL_SEQUENCE_RecordInfo_defined

class _IDL_SEQUENCE_RECORDINFO 
{
	unsigned long ulMaximum;
	unsigned long ulLength;
	unsigned long ulRelease;
	_RECORD_INFO* pBuffer;

public:
	_IDL_SEQUENCE_RECORDINFO()
	{
		ulRelease = 1;
		ulLength = 0;
		ulMaximum =0;
		pBuffer = NULL;
	}

	_IDL_SEQUENCE_RECORDINFO(const _IDL_SEQUENCE_RECORDINFO &IDL_s)
	{
		ulLength = IDL_s.ulLength;
		ulRelease = 1;
		unsigned long IDL_maximum = ulMaximum = IDL_s.ulMaximum;
		if (IDL_maximum) 
		{
			pBuffer = Allocbuf(IDL_maximum);
			for(unsigned long IDL_i=0; IDL_i<ulLength; IDL_i++)
			{
				pBuffer[IDL_i] = IDL_s.pBuffer[IDL_i];
			}
		} else
			pBuffer = NULL;
	}

	_IDL_SEQUENCE_RECORDINFO(unsigned long IDL_max)
	{
		if(IDL_max)
		{
			pBuffer = Allocbuf(IDL_max);
		} else
			pBuffer = NULL;
		ulLength = 0;
		ulRelease = 1;
		ulMaximum = IDL_max;
	}

	_IDL_SEQUENCE_RECORDINFO(unsigned long max, unsigned long length, _RECORD_INFO* data, unsigned char release = 0)
	{
		ulRelease =release;
		ulLength = length;
		pBuffer = data;
		ulMaximum = max;
	}

	~_IDL_SEQUENCE_RECORDINFO()
	{
		if (pBuffer && ulRelease)
		{
			Freebuf(pBuffer);
		}
	}

	_IDL_SEQUENCE_RECORDINFO& operator= (const _IDL_SEQUENCE_RECORDINFO &IDL_s)
	{
		if (this == &IDL_s) return *this;
		if(!ulRelease || (IDL_s.ulMaximum > ulMaximum))
		{
			if(pBuffer && ulRelease)
			{
				Freebuf(pBuffer);
			}
			pBuffer = Allocbuf(IDL_s.ulMaximum);
			ulMaximum = IDL_s.ulMaximum;
			ulRelease = 1;
		}
		ulLength = IDL_s.ulLength;
		for (unsigned long IDL_j=0; IDL_j<ulLength; IDL_j++)
		{
			pBuffer[IDL_j] = IDL_s.pBuffer[IDL_j];
		}
		return *this;
	}

	_RECORD_INFO& operator [](unsigned long IDL_i)
	{
		if(IDL_i >= ulLength) throw RETURNCODE_NO_MEMORY;
		return pBuffer[IDL_i];
	}

	_RECORD_INFO& operator [](unsigned long IDL_i) const
	{
		if(IDL_i >= ulLength) throw RETURNCODE_NO_MEMORY;
		return pBuffer[IDL_i];
	}

	static _RECORD_INFO* Allocbuf(unsigned long nelems)
	{
		return (new _RECORD_INFO[nelems]);
	}

	static void Freebuf(_RECORD_INFO* data)
	{
		if(data) delete [] data;
	}

	unsigned long Maximum() const {return ulMaximum; }

	unsigned long Length() const {return ulLength; }

	void Length(unsigned long len)
	{
		if(len > ulMaximum)
		{
			_IDL_SEQUENCE_RECORDINFO tempSeq(*this);
			if(pBuffer && ulRelease)
			{
				Freebuf(pBuffer);
			}
			ulRelease = 1;
			ulLength = len;
			ulMaximum = len;
			pBuffer = Allocbuf(len);
			for(unsigned long IDL_i=0; IDL_i<tempSeq.ulLength; IDL_i++)
			{
				pBuffer[IDL_i] = tempSeq.pBuffer[IDL_i];
			}
		} else if(len<ulLength)
		{
			ulLength = len;
		} else 
		{
			ulLength = len;
		}
	}

	void Marshal(CDR *cdr) const 
	{
		cdr->PutULong(ulLength);
		for (unsigned long IDL_j=0; IDL_j<ulLength; IDL_j++)
		{
			pBuffer[IDL_j].Marshal(cdr);
		}
	}

	void UnMarshal(CDR *cdr)
	{
		cdr->GetULong(ulLength);
		if(!ulRelease || (ulLength > ulMaximum))
		{
			if(pBuffer && ulRelease)
			{
				Freebuf(pBuffer);
			}
			ulMaximum = ulLength;
			pBuffer = Allocbuf(ulMaximum);
			ulRelease = 1;
		}
		for (unsigned long IDL_j=0; IDL_j<ulLength; IDL_j++)
		{
			pBuffer[IDL_j].UnMarshal(cdr);
		}
	}
};

#endif

//数据状态信息列表及记录数量，用于发送记录
/*struct _RECORD_INFO_SENDLIST {
//数据状态信息列表
_RECORD_INFO_SEQ RecordInfoSeq;
//数据状态信息个数
unsigned long ulNumbs;
};*/


typedef _IDL_SEQUENCE_RECORDINFO _RECORD_INFO_SEQ;
typedef const _IDL_SEQUENCE_RECORDINFO _RECORD_INFO_SEQ_IDL_CONST;

#ifndef RecordInfoSendList_defined
#define RecordInfoSendList_defined

struct _RECORD_INFO_SENDLIST 
{
	_RECORD_INFO_SENDLIST(){}

	_RECORD_INFO_SENDLIST(const _RECORD_INFO_SENDLIST  &IDL_s)
	{
		RecordInfoSeq = IDL_s.RecordInfoSeq;
		ulNumbs = IDL_s.ulNumbs;
		iMRKind = IDL_s.iMRKind;
	}

	~_RECORD_INFO_SENDLIST(){}

	_RECORD_INFO_SENDLIST& operator= (const _RECORD_INFO_SENDLIST &IDL_s)
	{
		if (this == &IDL_s) return *this;
		RecordInfoSeq = IDL_s.RecordInfoSeq;
		ulNumbs = IDL_s.ulNumbs;
		iMRKind = IDL_s.iMRKind;
		return *this;
	}

	void Marshal(CDR *cdr) const
	{
		RecordInfoSeq.Marshal(cdr);
		cdr->PutULong(ulNumbs);
		cdr->PutULong(iMRKind);
	}

	void UnMarshal(CDR *cdr)
	{
		RecordInfoSeq.UnMarshal(cdr);
		cdr->GetULong(ulNumbs);
		{
			unsigned long l;
			cdr->GetULong(l);
			iMRKind = l;
		}
	}

	_RECORD_INFO_SEQ RecordInfoSeq;
	unsigned long ulNumbs;
	int iMRKind;                             //用于判断开启了监控还是记录还是都开起了

};

#endif

struct _RECORD_CONTENT
{
	_RECORD_CONTENT()
	{
		pTopicName = new char[TOPICNAME_LENG];
		pContent = new char[RECORDCONTENT_LENG];
	}
	~_RECORD_CONTENT()
	{
		delete [] pTopicName;
		delete [] pContent;
	}
	_RECORD_CONTENT(const _RECORD_CONTENT  &IDL_s)
	{
		pTopicName = new char[TOPICNAME_LENG];
		pContent = new char[RECORDCONTENT_LENG];
		strcpy_s(pContent,RECORDCONTENT_LENG, IDL_s.pContent);
		strcpy_s(pTopicName, TOPICNAME_LENG,IDL_s.pTopicName);
		//ulIpAddress = IDL_s.ulIpAddress;

	}


	_RECORD_CONTENT& operator= (const _RECORD_CONTENT &IDL_s)
	{
		if(this == &IDL_s)return *this;
		pTopicName = new char[TOPICNAME_LENG];
		pContent = new char[RECORDCONTENT_LENG];
		strcpy_s(pContent, RECORDCONTENT_LENG,IDL_s.pContent);
		strcpy_s(pTopicName,TOPICNAME_LENG, IDL_s.pTopicName);
		//ulIpAddress = IDL_s.ulIpAddress;
		return *this;

	}


	//主题名
	char* pTopicName;
	//主机IP地址
	//unsigned long ulIpAddress;
	//主题内容
	char* pContent;
};

typedef list<_RECORD_CONTENT> _RECORD_CONTENT_LIST;

/////////////////////////////////////////////////////////////////////////////界面结构体
struct _DATE_T
{
	int iTm_sec;     /* 秒 – 取值区间为[0,59] */
	int iTm_min;     /* 分 - 取值区间为[0,59] */
	int iTm_hour;    /* 时 - 取值区间为[0,23] */
	int iTm_mday;    /* 一个月中的日期 - 取值区间为[1,31] */
	int iTm_mon;     /* 月份（从一月开始，0代表一月） - 取值区间为[0,11] */
	int iTm_year;    /* 年份 */
};


const int LISTENQ = 10;
const int MSG_SIZE = 6000;

//系统发送和接收数据大小
#define BUF_TIMES	10			//设置系统的发送和接收数据缓冲区为默认的10倍，在xp32下为 8k*10
#define BUF_SIZE	(1024 * 50)	//缓冲区的大小
const unsigned int TOPICNAME_N_LENG = 1024;
const unsigned int COMPNAME_N_LENG = 1024;
const unsigned int IP_LENG = 20;
const unsigned int COMPSIMPLEINFOLIST_LENG = 25;
const unsigned int FILENAME_LENG = 50;
const unsigned int SEQSIZE = 200;
enum _CLIENT_REQUEST_ITEM{
	QUERYNODEFIXEDINFO,
	QUERYNODERTINFO,
	QUERYCOMPINFO,
	QUERYTOPICINFO,
	OPENRECORD,
	CLOSERECORD,
	WIPERECORD,
	TRANSMITRECORD,
	REQFILESIZE,
	REQFILENAMES, //请求文件长度
	REQTOPICLIST,
	REQNODELIST
	//REQNON		//没有请求
};

typedef struct _HDR
{
	char	chType;	//类型		
	unsigned short	usLen;	//数据包长度(头+包体)
	unsigned long 	ulFpos;	//文件开始位置
	unsigned long 	ulFlen;	//文件长度
}hdr, *phdr;

//数据包类型
#define ROOT		'R'			//根目录
#define DIRC		'D'			//文件目录
#define FSIZ		'S'			//文件大小
#define FDAT		'F'			//文件数据
#define HEADLEN		(sizeof(hdr))//包头的长度

enum _REQUEST_TYPE{
	REQROOT,	//请求根目录
	REQDIRC,	//请求子目录
	REQFSIZ,	//请求文件大小
	REQFDAT,	//请求下载文件
	REQNON		//没有请求
};
struct _CLIENT_REQUEST
{
	_CLIENT_REQUEST_ITEM RequestItem;
	char szIP[IP_LENG];
	char szCompName[COMPNAME_LENG];
	char szTopicName[TOPICNAME_LENG];
	unsigned long ulDomainId;
	int iQueryPeriodinSecond;   
	unsigned long ulFpos;  //文件开始的位置
	unsigned long ulFlen;  //文件长度
	char szFileName[FILENAME_LENG];
};

//_COMP_GINFO
struct _COMP_GINFO_TX
{
	//应用组件所属的节点ip
	unsigned long ulIPAddress;
	//应用组件所属的主机名
	char szHostName[HOSTNAME_LENG];
	//应用组件名
	char szCompName[COMPNAME_LENG];
	//应用组件主任务id
	unsigned long ulTaskId;
	//主任务优先级
	unsigned long ulPriority;
	//应用组件的状态
	_COMP_STATUS CompStatus;
	//时间戳
	_TIMESTAMP_T Timestamp;
	//组件CPU利用率
	unsigned long ulCpuPercentage;
	//组件物理内存使用情况
	unsigned long ulPhysicalMemUsage;
	//组件虚拟内存使用情况
	unsigned long ulVirtualMemUsage;
	//应用组件发布的主题名列表
	char szPublishedTopics[TOPICNAME_N_LENG];
	//应用组件订阅的主题名列表
	char szSubscribedTopics[TOPICNAME_N_LENG];
	//此应用组件信息是否可用
	bool bValid;
};

//_NODE_FIXED_INFO
struct _NODE_FIXED_INFO_TX
{
	//主机地址
	unsigned long ulIpAddress;
	//主机名
	char szHostName[HOSTNAME_LENG];
	//此节点固定状态信息是否可用
	bool bValid;
};

struct _NODE_INFO_TX 
{
	//节点ip
	unsigned long ulIPAddress;
	//节点名称
	char szHostName[HOSTNAME_LENG];
	//CPU利用率
	float fCpuOccupPercentage;
	//内存利用率
	float fMemOccupPercentage;
	//时间戳
	_TIMESTAMP_T Timestamp;
};
//_NODE_GLOBAL_INFO
struct _NODE_GINFO_TX
{
	//单个节点的节点信息
	_NODE_INFO_TX NodeInfo;
	//组件名列表
	char szCompNameList[COMPNAME_N_LENG];	
	//此节点信息是否可用
	bool bValid;
};



//_COMP_SIMPLE_INFO
struct _COMP_SIMPLE_INFO_TX
{
	//主机地址
	unsigned long ulIPAddress;
	//主机名
	char szHostName[HOSTNAME_LENG];
	//应用组件名称
	char szCompName[COMPNAME_LENG];
	
	_COMP_SIMPLE_INFO_TX()
	{
	}
	

	_COMP_SIMPLE_INFO_TX(const _COMP_SIMPLE_INFO_TX &IDL_s)
	{
		ulIPAddress = IDL_s.ulIPAddress;
		strcpy_s(szHostName ,HOSTNAME_LENG, IDL_s.szHostName);
		strcpy_s(szCompName,COMPNAME_LENG, IDL_s.szCompName);
	}

	_COMP_SIMPLE_INFO_TX& operator= (const _COMP_SIMPLE_INFO_TX &IDL_s)
	{
		if (this == &IDL_s) return *this;
		ulIPAddress = IDL_s.ulIPAddress;
		strcpy_s(szHostName ,HOSTNAME_LENG, IDL_s.szHostName);
		strcpy_s(szCompName,COMPNAME_LENG, IDL_s.szCompName);
		return *this;
	}

};


struct _TOPIC_GINFO_TX
{

	//主题名
	char szName[TOPICNAME_LENG];
	//主题类型
	char szTypeName[TYPENAME_LENG];
	//类型信息
	char szTypeCode[TYPECODE_LENG];       //sunfei
	//域ID
	unsigned long ulDomainId;
	//发布者信息列表
	_COMP_SIMPLE_INFO_TX PublicationList[COMPSIMPLEINFOLIST_LENG];
	//发布者信息列表中发布者的数量
	unsigned long ulPubCompCount;
	//订阅者信息列表
	_COMP_SIMPLE_INFO_TX SubscriptionList[COMPSIMPLEINFOLIST_LENG];
	//订阅者信息列表中订阅者的数量
	unsigned long ulSubCompCount;
	//fengjiaqi
	//用于统计这个主题的发布组件对应的统计信息
	int pPubStatics[COMPSIMPLEINFOLIST_LENG];
	//用于统计这个主题的订阅组件对应的统计信息
	int pSubStatics[COMPSIMPLEINFOLIST_LENG];
	//此主题信息是否可用
	bool bValid;

	//fengjiaqi
	_TOPIC_GINFO_TX()
	{
	}

	_TOPIC_GINFO_TX(const _TOPIC_GINFO_TX  &IDL_s)
	{
		strcpy_s(szName,TOPICNAME_LENG, IDL_s.szName);
		strcpy_s(szTypeName, TYPENAME_LENG,IDL_s.szTypeName);
		strcpy_s(szTypeCode, TYPECODE_LENG,IDL_s.szTypeCode);   //sunfei
		ulDomainId = IDL_s.ulDomainId;
		ulPubCompCount = IDL_s.ulPubCompCount;
		//fengjiaqi
		for (unsigned int I = 0;I<ulPubCompCount;I++)
		{
			PublicationList[I] = IDL_s.PublicationList[I];
			pPubStatics[I] = IDL_s.pPubStatics[I];
		}
		ulSubCompCount = IDL_s.ulSubCompCount;
		for(unsigned int I = 0;I<ulSubCompCount;I++)
		{
			SubscriptionList[I] = IDL_s.SubscriptionList[I];
			pSubStatics[I] = IDL_s.pSubStatics[I];
		}
	}


	_TOPIC_GINFO_TX& operator= (const _TOPIC_GINFO_TX &IDL_s)
	{
		if (this == &IDL_s) return *this;
		strcpy_s(szName,TOPICNAME_LENG, IDL_s.szName);
		strcpy_s(szTypeName, TYPENAME_LENG,IDL_s.szTypeName);
		strcpy_s(szTypeCode, TYPECODE_LENG,IDL_s.szTypeCode);   //sunfei
		ulDomainId = IDL_s.ulDomainId;
		ulPubCompCount = IDL_s.ulPubCompCount;
		//fengjiaqi
		for (unsigned int I = 0;I<ulPubCompCount;I++)
		{
			PublicationList[I] = IDL_s.PublicationList[I];
			pPubStatics[I] = IDL_s.pPubStatics[I];
		}
		ulSubCompCount = IDL_s.ulSubCompCount;
		for(unsigned int I = 0;I<ulSubCompCount;I++)
		{
			SubscriptionList[I] = IDL_s.SubscriptionList[I];
			pSubStatics[I] = IDL_s.pSubStatics[I];
		}
		return *this;

	}
	~_TOPIC_GINFO_TX()
	{
	}

};

struct _TOPIC_ID_TX{
	//域ID
	unsigned long ulDomainId;
	//主题名
	char szName[TOPICNAME_LENG];
	bool bValid;
};
typedef list<_NODE_FIXED_INFO_TX> _NODE_FIXED_INFO_TX_LIST;
typedef list<_TOPIC_ID_TX> _TOPIC_ID_TX_LIST;

struct _NODE_FIXED_INFO_SEQ
{
	int iCount;
	//_NODE_FIXED_INFO_TX m_nodeFixedInfoTXSeq[SEQSIZE];
	_NODE_FIXED_INFO_TX m_nodeFixedInfoTXSeq[50];
	_NODE_FIXED_INFO_SEQ(const _NODE_FIXED_INFO_SEQ  &IDL_s)
	{
		iCount = IDL_s.iCount;
		for(int i= 0; i<IDL_s.iCount; i++)
		{
			m_nodeFixedInfoTXSeq[i] = IDL_s.m_nodeFixedInfoTXSeq[i];
		}

	}
	_NODE_FIXED_INFO_SEQ()
	{
	}


	_NODE_FIXED_INFO_SEQ& operator= (const _NODE_FIXED_INFO_SEQ &IDL_s)
	{
		if(this == &IDL_s)return *this;
		iCount = IDL_s.iCount;
		for(int i= 0; i<IDL_s.iCount; i++)
		{
			m_nodeFixedInfoTXSeq[i] = IDL_s.m_nodeFixedInfoTXSeq[i];
		}
		return *this;

	}


};

struct _TOPIC_ID_SEQ
{
	int iCount;
	//_TOPIC_ID_TX pTopicIDTXSeq[SEQSIZE];
	_TOPIC_ID_TX pTopicIDTXSeq[50];

};

#endif
