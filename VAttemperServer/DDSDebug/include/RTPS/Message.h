/************************************************************
** 文件名：Message.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：Message头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_MESSAGE_H_INCLUDED_
#define _RTPS_MESSAGE_H_INCLUDED_

#include "BasicTypes.h"
#include <bitset>

using std::bitset;

/**
* @ brief 定义子报文元素 SubmessageElement
*/
typedef _ENTITY_ID_T _ENTITYID;
typedef _GUID_PREFIX_T _GUIDPREFIX;
typedef _VENDOR_ID_T _VENDORID;
typedef _PROTOCOL_VERSION_T _PROTOCOL_VERSION;
typedef _SEQUENCE_NUMBER_T _SEQUENCE_NUMBER;
struct _SEQUENCE_NUMBER_SET 
{
    _SEQUENCE_NUMBER_T BitmapBase;
    bitset<256> bitmap;//big data
};

struct _FRAGMENT_NUMBER_SET 
{
    _FRAGMENT_NUMBER_T BitmapBase;
    //bitset<256> bitmap;//big data
	bitset<512> bitmap;
};

typedef _TIME_T _TIME_STAMP;
struct _LOCATORLIST 
{
    unsigned long ulNumLocators;
    _LOCATOR_T *pLocator;

    _LOCATORLIST();
    _LOCATORLIST(unsigned long ulNum) 
    {
        this->ulNumLocators = ulNum;
        this->pLocator = new _LOCATOR_T[ulNum];
    }
};
typedef _COUNT_T _COUNT;
typedef char* pSerializedPayload;

/**
* @ brief 定义报文类型
*/
typedef Octet _SUBMESSAGE_KIND;
const _SUBMESSAGE_KIND PAD             = 0x01;
const _SUBMESSAGE_KIND ACKNACK         = 0x06;
const _SUBMESSAGE_KIND HEARTBEAT       = 0x07;
const _SUBMESSAGE_KIND GAP             = 0x08;
const _SUBMESSAGE_KIND INFO_TS         = 0x09;
const _SUBMESSAGE_KIND INFO_SRC        = 0x0c;
const _SUBMESSAGE_KIND INFO_REPLY_IP4  = 0x0d;
const _SUBMESSAGE_KIND INFO_DST        = 0x0e;
const _SUBMESSAGE_KIND INFO_REPLY      = 0x0f;
const _SUBMESSAGE_KIND NACK_FRAG       = 0x12;
const _SUBMESSAGE_KIND HEARTBEAT_FRAG  = 0x13;
const _SUBMESSAGE_KIND DATA            = 0x15;
const _SUBMESSAGE_KIND DATA_FRAG       = 0x16;

/**
* @ brief 定义协议
*/
typedef char _PROTOCOLID_T[4];
#define PROTOCOL_RTPS "RTPS"


/**
* @ brief 定义报文头_MESSAGE_HEADER
*/ 
struct _MESSAGE_HEADER 
{
    _PROTOCOLID_T Protocol;
    _PROTOCOL_VERSION Version;
    _VENDORID VendorId;
    _GUIDPREFIX GuidPrefix;
};

/**
* @ brief 定义子报文头 _SUBMESSAGE_HEADER
*/ 
typedef Octet _SUBMESSAGE_FLAG;
struct _SUBMESSAGE_HEADER 
{
    _SUBMESSAGE_KIND SubmessageId;
    //Flag 第一位始终为 EndiannessFlag 其他各位根据报文类型而定
    _SUBMESSAGE_FLAG Flag;
    unsigned short usSubmessageLength;
};

/**
* @ brief 定义AckNack子报文
* @       Header中Flag第二位为 FinalFlag
*/
#pragma pack(4)
struct _ACKNACK_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
    _SEQUENCE_NUMBER_SET ReaderSNState;
    _COUNT Count;
};
#pragma pack()

