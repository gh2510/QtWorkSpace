/************************************************************
** �ļ�����BasicTypes.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-10
** �޸��ˣ���
** ��  �ڣ���
** ��  ����BasicTypesͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _GLOBAL_BASICTYPES_H_INCLUDED_
#define _GLOBAL_BASICTYPES_H_INCLUDED_

//#include "ReturnCode.h"
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <string>
#include <queue>
using std::vector;
using std::list;
using std::map;
using std::pair;
using std::string;
using std::make_pair;
using std::queue;

//test
#include <iostream>

using std::cout;
using std::endl;
using std::string;

#ifndef VXWORKS  //��ֲ
//#define _WIN32_WINNT   0x0501
#include <winsock.h>
#endif

//������
#include <math.h>

/**
* @ brief ����GUIDǰ׺
*/
typedef unsigned char Octet;
typedef Octet _GUID_PREFIX_T[12];
const _GUID_PREFIX_T GUIDPREFIX_UNKNOWN = {\
    0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00};

/**
* @ brief ����EntityId
*/
typedef Octet _ENTITY_KEY_TYPE[3];
typedef Octet _ENTITY_KIND_T;
struct _ENTITY_ID_T 
{
    _ENTITY_KEY_TYPE EntityKey;
    _ENTITY_KIND_T EntityKind;

    //��������� =
    _ENTITY_ID_T operator = (const _ENTITY_ID_T &Right) 
    {
        memcpy(&this->EntityKey, &Right.EntityKey, sizeof(_ENTITY_KEY_TYPE));
        memcpy(&this->EntityKind, &Right.EntityKind, sizeof(_ENTITY_KIND_T));

        return *this;
    }

    //��������� <
    bool operator < (const _ENTITY_ID_T &Right) const 
    {
        for (int I = 0; I < 3; ++I) 
        {
            if (this->EntityKey[I] < Right.EntityKey[I]) 
            {
                return true;
            }
            else if (this->EntityKey[I] > Right.EntityKey[I]) 
            {
                return false;
            }
        }
        if (this->EntityKind < Right.EntityKind) 
        {
            return true;
        }
        return false;
    }

    //��������� >
    bool operator > (const _ENTITY_ID_T &Right) const 
    {
        for (int I = 0; I < 3; ++I) 
        {
            if (this->EntityKey[I] > Right.EntityKey[I]) 
            {
                return true;
            }
            else if (this->EntityKey[I] < Right.EntityKey[I]) 
            {
                return false;
            }
        }
        if (this->EntityKind > Right.EntityKind) 
        {
            return true;
        }
        return false;
    }

    //��������� >=
    bool operator >= (const _ENTITY_ID_T &Right) const 
    {
        for (int I = 0; I < 3; ++I) 
        {
            if (this->EntityKey[I] > Right.EntityKey[I]) 
            {
                return true;
            }
            else if (this->EntityKey[I] < Right.EntityKey[I]) 
            {
                return false;
            }
        }
        if (this->EntityKind >= Right.EntityKind) 
        {
            return true;
        }
        return false;
    }

    //��������� <=
    bool operator <= (const _ENTITY_ID_T &Right) const 
    {
        for (int I = 0; I < 3; ++I) 
        {
            if (this->EntityKey[I] < Right.EntityKey[I]) 
            {
                return true;
            }
            else if (this->EntityKey[I] > Right.EntityKey[I]) 
            {
                return false;
            }
        }
        if (this->EntityKind <= Right.EntityKind) 
        {
            return true;
        }
        return false;
    }

    //��������� ==
    bool operator == ( const _ENTITY_ID_T &Right)
    {
        int N = 0;
        while( N < 3)
        {
            if( this->EntityKey[N] != Right.EntityKey[N])
                return false;
            ++N;
        }
        if( this->EntityKind != Right.EntityKind)
            return false;

        return true;
    }

    //��������� !=
    bool operator != ( const _ENTITY_ID_T &Right)
    {
        int N = 0;
        while( N < 3)
        {
            if( this->EntityKey[ N] != Right.EntityKey[ N])
                return true;
            ++N;
        }
        if( this->EntityKind != Right.EntityKind)
            return true;

        return false;
    }

};
//#define ENTITYID_UNKNOW { 0x00, 0x00, 0x00, 0x00}
//OMG�淶�����EntityKind
//δ֪ʵ��
#define ENTITYKIND_USER_UNKNOWN             0x00
//����δ֪�˵�
#define ENTITYKIND_BUILTIN_UNKNOWN          0xc0
//����������߶˵�
#define ENTITYKIND_BUILTIN_PARTICIPANT      0xc1
//�û���key������
#define ENTITYKIND_USER_WRITER_WITH_KEY     0x02
//���ô�key������
#define ENTITYKIND_BUILTIN_WRITER_WITH_KEY  0xc2
//�û�������
#define ENTITYKIND_USER_WRITER_NO_KEY       0x03
//���÷�����
#define ENTITYKIND_BUILTIN_WRITER_NO_KEY    0xc3
//�û���key���Ķ�
#define ENTITYKIND_USER_READER_WITH_KEY     0x07
//���ô�key���Ķ�
#define ENTITYKIND_BUILTIN_READER_WITH_KEY  0xc7
//�û����Ķ�
#define ENTITYKIND_USER_READER_NO_KEY       0x04
//���ö��Ķ�
#define ENTITYKIND_BUILTIN_READER_NO_KEY    0xc4

//�������ö����EntityId
//δ֪ʵ��EntityId
const _ENTITY_ID_T ENTITYID_UNKNOW                                    = { 0x00, 0x00, 0x00, 0x00 };
//�������EntityId
const _ENTITY_ID_T ENTITYID_PARTICIPANT                               = { 0x00, 0x00, 0x01, 0xc1 };
//�������ⷢ����EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_TOPIC_WRITER                 = { 0x00, 0x00, 0x02, 0xc2 };
//�������ⶩ�Ķ�EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_TOPIC_READER                 = { 0x00, 0x00, 0x02, 0xc7 };
//���÷�����Ϣ������EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER          = { 0x00, 0x00, 0x03, 0xc2 };
//���÷����������Ķ�EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER          = { 0x00, 0x00, 0x03, 0xc7 };
//���ö�����Ϣ������EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER         = { 0x00, 0x00, 0x04, 0xc2 };
//���ö�����Ϣ���Ķ�EntityId
const _ENTITY_ID_T ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER         = { 0x00, 0x00, 0x04, 0xc7 };
//����������߷�����EntityId
const _ENTITY_ID_T ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER           = { 0x00, 0x01, 0x00, 0xc2 };
//����������߶��Ķ�EntityId
const _ENTITY_ID_T ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER           = { 0x00, 0x01, 0x00, 0xc7 };
//�������������Ϣ������EntityId
const _ENTITY_ID_T ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER    = { 0x00, 0x02, 0x00, 0xc2 };
//�������������Ϣ���Ķ�EntityId
const _ENTITY_ID_T ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER    = { 0x00, 0x02, 0x00, 0xc7 };

