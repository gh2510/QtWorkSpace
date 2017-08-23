/************************************************************
** �ļ�����Message.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Messageͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_MESSAGE_H_INCLUDED_
#define _RTPS_MESSAGE_H_INCLUDED_

#include "BasicTypes.h"
#include <bitset>

using std::bitset;

/**
* @ brief �����ӱ���Ԫ�� SubmessageElement
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
* @ brief ���屨������
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
* @ brief ����Э��
*/
typedef char _PROTOCOLID_T[4];
#define PROTOCOL_RTPS "RTPS"


/**
* @ brief ���屨��ͷ_MESSAGE_HEADER
*/ 
struct _MESSAGE_HEADER 
{
    _PROTOCOLID_T Protocol;
    _PROTOCOL_VERSION Version;
    _VENDORID VendorId;
    _GUIDPREFIX GuidPrefix;
};

/**
* @ brief �����ӱ���ͷ _SUBMESSAGE_HEADER
*/ 
typedef Octet _SUBMESSAGE_FLAG;
struct _SUBMESSAGE_HEADER 
{
    _SUBMESSAGE_KIND SubmessageId;
    //Flag ��һλʼ��Ϊ EndiannessFlag ������λ���ݱ������Ͷ���
    _SUBMESSAGE_FLAG Flag;
    unsigned short usSubmessageLength;
};

/**
* @ brief ����AckNack�ӱ���
* @       Header��Flag�ڶ�λΪ FinalFlag
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
* @ brief ����_PARAMETER_LIST
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
* @ brief ����Data�ӱ���
* @       Header��Flag�ڶ�λΪ InlineQosFlag //�ݲ�ʵ��
* @       ����λΪ DataFlag
* @       ����λΪ KeyFlag
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
* @ brief ����Heartbeat�ӱ���
* @       Header��Flag�ڶ�λΪ FinalFlag
* @       ����λΪ LivenessFlag
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
* @ brief ����InfoDestination�ӱ���
*/
struct _INFO_DESTINATION_SUBMESSAGE {
    _SUBMESSAGE_HEADER Header;
    _GUIDPREFIX GuidPrefix;
};

/**
* @ brief ����InfoReply�ӱ���
* @       Header��Flag�ڶ�λΪ MulticastFlag
*/
struct _INFO_REPLY_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _LOCATORLIST UnicastLocatorList;
    _LOCATORLIST MulticastLocatorList;
};

/**
* @ brief ����InfoReplyIp4�ӱ���
* @       Header��Flag�ڶ�λΪ MulticastFlag
*/
/*
struct InfoReplySubmessage {
_SUBMESSAGE_HEADER Header;
LocatorUDPv4_t UnicastLocatorList;
LocatorUDPv4_t MulticastLocatorList;
};
*/

/**
* @ brief ����InfoSource�ӱ���
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
* @ brief ����InfoTimestamp�ӱ���
* @       Header��Flag�ڶ�λΪ InvalidateFlag
*/
struct _INFO_TIME_STAMP 
{
    _SUBMESSAGE_HEADER Header;
    _TIME_STAMP Timestamp;
};

/**
* @ brief ����DataFrag�ӱ���
* @       Header��Flag�ڶ�λΪ InlineQosFlag //�ݲ�ʵ��
* @       ����λΪ DataFlag
* @       ����λΪ KeyFlag
*/
struct _DATA_FRAG_SUBMESSAGE 
{
    _SUBMESSAGE_HEADER Header;
    _SUBMESSAGE_FLAG ExtraFlags[2];
    unsigned short usOctetsToInlineQos;
    _ENTITYID ReaderId;
    _ENTITYID WriterId;
    _SEQUENCE_NUMBER WriterSN;
	_FRAGMENT_NUMBER_T FragmentStartingNum; //��Ƭ����ʼfrag�ķ�Ƭ��
	unsigned long ulFragmentsInSubmessage; //��Ƭ�а�����frag����
	unsigned long ulFragmentSize; //ÿ����Ƭ�Ĵ�С
	unsigned long ulDataSize; //����ԭʼ��С
    _PARAMETER_LIST InlineQos; //
    pSerializedPayload SerializedPayload;
};

/**
* @ brief ����NackFrag�ӱ���
* @       Header��Flag��һλΪ EndiannessFlag
* @       Header��Flag�ڶ�λΪ InvalidateFlag
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

