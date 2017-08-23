/************************************************************
** �ļ�����ParticipantDataWriter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����ParticipantDataWriterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_PARTICIPANTDATAWRITER_H_INCLUDED_
#define _DDS_PARTICIPANTDATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/DataWriter.h"

class Topic;
class DataWriterListener;
class Publisher;

class ParticipantDataWriter : public DataWriter 
{
public:
    //���캯��
    ParticipantDataWriter (Topic* pTopic,
        const _DATA_WRITER_QOS* pQos,
        DataWriterListener* pListener,
        _STATUS_MASK Mask,
        Publisher* pPublisher,
        unsigned long ulCacheLength);

    //��������
    virtual ~ParticipantDataWriter ();

    //д����
    _RETURNCODE_T Write(_SPDP_DISCOVERED_PARTICIPANT_DATA *pData);

    //��������
    _RETURNCODE_T SendParticipantData (_ENTITY_STATUS_T Status);

    //��ָ��DataWriter��ָ�빹��StringDataWriter����
    static ParticipantDataWriter* Narrow (DataWriter* pDataWriter);

    //��ʼ��
    _RETURNCODE_T Init (_DURATION_T LeaseTime);

    DEF_NARROW_METHOD(ParticipantDataWriter);

    //����״̬��Ϣ
	//2013-09-27 hjy modify
    _RETURNCODE_T SendInfo(_ENTITY_STATUS_T Status) 
    {
		//cout<<"lllllllllllllllllllllllllllllllll"<<endl;
        return RETURNCODE_OK;
    }

	//2013-09-27 hjy modify ���ڷ������ýڵ�ParticipantDataWriterɾ������Ϣ
	//_RETURNCODE_T SendDeleteInfo(_ENTITY_STATUS_T Status) 
	//{
	//	DomainParticipant* pDomainParticipant = this->GetDomainParticipant();
	//	Discovery* pDiscovery= pDomainParticipant->GetRelatedDiscovery();
	//	return pDiscovery->SendPublicationData(this, Status);
	//}

    //ƥ��
    _RETURNCODE_T Match() 
    {
        return RETURNCODE_OK;
    }

private:
    //ʧ���ʱ������
    _DURATION_T m_LeaseTime;

    //��ʼ�� ����ReaderProxy
    _RETURNCODE_T ReaderProxyInit ();
};

#endif