/**
* @ brief 定义_PARAMETER_LIST
*/
typedef short _PARAMETERID_T;
struct _PARAMETER 
{
    _PARAMETERID_T ParameterId;
    short sLength;
    Octet* pValue;
};
typedef list<_PARAMETER> _PARAMETER_LIST;
#define PID_PAD         0
#define PID_SENTINEL    1
#define PID_STATUS_INFO 0x0071
#define PID_KEY_HASH    0x0070
//DISPOSED
//const _PARAMETER D = {PID_STATUS_INFO, 4, {0x00, 0x00, 0x00, 0x01}};
//UNREGISTERED
//const _PARAMETER U = {PID_STATUS_INFO, 4, {0x00, 0x00, 0x00, 0x02}};


/**
* @ brief 定义Data子报文
* @       Header中Flag第二位为 InlineQosFlag //暂不实现
* @       第三位为 DataFlag
* @       第四位为 KeyFlag
*/
struct _DATA_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _SUBMESSAGE_FLAG ExtraFlags[2];
    unsigned short usOctetsToInlineQos;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
    _SEQUENCE_NUMBER WriterSN;
    _PARAMETER_LIST InlineQos; //
    pSerializedPayload SerializedPayload;
};

/**
* @ brief 定义Heartbeat子报文
* @       Header中Flag第二位为 FinalFlag
* @       第三位为 LivenessFlag
*/
struct _HEARTBEAT_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
    _SEQUENCE_NUMBER FirstSN;
    _SEQUENCE_NUMBER LastSN;
    _COUNT Count;
};

/**
* @ brief 定义InfoDestination子报文
*/
struct _INFO_DESTINATION_SUBMESSAGE {
    _SUBMESSAGE_HEADER Header;
    _GUIDPREFIX GuidPrefix;
};

/**
* @ brief 定义InfoReply子报文
* @       Header中Flag第二位为 MulticastFlag
*/
struct _INFO_REPLY_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _LOCATORLIST UnicastLocatorList;
    _LOCATORLIST MulticastLocatorList;
};

/**
* @ brief 定义InfoReplyIp4子报文
* @       Header中Flag第二位为 MulticastFlag
*/
/*
struct InfoReplySubmessage {
_SUBMESSAGE_HEADER Header;
LocatorUDPv4_t UnicastLocatorList;
LocatorUDPv4_t MulticastLocatorList;
};
*/

/**
* @ brief 定义InfoSource子报文
*/
struct _INFO_SOURCE 
{
    _SUBMESSAGE_HEADER Header;
    long lUnused;
    _PROTOCOL_VERSION_T Version;
    _VENDOR_ID_T VendorId;
    _GUID_PREFIX_T GuidPrefix;
};

/**
* @ brief 定义InfoTimestamp子报文
* @       Header中Flag第二位为 InvalidateFlag
*/
struct _INFO_TIME_STAMP 
{
    _SUBMESSAGE_HEADER Header;
    _TIME_STAMP Timestamp;
};

/**
* @ brief 定义DataFrag子报文
* @       Header中Flag第二位为 InlineQosFlag //暂不实现
* @       第三位为 DataFlag
* @       第四位为 KeyFlag
*/
struct _DATA_FRAG_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _SUBMESSAGE_FLAG ExtraFlags[2];
    unsigned short usOctetsToInlineQos;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
    _SEQUENCE_NUMBER WriterSN;
	_FRAGMENT_NUMBER_T FragmentStartingNum; //分片中起始frag的分片号
	unsigned long ulFragmentsInSubmessage; //分片中包含的frag个数
	unsigned long ulFragmentSize; //每个分片的大小
	unsigned long ulDataSize; //数据原始大小
    _PARAMETER_LIST InlineQos; //
    pSerializedPayload SerializedPayload;
};

/**
* @ brief 定义NackFrag子报文
* @       Header中Flag第一位为 EndiannessFlag
* @       Header中Flag第二位为 InvalidateFlag
*/
struct _NACK_FRAG_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
	_SEQUENCE_NUMBER WriterSN;
    _FRAGMENT_NUMBER_SET FragmentNState;
    _COUNT Count;
};

#endif

