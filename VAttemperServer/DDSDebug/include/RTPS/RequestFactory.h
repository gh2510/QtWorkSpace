/************************************************************
** �ļ�����RequestFactory.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����RequestFactoryͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _RTPS_REQUESTFACTORY_H_INCLUDED_
#define _RTPS_REQUESTFACTORY_H_INCLUDED_

#include "BasicTypes.h"
#include "ReturnCode.h"

class Endpoint;
class WriterProxy;
class RequestScheduler;
class MessageProcessor;
class MessageTransmitter;
struct _FRAGMENT_NUMBER_SET;

class RequestFactory 
{
public:
    //�����µ�����
    static Request *CreateDataMessageRequest (
        Endpoint *pEndpoint,
        ReaderProxy *pReaderProxy,
        RequestScheduler *pRequestScheduler);
    static Request *CreateDataMessageMultiRequest (
        Endpoint *pEndpoint,
        RequestScheduler *pRequestScheduler);
	static Request *CreateDataMessageRequest_L (
		Endpoint *pEndpoint,
        _CACHE_CHANGE *pCacheChange,
        RequestScheduler *pRequestScheduler);
    static Request *CreateHeartbeatMessageRequest (
        Endpoint *pEndpoint,
        RequestScheduler *pRequestScheduler);
    static Request *CreateAcknackMessageRequest (
        Endpoint *pEndpoint,
        WriterProxy *pWriterProxy,
        RequestScheduler *pRequestScheduler);
    static Request *CreateDeadlineRequest (
        Endpoint *pEndpoint,
        RequestScheduler *pRequestScheduler);
	static Request *CreateFragRepairRequest(
		Endpoint *pEndpoint,
        ReaderProxy *pReaderProxy,
		_SEQUENCE_NUMBER_T *pWriterSN,
		_FRAGMENT_NUMBER_SET *pFragmentNumberSet,
        RequestScheduler *pRequestScheduler);
};


#endif