/**
* @ brief ����GUID
*/
struct _GUID_T 
{
    _GUID_PREFIX_T GuidPrefix;
    _ENTITY_ID_T EntityId;

    _GUID_T () {};
    _GUID_T(_GUID_PREFIX_T Prefix, _ENTITY_ID_T Id) 
    {
        memcpy (this->GuidPrefix, Prefix, sizeof(_GUID_PREFIX_T));
        this->EntityId = Id;
    }

    //���������==
    bool operator ==( const _GUID_T &Right) 
    {
        int M = 0;
        while ( M < 12)
        {
            if( this->GuidPrefix[M] != Right.GuidPrefix[M])
                return false;
            ++M;
        }
        if( this->EntityId != Right.EntityId)
            return false;

        return true;
    }

    //��������� !=
    bool operator != ( const _GUID_T &Right)
    {
        int M = 0;
        while ( M < 12)
        {
            if( this->GuidPrefix[M] != Right.GuidPrefix[M])
                return true;
            ++M;
        }
        if( this->EntityId != Right.EntityId)
            return true;

        return false;
    }

    //��������� <
    bool operator < ( const _GUID_T &Right) const 
    {
        int M = 0;
        while (M < 12)
        {
            if(this->GuidPrefix[M] > Right.GuidPrefix[M]) 
            {
                return false;
            }
            else if (this->GuidPrefix[M] < Right.GuidPrefix[M]) 
            {
                return true;
            }
            ++M;
        }
        if( this->EntityId < Right.EntityId)
            return true;

        return false;
    }

    //��������� >
    bool operator > ( const _GUID_T &Right) const
    {
        int M = 0;
        while (M < 12)
        {
            if(this->GuidPrefix[M] < Right.GuidPrefix[M])
            {
                return false;
            }
            else if (this->GuidPrefix[M] > Right.GuidPrefix[M]) 
            {
                return true;
            }
            ++M;
        }
        if( this->EntityId > Right.EntityId)
            return true;
		
        return false;
    }

    //��������� =
    _GUID_T operator = ( const _GUID_T &Right)
    {
        memcpy (this->GuidPrefix, Right.GuidPrefix, sizeof(_GUID_PREFIX_T));
        this->EntityId = Right.EntityId;

        return *this;
    }
};

//#define GUID_UNKNOWN { GUIDPREFIX_UNKNOWN, ENTITYID_UNKNOW }
const _GUID_T GUID_UNKNOWN((Octet*)GUIDPREFIX_UNKNOWN, ENTITYID_UNKNOW);
//const _GUID_T GUID_UNKNOWN = {\
//    0x00, 0x00, 0x00, 0x00, \
//    0x00, 0x00, 0x00, 0x00, \
//    0x00, 0x00, 0x00, 0x00, \
//	0x00, 0x00, 0x00, 0x00 };
/**
* @ brief ����ʱ���ʽ_TIME_T
*/
struct _TIME_T 
{
    long lSecond;
    unsigned long ulNanosec;

