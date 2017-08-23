/************************************************************
** 文件名：BuiltinListener.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-18
** 修改人：无
** 日  期：无
** 描  述：BuiltinListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_BUILTIN_LISTENER_H_INCLUDED_
#define _RTPS_BUILTIN_LISTENER_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "dds/DataWriterListener.h"
#include "dds/DataReaderListener.h"

class DataWriter;
class DataReader;

class BuiltinPariticipantWriterListener : public DataWriterListener
{
public:
    BuiltinPariticipantWriterListener() {};
    virtual ~BuiltinPariticipantWriterListener() {};
    _RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pBuiltinParticipantWriter, const _OFFERED_DEADLINE_MISSED_STATUS& Status);
};

//2013-10-14 hjy modify
class BuiltinPublicationsWriterListener : public DataWriterListener
{
public:
	BuiltinPublicationsWriterListener() {};
	virtual ~BuiltinPublicationsWriterListener() {};
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pBuiltinPublicationsWriter, const _OFFERED_DEADLINE_MISSED_STATUS& Status);
};

//2013-10-14 hjy modify
class BuiltinSubscriptionsWriterListener : public DataWriterListener
{
public:
	BuiltinSubscriptionsWriterListener() {};
	virtual ~BuiltinSubscriptionsWriterListener() {};
	_RETURNCODE_T On_Offered_Deadline_Missed( DataWriter* pBuiltinPSubscriptionsWriter, const _OFFERED_DEADLINE_MISSED_STATUS& Status);
};

class BuiltinPariticipantReaderListener : public DataReaderListener
{
public:
    BuiltinPariticipantReaderListener() {};
    virtual ~BuiltinPariticipantReaderListener() {};
    _RETURNCODE_T  On_Data_Available( DataReader* pBuiltinParticipantReader);
};

class BuiltinPublicationsReaderListener : public DataReaderListener
{
public:
    BuiltinPublicationsReaderListener() {};
    virtual ~BuiltinPublicationsReaderListener() {};
    _RETURNCODE_T  On_Data_Available( DataReader* pBuiltinPublicationsReader);
};

class BuiltinSubscriptionsReaderListener : public DataReaderListener
{
public:
    BuiltinSubscriptionsReaderListener() {};
    virtual ~BuiltinSubscriptionsReaderListener() {};
    _RETURNCODE_T  On_Data_Available( DataReader* pBuiltinSubscriptionsReader);
};

#endif
