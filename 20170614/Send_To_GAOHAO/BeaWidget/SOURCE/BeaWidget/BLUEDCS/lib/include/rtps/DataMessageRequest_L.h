/**
* @ file DataMessageRequest.h
* @ brief DataMessageRequest define
* @ author xusen
* @ version 0.1
* @ history
*   1. create on 2012-12-29
*/
#ifndef _RTPS_DATAMESSAGE_REQUEST_L_H_INCLUDED_
#define _RTPS_DATAMESSAGE_REQUEST_L_H_INCLUDED_

#include "rtps/Request.h"

class ReaderLocator;

class DataMessageRequest_L : public Request {
public:
	DataMessageRequest_L (Endpoint *pEndpoint,
        _CACHE_CHANGE *pCacheChange,
        MessageProcessor *pMessageProcessor,
        MessageTransmitter *pMessageTransmitter,
        _TIME_T StartTime,
        _TIME_T EndTime) :
    Request (pEndpoint, pMessageProcessor, pMessageTransmitter, StartTime, EndTime, "Data_L") {
        m_pCacheChange = pCacheChange;
    };

    _RETURNCODE_T Execute();

	_CACHE_CHANGE* GetCacheChange() {
		return m_pCacheChange;
	}

private:
    _CACHE_CHANGE *m_pCacheChange;
};

#endif
