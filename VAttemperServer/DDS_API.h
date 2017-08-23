#ifndef DDS_API_INCLUDE
#define DDS_API_INCLUDE

#include "BasicTypes.h"
#include "ReturnCode.h"

#include "dds/DomainManagement.h"
#include "dds/DomainParticipant.h"
#include "dds/DataWriter.h"
#include "dds/DataReader.h"
#include "dds/DataWriterListener.h"
#include "dds/DataReaderListener.h"

#include "dds/StringDataWriter.h"
#include "dds/StringDataReader.h"
#include "dds/StringTypeSupport.h"

#include "dds/MassDataWriter.h"
#include "dds/MassDataReader.h"
#include "dds/MassDataListener.h"
#include "dds/MassDataTypeSupport.h"

//IDL生成的文件
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "IDL_TypeSupport.h"

//加入数据域
inline _RETURNCODE_T DomainInit(_DOMAINID_T domainId, char* compName) {
    DomainParticipant *domainParticipant = DomainManagement::GetInstance()->DomainInit(domainId, compName);
    if (domainParticipant == NULL)
        return RETURNCODE_DOMAIN_INIT_FAILED;

    //IDL编译器生成 注册数据类型
    V_PageAttemperTypeSupport::register_type(domainParticipant, V_PageAttemperTypeSupport::get_type_name());

    return RETURNCODE_OK;
}

//创建发布者
inline DataWriter *CreateDataWriter(const char *componentName,
                             _DOMAINID_T domainId,
                             const char *topic_name,
                             const char *type_name,
                             DataWriterListener *listener,
                             const _DATA_WRITER_QOS   *qos) {
    DomainParticipant *domainParticipant = DomainManagement::GetInstance()->ParticipantGet(domainId);
    if (domainParticipant == NULL) {
        return NULL;
    }

    Topic *topic = domainParticipant->CreateTopic(topic_name, type_name);
    if (topic == NULL) {
        return NULL;
    }

    DataWriter *newDataWriter = domainParticipant->CreateDataWriter(
        topic, listener, qos, STATUS_MASK_ALL);
	   if(newDataWriter != NULL)
        newDataWriter->AppSet(componentName);

    return newDataWriter;
}

//删除发布者
inline _RETURNCODE_T DeleteDataWriter(DataWriter *aDataWriter) {
    DomainParticipant *domainParticipant = aDataWriter->GetDomainParticipant();
    _RETURNCODE_T ret = domainParticipant->Delete_Datawriter(aDataWriter);
    if(ret == RETURNCODE_OK) return RETURNCODE_DELETEDATAWRITER_OK;
    else return ret;
}

//创建订阅者
inline DataReader *CreateDataReader(const char *componentName,
                             _DOMAINID_T domainId,
                             const char *topic_name,
                             const char *type_name,
                             DataReaderListener *listener,
                             const _DATA_READER_QOS *qos) {
    DomainParticipant *domainParticipant = DomainManagement::GetInstance()->ParticipantGet(domainId);
    if (domainParticipant == NULL) {
        return NULL;
    }

    Topic *topic = domainParticipant->CreateTopic(topic_name, type_name);
    if (topic == NULL) {
        return NULL;
    }

    DataReader *newDataReader = domainParticipant->CreateDataReader(
        topic, listener, qos, STATUS_MASK_ALL);
	   if(newDataReader != NULL)
        newDataReader->AppSet(componentName);

    return newDataReader;
}

//删除订阅者
inline _RETURNCODE_T DeleteDataReader(DataReader *aDataReader) {
    DomainParticipant *domainParticipant = aDataReader->GetDomainParticipant();
    _RETURNCODE_T ret = domainParticipant->Delete_Datareader(aDataReader);
    if(ret == RETURNCODE_OK) return RETURNCODE_DELETEDATAREADER_OK;
    else return ret;
}

//创建数据过滤订阅者
inline DataReader *CreateDataReader(const char *componentName,
                  _DOMAINID_T domainId,
				     const char *contentfilteredtopic_name,
                  const char *topic_name,
                  const char *type_name,
                  DataReaderListener *listener,
                  const _DATA_READER_QOS *qos,
				  const string filter_expression,
				  _STRING_SEQ parameters) {
    DomainParticipant *domainParticipant = DomainManagement::GetInstance()->ParticipantGet(domainId);
    if (domainParticipant == NULL) {
        return NULL;
    }

    Topic *topic = domainParticipant->CreateTopic(topic_name, type_name);
    if (topic == NULL) {
        return NULL;
    }

    ContentFilteredTopic *contentfilteredtopic = domainParticipant->Create_ContentFilteredTopic(contentfilteredtopic_name, filter_expression, topic, parameters);
    if (contentfilteredtopic == NULL) {
        return NULL;
    }
    DataReader *newDataReader = domainParticipant->CreateDataReader(
        contentfilteredtopic, listener, qos, STATUS_MASK_ALL);
	   if(newDataReader != NULL)
       newDataReader->AppSet(componentName);

    return newDataReader;
}

//退出数据域
inline _RETURNCODE_T DomainRelease(_DOMAINID_T domainId) {
    return DomainManagement::GetInstance()->DomainRelease(domainId);
}

#endif