    //��������� <=
    bool operator <= (const _TIME_T &Right) const 
    {
        if (this->lSecond > Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond < Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec > Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� <
    bool operator < (const _TIME_T &Right) const 
    {
        if (this->lSecond > Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond < Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec >= Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� >=
    bool operator >= (const _TIME_T &Right) const 
    {
        if (this->lSecond < Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond > Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec < Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� >
    bool operator > (const _TIME_T &Right) const 
    {
        if (this->lSecond < Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond > Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec <= Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� ==
    bool operator == (const _TIME_T &Right) const 
    {
        if (this->lSecond == Right.lSecond &&
            this->ulNanosec == Right.ulNanosec) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� !=
    bool operator != (const _TIME_T &Right) const 
    {
        if (this->lSecond == Right.lSecond &&
            this->ulNanosec == Right.ulNanosec) 
        {
                return false;
        }
        else 
        {
            return true;
        }
    }

    ////��������� +
    //_TIME_T operator + (const _TIME_T &Right) const 
    //{
    //    _TIME_T Temp = *this;
    //    if (Right.ulNanosec + Temp.ulNanosec >= (unsigned long)-1) 
    //    {
    //        ++ Temp.lSecond;
    //    }
    //    Temp.ulNanosec += Right.ulNanosec;
    //    Temp.lSecond += Right.lSecond;

    //    return Temp;
    //}

    ////��������� -
    //_TIME_T operator - (const _TIME_T &Right) const 
    //{
    //    _TIME_T Temp = *this;
    //    if (Temp.ulNanosec - Right.ulNanosec < 0) 
    //    {
    //        -- Temp.lSecond;
    //    }
    //    Temp.ulNanosec -= Right.ulNanosec;
    //    Temp.lSecond -= Right.lSecond;

    //    return Temp;
    //}

	//�޸�2013-8-1
	//��������� +
    _TIME_T operator + (const _TIME_T &Right) const 
    {
        _TIME_T Temp = *this;
        if (Right.ulNanosec + Temp.ulNanosec >= 1000000000) 
        {
            ++ Temp.lSecond;
			Temp.ulNanosec = Temp.ulNanosec+Right.ulNanosec-1000000000;
        }
		else
			Temp.ulNanosec = Temp.ulNanosec+Right.ulNanosec;
        
        Temp.lSecond += Right.lSecond;

        return Temp;
    }

    //��������� -
    _TIME_T operator - (const _TIME_T &Right) const 
    {
        _TIME_T Temp = *this;
        //if (Temp.ulNanosec - Right.ulNanosec < 0) 
		if (Temp.ulNanosec < Right.ulNanosec) 
        {
            -- Temp.lSecond;
			Temp.ulNanosec = Temp.ulNanosec+1000000000-Right.ulNanosec;
        }
		else
			Temp.ulNanosec -= Right.ulNanosec;

        Temp.lSecond -= Right.lSecond;

        return Temp;
	}

		//�����ݣ����������/
	_TIME_T operator / (const unsigned long &Right) const 
    {
        _TIME_T Temp = *this;
		_TIME_T Result;
		//double dTempb = Temp.lSecond + Temp.ulNanosec / 1000000000.0;
        //double dTempa = dTempb/Right;
        //Temp.lSecond = floor(dTempa);
		//Temp.ulNanosec = (dTempa - floor(dTempa))*1000000000;
		Result.lSecond = (Temp.lSecond*1000000000+Temp.ulNanosec)/(Right*1000000000);
		Result.ulNanosec = ((Temp.lSecond*1000000000+Temp.ulNanosec)-((Temp.lSecond*1000000000+Temp.ulNanosec)/(Right*1000000000))*(Right*1000000000))/Right;
        return Result;
    }
};

//ʱ����Ϣ
typedef _TIME_T _DURATION_T;

//ʱ��0
const _TIME_T TIME_ZERO      = { 0, 0 };
//�Ƿ�ʱ��
const _TIME_T TIME_INVALID   = { -1, 0xffffffff };
//���ʱ��
const _TIME_T TIME_INFINITE  = { 0x7fffffff, 0xffffffff };

//�ظ�������Ϣ����ʱ
const _DURATION_T HEARTBEAT_RESPONSE_DELAY       = { 0, /*������ɭ500000000*/100000000 };
//������Ϣ����ʱ��
const _DURATION_T HEARTBEAT_SUPPRESSION_DURATION = { 0, 0 };
//������Ϣ�ط�ʱ��
const _DURATION_T HEARTBEAT_PERIOD               = { 0,  /*������ɭ400000000*/100000000 };
//nack��Ϣ�ظ���ʱ
const _DURATION_T NACK_RESPONSE_DELAY            = { 0,  /*������ɭ200000000*/50000000 };
//nack��Ϣ����ʱ��
const _DURATION_T NACK_SUPPRESSION_DURATION      = { 0, 0 };

/**
* @ brief ���幩Ӧ�̱��
*/
struct _VENDOR_ID_T 
{
    Octet VendorId[2];

    _VENDOR_ID_T operator = (const _VENDOR_ID_T &Right) 
    {
        memcpy(this->VendorId, Right.VendorId, sizeof(_VENDOR_ID_T));

        return *this;
    }
};
const _VENDOR_ID_T VENDORID_UNKNOWN  = { 0x00, 0x00 };
const _VENDOR_ID_T VENDORID_SEU      = { 0x08, 0x08 };

/**
* @ brief �������ݵ����к� 64bit
* @       ���ز��������
*/
struct _SEQUENCE_NUMBER_T 
{
    long lHigh;
    unsigned long ulLow;

    //Ĭ�Ϲ��캯�� ��ֵΪ-1 ��ʾ��������к�
    _SEQUENCE_NUMBER_T () 
    {
        this->lHigh = -2;
        this->ulLow = 0;
    }

    //���캯��
    _SEQUENCE_NUMBER_T (const long lSeqhigh, const unsigned long ulSeqlow) 
    {
        this->lHigh = lSeqhigh;
        this->ulLow = ulSeqlow;
    }

    //��ֵ���� ()
    _SEQUENCE_NUMBER_T operator () (const long lSeqhigh, const unsigned long ulSeqlow) 
    {
        this->lHigh = lSeqhigh;
        this->ulLow = ulSeqlow;

        return *this;
    }

    //��������� <
    bool operator < (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if (this->lHigh < Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh > Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow < Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� <=
    bool operator <= (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if (this->lHigh < Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh > Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow <= Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� >
    bool operator > (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if (this->lHigh > Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh < Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow > Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� >
    bool operator > (const long &Right) const 
    {
        if (this->lHigh > 0) 
        {
            return true;
        }
        else if (this->lHigh < 0) 
        {
            return false;
        }
        else if (this->ulLow > (unsigned long)Right) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� >=
    bool operator >= (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if (this->lHigh > Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh < Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow >= Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� !=
    bool operator != (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if ((this->lHigh == Right.lHigh) && (this->ulLow == Right.ulLow)) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� ==
    bool operator == (const _SEQUENCE_NUMBER_T &Right) const 
    {
        if ((this->lHigh == Right.lHigh) && (this->ulLow == Right.ulLow)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� =
    _SEQUENCE_NUMBER_T operator = (const _SEQUENCE_NUMBER_T &Right) 
    {
        this->lHigh = Right.lHigh;
        this->ulLow = Right.ulLow;

        return *this;
    }

    //��������� =
    _SEQUENCE_NUMBER_T operator = (const unsigned long &Right) 
    {
        this->lHigh = 0;
        this->ulLow = Right;

        return *this;
    }

    //��������� ǰ��++
    _SEQUENCE_NUMBER_T operator ++ () 
    {
        ++ (this->ulLow);
        if (this->ulLow == 0)
        {
            ++ (this->lHigh);
        }

        return *this;
    }

    //��������� ����++
    _SEQUENCE_NUMBER_T operator ++ (int) 
    {
        _SEQUENCE_NUMBER_T Temp;
        Temp.lHigh = this->lHigh;
        Temp.ulLow = this->ulLow;
        this->ulLow ++;
        if (this->ulLow == 0)
        {
            this->lHigh ++;
        }

        return Temp;
    }

    //��������� ǰ��--
    _SEQUENCE_NUMBER_T operator -- () 
    {
        if (this->ulLow == 0) 
        {
            -- (this->lHigh);
        }
        -- (this->ulLow);

        return *this;
    }

    //��������� ����--
    _SEQUENCE_NUMBER_T operator -- (int)
    {
        _SEQUENCE_NUMBER_T Temp;
        Temp.lHigh = this->lHigh;
        Temp.ulLow = this->ulLow;
        if (this->ulLow == 0) 
        {
            -- (this->lHigh);
        }
        -- (this->ulLow);

        return Temp;
    }

    //��������� +
    _SEQUENCE_NUMBER_T operator + (const long Add) const 
    {
        _SEQUENCE_NUMBER_T Temp = *this;
        ////cout<<Temp.ulLow<<" "<<Add<<" "<<(unsigned long)-1<<endl;
        if (Temp.ulLow + Add >= (unsigned long)-1)
        {
            ++ Temp.lHigh;
        }
        Temp.ulLow += Add;

        return Temp;
    }

    //��������� +
    _SEQUENCE_NUMBER_T operator + (const _SEQUENCE_NUMBER_T &Right) const 
    {
        _SEQUENCE_NUMBER_T Temp = *this;
        if (Temp.ulLow + Right.ulLow >= (unsigned long)-1)
        {
            ++ Temp.lHigh;
        }
        Temp.ulLow += Right.ulLow;
        Temp.lHigh += Right.lHigh;

        return Temp;
    }

    //��������� -
    _SEQUENCE_NUMBER_T operator - (const long Sub) const 
    {
        _SEQUENCE_NUMBER_T Temp = *this;
        if (Temp.ulLow < (unsigned long)Sub)
        {
            -- Temp.lHigh;
        }
        Temp.ulLow -= Sub;

        return Temp;
    }

    //��������� -
    _SEQUENCE_NUMBER_T operator - (const _SEQUENCE_NUMBER_T &Right) const 
    {
        _SEQUENCE_NUMBER_T Temp = *this;
        if (Temp.ulLow < Right.ulLow)
        {
            -- Temp.lHigh;
        }
        Temp.ulLow -= Right.ulLow;
        Temp.lHigh -= Right.lHigh;

        return Temp;
    }

    //��������� +=
    _SEQUENCE_NUMBER_T operator += (const long lAdd) 
    {
        if (this->ulLow + lAdd >= (unsigned long)-1)
        {
            ++ this->lHigh;
        }
        this->ulLow += lAdd;

        return *this;
    }

    //��������� -=
    _SEQUENCE_NUMBER_T operator -= (const long lSub)
    {
        if (this->ulLow - lSub < 0)
        {
            -- this->lHigh;
        }
        this->ulLow -= lSub;

        return *this;
    }
};

//δ֪���к�
const _SEQUENCE_NUMBER_T SEQUENCENUMBER_UNKNOWN;

//���кŶ���
typedef queue<_SEQUENCE_NUMBER_T> _SEQ_NUM_QUEUE;

/**
* @ brief �����ַ��ʽ ip + ulPort
* @       ��ʱֻ����ipv4
*/
/*
struct _LOCATOR_T {
long Kind;
unsigned long ulPort;
Octet ulAddress[16];
};
*/
//Ŀǰ����ΪIPv4��ʽ
struct _LOCATOR_T 
{
    //ipv4 "a.b.c.d" => ulAddress = (((a*256 + b)*256 + c)*256 + d
    unsigned long ulAddress;
    unsigned long ulPort;

    //��������� !=
    bool operator != (const _LOCATOR_T &Right) const 
    {
        if (this->ulAddress == Right.ulAddress &&
            this->ulPort == Right.ulPort) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //��������� ==
    bool operator == (const _LOCATOR_T &Right) 
    {
        if (this->ulAddress == Right.ulAddress &&
            this->ulPort == Right.ulPort) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
};
const _LOCATOR_T LOCATOR_INVALID = { 0, 0 };
//����Ĭ�϶˿�Port
#define PORT_BASE_NUMBER 7400
#define DOMAINID_GAIN 250
#define PARTICIPANTID_GAIN 2
#define ADDITIONAL_OFFSETS_D0 0
#define ADDITIONAL_OFFSETS_D1 10
#define ADDITIONAL_OFFSETS_D2 1
#define ADDITIONAL_OFFSETS_D3 11
//�ಥ�˿�
#define SPDP_WELL_KNOWN_MULTICAST_PORT(ulDomainId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D0
//�����˿�
#define SPDP_WELL_KNOWN_UNICAST_PORT(ulDomainId, ulParticipantId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D1 + \
    PARTICIPANTID_GAIN * (unsigned long)ulParticipantId
//�û��ಥ�˿�
#define USER_DEFAULT_MULTICAST_PORT(ulDomainId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D2
//�û������˿�
#define USER_DEFAULT_UNICAST_PORT(ulDomainId, ulParticipantId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D3 + \
    PARTICIPANTID_GAIN * (unsigned long)ulParticipantId


/**
* @ brief �����ַ�б�
*/
typedef vector<_LOCATOR_T> _LOCATOR_LIST_T;

/**
* @ brief ����QoS
*/
//_QOS_POLICY���ƣ�ĿǰΪ_RELIABILITY_QOS_POLICY��//_DEADLINE_QOS_POLICY
enum _QOS_POLICY_NAME_T 
{
    RELIABILITYQOSPOLICY,
    DEADLINEQOSPOLICY,
	DURABILITYQOSPOLICY,
	HISTORYQOSPOLICY,
	//������
	MASSDATAQOSPOLICY,

	//2015-3-17 hjy add MultiNetworkCard support
	MULTINETWORKCARDQOSPOLICY
};

struct _QOS_POLICY 
{
    _QOS_POLICY_NAME_T Name;
};

typedef long _RELIABILITY_KIND_T;
#define BEST_EFFORT 1
#define RELIABLE 3

struct _RELIABILITY_QOS_POLICY : _QOS_POLICY 
{
    _RELIABILITY_QOS_POLICY() 
    {
        this->Name = RELIABILITYQOSPOLICY;
        this->Kind = BEST_EFFORT;
    }

    _RELIABILITY_KIND_T Kind;

    //��ͬʱʹ��RELIABLE��ResourceLimitsQosPolicy����ʱ����ס���ݿ�����ʱ�䳤��,Ŀǰ��Ϊ��ֵ
    //_DURATION_T max_blocking_time;
};

struct _DEADLINE_QOS_POLICY : _QOS_POLICY 
{
    _DEADLINE_QOS_POLICY() 
    {
        this->Name = DEADLINEQOSPOLICY;
        this->Period = TIME_INVALID;
    }

    _DURATION_T Period;
};

typedef long _DURABILITY_KIND_T;
#define VOLATILE 1
#define TRANSIENT_LOCAL 2
#define TRANSIENT 3
#define PERSISTENT 4
struct _DURABILITY_QOS_POLICY : _QOS_POLICY 
{
    _DURABILITY_QOS_POLICY() 
    {
        this->Name = DURABILITYQOSPOLICY;
        this->Kind = VOLATILE;
    }

    _DURABILITY_KIND_T Kind;
};

typedef long _HISTORY_KIND_T;
#define KEEP_NONE 1
#define KEEP_LAST 2
#define KEEP_ALL 3
struct _HISTORY_QOS_POLICY : _QOS_POLICY 
{
    _HISTORY_QOS_POLICY() 
    {
        this->Name = HISTORYQOSPOLICY;
        this->Kind = KEEP_NONE;
		this->ulDepth = 1;
    }

    _HISTORY_KIND_T Kind;
	unsigned long ulDepth;
};

//������
struct _MASS_DATA_QOS_POLICY : _QOS_POLICY
{
    _MASS_DATA_QOS_POLICY() 
    {
        this->Name = MASSDATAQOSPOLICY;
		this->Period = TIME_INVALID;
    }

    _DURATION_T Period;
};

//2015-3-17 hjy add MultiNetworkCard support
struct _MULTI_NETWORK_CARD_QOS_POLICY : _QOS_POLICY
{
	_MULTI_NETWORK_CARD_QOS_POLICY() 
	{
		this->Name = MULTINETWORKCARDQOSPOLICY;
		this->IsMultiNetCard = false;
		this->MultiNetCardNumber = 0;
	}

	bool IsMultiNetCard;
	int MultiNetCardNumber;
};

struct _ENTITY_QOS 
{
    struct _RELIABILITY_QOS_POLICY Reliability;
    struct _DEADLINE_QOS_POLICY Deadline;
	struct _DURABILITY_QOS_POLICY Durability;
	struct _HISTORY_QOS_POLICY History;
	struct _MULTI_NETWORK_CARD_QOS_POLICY MultiNetCard;//2015-3-17 hjy add MultiNetworkCard support
};
//struct _DATA_WRITER_QOS;
struct _DATA_READER_QOS : public _ENTITY_QOS 
{
	//bool operator== (const _DATA_WRITER_QOS& Right) const;
};

struct _DATA_WRITER_QOS : public _ENTITY_QOS 
{
	//��������� ==
	bool operator== (const _DATA_READER_QOS& Right) const
    {
		if(this->Reliability.Kind != Right.Reliability.Kind)
			return false;
		if(this->Deadline.Period > Right.Deadline.Period)
			return false;
		if(this->Durability.Kind < Right.Durability.Kind)
			return false;
		return true;
	}
	//������
	struct _MASS_DATA_QOS_POLICY Mass_Data;

};
//��������� ==
//bool _DATA_READER_QOS::operator== (const _DATA_WRITER_QOS& Right) const{
//	if(this->Reliability.Kind != Right.Reliability.Kind)
//		return false;
//	if(this->Deadline.Period < Right.Deadline.Period)
//		return false;
//	if(this->Durability.Kind > Right.Durability.Kind)
//		return false;
//	return true;
//}


//const _DATA_WRITER_QOS *DDS_DATAWRITER_QOS_DEFAULT = NULL;
//const _DATA_READER_QOS *DDS_DATAREADER_QOS_DEFAULT = NULL;


/**
* @ brief ����������
*/
typedef long _DOMAINID_T;

/**
* @ brief �������
*/
typedef long _COUNT_T;

/**
* @ brief ����RTPSЭ��汾  RTPS Protocol Version
*/
struct _PROTOCOL_VERSION_T 
{
    Octet Major;
    Octet Minor;

    _PROTOCOL_VERSION_T operator = (const _PROTOCOL_VERSION_T &Right) 
    {
        this->Major = Right.Major;
        this->Minor = Right.Minor;

        return *this;
    }
};
const _PROTOCOL_VERSION_T PROTOCOLVERSION_1_0 = {1, 0};
const _PROTOCOL_VERSION_T PROTOCOLVERSION_1_1 = {1, 1};
const _PROTOCOL_VERSION_T PROTOCOLVERSION_2_0 = {2, 0};
const _PROTOCOL_VERSION_T PROTOCOLVERSION_2_1 = {2, 1};
#define PROTOCOLVERSION PROTOCOLVERSION_2_1

/**
* @ brief �����������
*/ 
class Request;
typedef list<Request *> _REQUEST_LIST_T;

//������
class MassDataRequest;
typedef list<MassDataRequest *> _MASSDATA_REQUEST_LIST_T;
/**
* @ brief ���屨�Ľ�����Ϣ�ṹ
*/ 
struct _RECEIVER 
{
    _PROTOCOL_VERSION_T SourceVersion;
    _VENDOR_ID_T SourceVendorId;
    _GUID_PREFIX_T SourceGuidPrefix;
    _GUID_PREFIX_T DestGuidPrefix;
    _LOCATOR_LIST_T UnicastReplyLocatorList;
    _LOCATOR_LIST_T MulticastReplyLocatorList;
    bool bHaveTimestame;
    _TIME_T Timestamp;
};

/**
* @ brief ����Socket vxworks
*/ 
#ifdef VXWORKS   //��ֲ
typedef int _SOCKET_T;
#else
typedef SOCKET _SOCKET_T;
#endif

typedef list<_SOCKET_T> _SOCKET_LIST_T;

/**
* @ brief ����˵�Endpoint �б�
* @       ����ͨ��EntityId���ٲ���Endpoint
*/ 
class Endpoint;
typedef map<_ENTITY_ID_T, Endpoint*> _ENDPOINT_LIST_T;

/**
* @ brief ����ಥ��ַ��˵�ӳ���Ӧ��ϵ
* @       ����ͨ���ಥ��ַ����_ENDPOINT_LIST_T
*/ 
typedef map<unsigned long, _ENDPOINT_LIST_T> _ENDPOINT_MULTI_ADDR_LIST_T;

/**
* @ brief ������ջ�������С �ֽ�
*/ 
#define RECEIVE_BUFFER_SIZE 6553600

/**
* @ brief ����Listener������״̬��
*/
typedef unsigned long _STATUS_MASK;
#define STATUS_MASK_NULL                                0x00000000
#define STATUS_MASK_ALL                                 0xFFFFFFFF
#define STATUS_MASK_ON_DATA_AVAILABLE                   0x00000001 << 1
#define STATUS_MASK_ON_OFFERED_DEADLINE_MISSED          0x00000001 << 2
#define STATUS_MASK_ON_REQUESTED_DEADLINE_MISSED        0x00000001 << 3

/**
* @ brief ����Change������
*/
typedef unsigned short _CHANGE_KIND_T;
#define ALIVE                   0x0001 << 0
#define NOT_ALIVE_DISPOSED      0x0001 << 1
#define NOT_ALIVE_UNREGISTERED  0x0001 << 2


/**
* @ brief ����_INSTANCE_HANDLEʵ���ʶ����
*/
#define RTPS_KEY_HASH_MAX_LENGTH 16

struct _RTPS_KEY_HASH 
{
    unsigned char szValue[RTPS_KEY_HASH_MAX_LENGTH];
    unsigned int ulLength;

    //Ĭ�Ϲ��캯��
    //_RTPS_KEY_HASH () {
    //    memset(szValue, 0, RTPS_KEY_HASH_MAX_LENGTH);
    //    ulLength = RTPS_KEY_HASH_MAX_LENGTH;
    //}

    //��������� =
    _RTPS_KEY_HASH operator= (const _RTPS_KEY_HASH& Right) 
    {
        memcpy(this->szValue, Right.szValue, RTPS_KEY_HASH_MAX_LENGTH);
        this->ulLength = Right.ulLength;
        return *this;
    }

    //��������� ==
    bool operator== (const _RTPS_KEY_HASH& Right) const 
    {
        if(this->ulLength == Right.ulLength) 
        {
            unsigned  iPos = 0;
            const unsigned char *pLtkh, *pRtkh;
            while(iPos < this->ulLength) 
            {
                pLtkh = this->szValue + iPos;
                pRtkh = Right.szValue + iPos;
                if(*pLtkh != *pRtkh) 
                {
                    return false;
                }
                else 
                {
                    iPos++;
                }
            }
            return true;
        }
        else 
        {
            return false;
        }
    }

    //��������� !=
    bool operator!= (const _RTPS_KEY_HASH& Right) const 
    {
        return(!(*this == Right));
    }

    //��������� >
    bool operator> (const _RTPS_KEY_HASH& Right) const 
    {
        int iPos = 0;
        const unsigned char *pLtkh, *pRtkh;
        while(iPos < RTPS_KEY_HASH_MAX_LENGTH) 
        {
            pLtkh = this->szValue + iPos;
            pRtkh = Right.szValue + iPos;
            if(*pLtkh > *pRtkh) 
            {
                return true;
            }
            else if(*pLtkh < *pRtkh) 
            {
                return false;
            }
            else 
            {
                iPos++;
            }
        }
        return false;
    }

    //��������� <
    bool operator< (const _RTPS_KEY_HASH& Right) 
    {
        return(!(*this > Right) && *this != Right);
    }
};
struct _INSTANCE_HANDLE 
{
    struct _RTPS_KEY_HASH _KEY_HASH;
    bool bIsValid;

    //Ĭ�Ϲ��캯��
    //_INSTANCE_HANDLE() {
    //    memset(_KEY_HASH.szValue, 0, RTPS_KEY_HASH_MAX_LENGTH);
    //    _KEY_HASH.ulLength = RTPS_KEY_HASH_MAX_LENGTH;
    //    bIsValid = false;
    //}

    //��������� =
    _INSTANCE_HANDLE operator= (const _INSTANCE_HANDLE& Right) 
    {
        this->_KEY_HASH = Right._KEY_HASH;
        this->bIsValid = Right.bIsValid;
        return *this;
    }

    //��������� ==
    bool operator== (const _INSTANCE_HANDLE& Right) const 
    {
        return(this->_KEY_HASH == Right._KEY_HASH && this->bIsValid == Right.bIsValid);
    }

    //��������� !=
    bool operator!= (const _INSTANCE_HANDLE& Right) const 
    {
        return(this->_KEY_HASH != Right._KEY_HASH || this->bIsValid != Right.bIsValid);
    }

    //��������� >
    bool operator> (const _INSTANCE_HANDLE& Right) const
    {
        return(this->_KEY_HASH > Right._KEY_HASH || this->bIsValid && !(Right.bIsValid));
    }

    //��������� <
    bool operator< (const _INSTANCE_HANDLE& Right) const 
    {
        return(!(*this > Right) && *this != Right);
    }

    void print() 
    {
        for(unsigned int I = 0; I < this->_KEY_HASH.ulLength; I++) 
        {
      //      //cout<<this->_KEY_HASH.szValue[I];
        }
        //cout<<endl;
    }
};
typedef struct _INSTANCE_HANDLE _INSTANCE_HANDLE_T;
typedef struct _RTPS_KEY_HASH _KEY_HASH_T;
#define RTPS_KEY_HASH_NIL {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define RTPS_KEY_HASH_DEFAULT { \
RTPS_KEY_HASH_NIL,  /* szValue */\
RTPS_KEY_HASH_MAX_LENGTH/* ulLength */\
}
#define INSTANCE_HANDLE_NIL { \
RTPS_KEY_HASH_DEFAULT, \
FALSE /* bIsValid */ }
const _INSTANCE_HANDLE_T HANDLE_NIL = INSTANCE_HANDLE_NIL;


typedef list< pair<_SEQUENCE_NUMBER_T, _INSTANCE_HANDLE_T> > _SEQ_NUM_TO_HANDLE;

/**
* @ brief ����_CACHE_CHANGE��ʽ
*/
struct _CACHE_CHANGE 
{
    _CHANGE_KIND_T Kind;
    _GUID_T WriterGuid;
    _INSTANCE_HANDLE_T InstanceHandle;
    _SEQUENCE_NUMBER_T SequenceNumber;
    _TIME_T Timestamp;
    unsigned long ulLength;
    char *pDatavalue;
};

/**
* @ brief ����CacheChange���б��ʽ
*/
typedef list<_CACHE_CHANGE*> _CACHE_CHANGE_LIST_T;

/**
* @ brief ����WriterProxy���б��ʽ
*/
class WriterProxy;
typedef map<_GUID_T, WriterProxy*> _WRITER_PROXY_LIST_T;

/**
* @ brief ����HistoryCache�е�������ʽ
*/
typedef map<_SEQUENCE_NUMBER_T, unsigned long> _INDEX_T;

/**
* @ brief ����ӷ����˽��յ�����״̬��Ϣ��ʽ
*/
typedef Octet _CHANGE_FROM_WRITER_STATUS_KIND;
const _CHANGE_FROM_WRITER_STATUS_KIND WRITER_CHANGE_UNKNOWN = 0x00;
const _CHANGE_FROM_WRITER_STATUS_KIND WRITER_CHANGE_MISSING = 0x01;
const _CHANGE_FROM_WRITER_STATUS_KIND WRITER_CHANGE_REQUESTED = 0x02;
const _CHANGE_FROM_WRITER_STATUS_KIND WRITER_CHANGE_RECEIVED = 0x03;
const _CHANGE_FROM_WRITER_STATUS_KIND WRITER_CHANGE_LOST = 0x04;

struct _CHANGE_FROM_WRITER 
{
    _CHANGE_FROM_WRITER_STATUS_KIND Status;
    _SEQUENCE_NUMBER_T RemoteSeqNum;
    _SEQUENCE_NUMBER_T LocalSeqNum;
};

//���������ݽ���״̬ӳ���
typedef map<_SEQUENCE_NUMBER_T, _CHANGE_FROM_WRITER*> _CHANGE_FROM_WRITER_LIST_T;

/**
* @ brief ����ReaderProxy����
*/
class ReaderProxy;
/*�޸�
struct ReaderProxyElement {
    ReaderProxy *readerProxy;
    struct ReaderProxyElement *pNext;
};
struct _READER_PROXY_LIST {
    unsigned long num;
    struct ReaderProxyElement *head, *tail;
};
*/
typedef map<_GUID_T, ReaderProxy*> _READER_PROXY_LIST;

/**
* @ brief ����ReaderLocator����
*/
class ReaderLocator;
typedef map<_GUID_T, ReaderLocator*> _READER_LOCATOR_LIST;

/**
* @ brief ���巢�Ͷ˿ڶ���
*/
typedef map<int, _SOCKET_T> _SEND_SOCKET_LIST;

/**
* @ brief ���巢���˷������Ķ˵�����״̬��Ϣ��ʽ
*/
typedef Octet _CHANGE_FOR_READER_STATUS_KIND;
const _CHANGE_FOR_READER_STATUS_KIND NEW = 0x00;
const _CHANGE_FOR_READER_STATUS_KIND UNSENT = 0x01;
const _CHANGE_FOR_READER_STATUS_KIND REQUESTED = 0x02;
const _CHANGE_FOR_READER_STATUS_KIND UNDERWAY = 0x03;
const _CHANGE_FOR_READER_STATUS_KIND UNACKNOWLEDGED = 0x04;
const _CHANGE_FOR_READER_STATUS_KIND ACKNOWLEDGED = 0x05;

struct _CHANGE_FOR_READER
{
    _CHANGE_FOR_READER_STATUS_KIND Status;
    _SEQUENCE_NUMBER_T SequenceNumber;
   // _CHANGE_FOR_READER *pNext;
};

//struct _CHANGE_FOR_READER_LIST{  //�޸�4-29
//    unsigned long num;
//    _CHANGE_FOR_READER *head, *tail;
//};

typedef map<_SEQUENCE_NUMBER_T, _CHANGE_FOR_READER*> _CHANGE_FOR_READER_LIST;

/**
* @ brief ����ʵ��״̬����
*/
typedef unsigned short InstanceStateKind;
#define ALIVE                0x0001 << 0
#define NOT_ALIVE_DISPOSED   0x0001 << 1
#define NOT_ALIVE_NO_WRITERS 0x0001 << 2

/**
* @ brief �������ݸ�����Ϣ
*/
struct _SAMPLE_INFO 
{
    //ʵ����״̬
    InstanceStateKind Instance_state;
    //����ʱ��ʱ���
    _TIME_T Source_timestamp;
    //ʵ����ʶ
    _INSTANCE_HANDLE_T Instance_handle;
    //�Ƿ�����Ч����
    bool bValid_data;
};

//typedef list<_QOS_POLICY*> QosPolicyList;
typedef vector<_SAMPLE_INFO> _SAMPLE_INFO_SEQ;

/**
* @ brief ����DomainParticipa���б��ʽ
*/
class DomainParticipant;
typedef list<DomainParticipant*> _DOMAIN_PARTICIPANT_LIST;
typedef map<unsigned long, _DOMAIN_PARTICIPANT_LIST> _DOMAIN_PARTICIPANT_MAP;

/**
* @ brief �������ö˵㼯�ϱ�ʶ
*/
typedef unsigned long _BUILTIN_ENDPOINT_SET_T;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER         0x00000001 << 0
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR          0x00000001 << 1
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER         0x00000001 << 2
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR          0x00000001 << 3
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER        0x00000001 << 4
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR         0x00000001 << 5
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER   0x00000001 << 6
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR    0x00000001 << 7
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER   0x00000001 << 8
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR    0x00000001 << 9
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_WRITER    0x00000001 << 10
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_READER    0x00000001 << 11

/**
* @ brief ����˵�״̬
*/
enum _ENTITY_STATUS_T 
{
    CREATION,
    MODIFICATION,
    DELETION,
    EXTENSION
};

/**
* @ brief ����SPDP��������ݸ�ʽ
*/
//Participant��Ϣ
struct _PARTICIPANT_PROXY_DATA 
{
    _PROTOCOL_VERSION_T ProtocolVersion;
    _GUID_PREFIX_T GuidPrefix;
    _VENDOR_ID_T VendorId;
    _BUILTIN_ENDPOINT_SET_T AvailableBuiltinEndpoints;
    _LOCATOR_LIST_T MetatrafficUnicastLocatorList;
    _LOCATOR_LIST_T MetatrafficMulticastLocatorList;
    _LOCATOR_LIST_T DefaultUnicastLocatorList;
    _LOCATOR_LIST_T DefaultMulticastLocatorList;
};

//������ʹ�õ�Participant��Ϣ
struct _SPDP_DISCOVERED_PARTICIPANT_DATA : public _PARTICIPANT_PROXY_DATA
{
    _DURATION_T LeaseDuration;
    _TIME_T ReceiveTime;
    _ENTITY_STATUS_T Status;
};

/**
* @ brief ����SEDP��ʹ�õķ��������ݵĸ�ʽ
*/
//��������Ϣ
struct _WRITER_PROXY_DATA 
{
    _GUID_T RemoteWriterGuid;
    _LOCATOR_LIST_T UnicastLocatorList;
    _LOCATOR_LIST_T MulticastLocatorList;
};

//����������Ϣ
struct _PUBLICATION_BUILTIN_TOPIC_DATA 
{
    string strTopic_name;
    string strType_name;
    _DEADLINE_QOS_POLICY Deadline;
    _RELIABILITY_QOS_POLICY Reliability;
	_DURABILITY_QOS_POLICY Durability;
};

//����ʹ�õķ�������Ϣ
struct _DISCOVERED_WRITER_DATA :
    public _WRITER_PROXY_DATA,
    public _PUBLICATION_BUILTIN_TOPIC_DATA 
{
    _ENTITY_STATUS_T Status;
};
typedef list<_DISCOVERED_WRITER_DATA *> _PUBLICATIONS_DATA_LIST_T;
/**
* @ brief ����SEDP��ʹ�õĶ��Ķ����ݵĸ�ʽ
*/
//���Ķ���Ϣ
struct _READER_PROXY_DATA 
{
    _GUID_T RemoteReaderGuid;
    _LOCATOR_LIST_T UnicastLocatorList;
    _LOCATOR_LIST_T MulticastLocatorList;
};

//����������Ϣ
struct _SUBSCRIPTION_BUILTIN_TOPIC_DATA 
{
	string strTopic_name;
    string strType_name;
	_DEADLINE_QOS_POLICY Deadline;
	_RELIABILITY_QOS_POLICY Reliability;
	_DURABILITY_QOS_POLICY Durability;
};

//����ʹ�õĶ��Ķ���Ϣ
struct _DISCOVERED_READER_DATA :
    public _READER_PROXY_DATA,
    public _SUBSCRIPTION_BUILTIN_TOPIC_DATA 
{
    _ENTITY_STATUS_T Status;
};
typedef list<_DISCOVERED_READER_DATA *> _SUBSCRIPTIONS_DATA_LIST_T;

/**
* @ brief ��¼Agent�ṹ ������Ϣ
*/
//��¼Զ��DomainParticipa��Ϣ���б�
struct _REMOTE_PARTICIPANT_DATA_NODE
{
    _SPDP_DISCOVERED_PARTICIPANT_DATA* RemoteParticipantData;
    _REMOTE_PARTICIPANT_DATA_NODE* NextRemoteParticipant;
};

/**
* @ brief ��¼Agent�ṹ ������Ϣ
* @ brief ��¼Publisher��Subscriber��Topic��_TYPE��Ip��DataWriter��DataReader�б�ĸ�ʽ
*/
class Agent;
struct _TYPE
{
    Agent *pAgent;
};
class Publisher;
class Subscriber;
class Topic;
class DataWriter;
class DataReader;
class ContentFilteredTopic;
class Filter;
typedef list <Publisher*> _PUBLISHER_LIST_T;
typedef list <Subscriber*> _SUBSCRIBER_LIST_T;
typedef list <Topic*> _TOPIC_LIST_T;
typedef list <ContentFilteredTopic*> _CONTENT_FILTERED_TOPIC_LIST_T;
typedef list <_TYPE> _TYPE_LIST_T;
typedef list <unsigned long> _IP_LIST_T;
typedef list <DataWriter*> _DATA_WRITER_LIST_T;
typedef list <DataReader*> _DATA_READER_LIST_T;

/**
* @ brief �����������ͺ�typecode�Ķ�Ӧ��ϵ
*/
class TypeCode;
typedef map<string, TypeCode*> _TYPE_CODE_LIST_T;
/**
* @ brief ����_DDS_STRING����
*/
typedef std::string _DDS_STRING;
typedef list<_DDS_STRING> _STRING_SEQ;



///**
//* @ brief ʵ����DataWriter�˵���Ϣ
//*/
//struct InstanceInfo_DW {
//    //instance��״̬
//    InstanceStateKind InstanceState;
//};
//typedef map<_INSTANCE_HANDLE_T, InstanceInfo_DW> InstanceMap_DW;

/**
* @ brief ʵ����Writer�˵���Ϣ
*/
struct _INSTANCE_INFO_W 
{
    //instance��״̬
    InstanceStateKind InstanceState;
    //�ϴη��͵�ʱ��
    _TIME_T LastSendTime;
};
typedef map<_INSTANCE_HANDLE_T, _INSTANCE_INFO_W> _INSTANCE_MAP_W;


///**
//* @ brief ʵ����DataReader�˵���Ϣ
//*/
//struct InstanceInfo_DR {
//    //instance��״̬
//    InstanceStateKind InstanceState;
//};
//typedef map<_INSTANCE_HANDLE_T, InstanceInfo_DR> InstanceMap_DR;

/**
* @ brief ʵ����Reader�˵���Ϣ
*/
struct _INSTANCE_INFO_FROM_W 
{
    _CHANGE_KIND_T InstanceState;
};
typedef map<_GUID_T, _INSTANCE_INFO_FROM_W> _WRITER_TO_INSTANCE_INFO;
struct _INSTANCE_INFO_R 
{
    //instance��״̬
    InstanceStateKind InstanceState;
    //�ϴη��͵�ʱ��
    _TIME_T LastRecvTime;
    //�����˸�ʵ������Ϣ
    _WRITER_TO_INSTANCE_INFO WritertoInstanceInfo;
};
typedef map<_INSTANCE_HANDLE_T, _INSTANCE_INFO_R> _INSTANCE_MAP_R;


/**
* @ brief ������������ͣ��Ƿ���Key
*/
typedef enum 
{
    NO_KEY,
    WITH_KEY
}_TOPIC_KIND_T;

/**
* @ brief �����Deadlineδ�����״̬
*/
struct _REQUESTED_DEADLINE_MISSED_STATUS 
{
    long lTotal_count;
    long lTotal_count_change;
    _INSTANCE_HANDLE_T Last_instance_handle;

    //��������� =
    _REQUESTED_DEADLINE_MISSED_STATUS operator= (const _REQUESTED_DEADLINE_MISSED_STATUS& Right)
    {
        this->lTotal_count = Right.lTotal_count;
        this->lTotal_count_change = Right.lTotal_count_change;
        this->Last_instance_handle = Right.Last_instance_handle;
        return *this;
    }
};

/**
* @ brief �ṩ��Deadlineδ�����״̬
*/
struct _OFFERED_DEADLINE_MISSED_STATUS 
{
    long lTotal_count;
    long lTotal_count_change;
    _INSTANCE_HANDLE_T Last_instance_handle;

    //��������� =
    _OFFERED_DEADLINE_MISSED_STATUS operator= (const _OFFERED_DEADLINE_MISSED_STATUS& Right) 
    {
        this->lTotal_count = Right.lTotal_count;
        this->lTotal_count_change = Right.lTotal_count_change;
        this->Last_instance_handle = Right.Last_instance_handle;
        return *this;
    }
};

/**
* @ brief ��Ƭ��
*/
typedef unsigned long _FRAGMENT_NUMBER_T;

/**
* @ brief ���ݳ����б�
*/
typedef vector<unsigned long> _MESSAGE_LENGTH_LIST_T;

/**
* @ brief ��Ƭ���ݵ�ָ�롢����
*/
struct _FRAG_DATA 
{
	char* pData;
	unsigned long ulLength;
};

/**
* @ brief ���ݷ�Ƭ�ź����ݵĶ�Ӧ��ϵ
*/
typedef map<_FRAGMENT_NUMBER_T, _FRAG_DATA> _FRAG_NUM_MAP_T;

/**
* @ brief һ��SequenceNumber��Ӧ�����ݷ�Ƭ
*/
struct _FRAGMENT_DATA 
{
	_SEQUENCE_NUMBER_T SeqNum;
	_FRAG_NUM_MAP_T FragNumMap;
	_TIME_T LastUpdateTime;
	_FRAGMENT_NUMBER_T FragSum;
	_GUID_T WriterGUID;
};

//������
struct _MASS_FRAGMENT_DATA 
{
	unsigned long DataNum;
	_FRAG_NUM_MAP_T FragNumMap;
	_FRAGMENT_NUMBER_T FragSum;
	unsigned long Length;
	_GUID_T WriterGUID;
};
/**
* @ brief ���ݷ�Ƭ�б�
*/
typedef list<_FRAGMENT_DATA*> _FRAGMENT_DATA_LIST_T;
//������
typedef list<_MASS_FRAGMENT_DATA*> _MASS_FRAGMENT_DATA_LIST_T;
typedef _FRAG_DATA _MASS_DATA;
typedef list<_MASS_DATA*> _MASS_DATA_LIST_T;

/**
* @ brief ������Ҫ��Ƭ�����ݴ�С�ͷ�Ƭ��С
*/
#define DATAFRAG_LENGTH 4200
#define DATAMESSAGE_LIMIT 8400

///**
//* @ brief �м���_DDS_STRING����
//*/
//struct KeyedString {
//    char* key;
//    char* szValue;
//};
//typedef struct KeyedString _KEYED_STRING_KEY_HOLDER;
//typedef vector<KeyedString> _KEYED_STRING_SEQ;
//typedef map<_INSTANCE_HANDLE_T, _KEYED_STRING_KEY_HOLDER> _INSTANCE_HANDLE_TO_KEY_HOLDER;

/**
* @ brief CDR��TypeCode���Ͷ���
*/
class TypeCode;
typedef TypeCode *_TYPE_CODE_PTR;

typedef __int64 _LONG_LONG;
typedef unsigned __int64 _U_LONG_LONG;
typedef long double _LONG_DOUBLE;

/**
* @ brief Ĭ�ϵ�ContentFilteredTopic��������
*/
#define DDS_CONTENT_FILTERED_TOPIC_TYPE "DDSContentFilteredTopic"

#ifndef VXWORKS
#ifndef _DDS_LIB_FILE
#ifdef _DDS_DLL_FILE
#define DDS_DLL _declspec(dllexport)
#else
#define DDS_DLL _declspec(dllimport)
#endif
#endif
#endif

#endif
