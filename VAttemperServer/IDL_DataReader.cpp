#include "IDL_DataReader.h"

V_PageAttemperDataReader::V_PageAttemperDataReader(
               TopicDescription* topic,
               const _DATA_READER_QOS *qos,
               DataReaderListener* listener,
               _STATUS_MASK mask,
               Subscriber* subscriber,
               unsigned long cacheLength) :
       DataReader(topic, qos, listener, mask, subscriber, cacheLength) {
    m_appName = NULL;
}

V_PageAttemperDataReader::~V_PageAttemperDataReader() {
#ifdef _APP_SERVICE_MONITOR_
    this->MonitorService(STOPSUBSCRIBE);
#endif
}

_RETURNCODE_T V_PageAttemperDataReader::AppSet(const char *appName) {
    if (appName == NULL) {
        return RETURNCODE_APPSET_FAILED;
    }
    m_appName = const_cast<char*>(appName);
#ifdef _APP_SERVICE_MONITOR_
    this->MonitorService(SUBSCRIBED);
#endif
    return RETURNCODE_OK;
}

#ifdef _APP_DATA_RECORD_
_RETURNCODE_T V_PageAttemperDataReader::RecordData(_SEQUENCE_NUM seqNum) {
    if (m_appName == NULL) {
        return RETURNCODE_APP_NOTSET;
    }
    unsigned long domainId = this->GetDomainParticipant()->GetDomainId();
    string topic_name = this->m_pRelatedTopic->Get_Name();
    char *topicName = const_cast<char*>(topic_name.c_str());
    _TIME_T time = DomainParticipant::GetCurrentTime();
    _TIMESTAMP_T timestamp;
    timestamp.lSecond = time.lSecond;
    timestamp.ulNanosec = time.ulNanosec;
    if(this->GetDomainParticipant()->GetRecordAgent() == 1) return this->GetDomainParticipant()->GetMonitorRecordAgent()->SendRecordInfo(domainId, m_appName, topicName, timestamp, RECEIVE, seqNum);
    return RETURNCODE_OK;
}
#endif

#ifdef _APP_SERVICE_MONITOR_
_RETURNCODE_T V_PageAttemperDataReader::MonitorService(_TOPIC_STATUS status) {
    if (m_appName == NULL) {
        return RETURNCODE_APP_NOTSET;
    }
    unsigned long domainId = this->GetDomainParticipant()->GetDomainId();
    string topic_name = this->m_pRelatedTopic->Get_Name();
    string type_name = this->m_pRelatedTopic->Get_Type_Name();
    char *topicName = const_cast<char*>(topic_name.c_str());
    char* typeName = const_cast<char*>(type_name.c_str());
	   ValueCode *vc = new ValueCode();
    vc->Set_Typecode(tc_V_PageAttemper);
    string type_Code = vc->Output_Type();
    char* typeCode = const_cast<char*>(type_Code.c_str());
    if(this->GetDomainParticipant()->GetMonitorAgent() == 1)
        return this->GetDomainParticipant()->GetMonitorRecordAgent()->SendTopicInfo(m_appName,topicName, typeName, typeCode, domainId, status);
    return RETURNCODE_OK;
}
#endif

void* V_PageAttemperDataReader::narrow_helper(long type_const) {
    void *rval = NULL; 
    if (type_const == (long)type_id) 
        rval = this; 
    return rval; 
}

V_PageAttemperDataReader* V_PageAttemperDataReader::Narrow(DataReader* dataReader) {
    if (!dataReader) { return NULL; }
    V_PageAttemperDataReader *aV_PageAttemperDataReader = (V_PageAttemperDataReader *)dataReader->narrow_helper((long)&V_PageAttemperDataReader::type_id);
    return aV_PageAttemperDataReader;
}

_RETURNCODE_T V_PageAttemperDataReader::Read_Next_Sample(V_PageAttemper& receivedData) {
    char* myDataValue = NULL;
    unsigned long size;
    _SEQUENCE_NUMBER_T seqNum;
    _RETURNCODE_T ret = RETURNCODE_OK;
    _INSTANCE_HANDLE_T handle;
    _CHANGE_KIND_T Kind;
    ret = this->ReadCache(myDataValue,size,handle,Kind,seqNum);
    if (ret == RETURNCODE_OK) {
        CDR* CDRData = NULL;
        CDRData = new CDR((unsigned char *)myDataValue, size, MY_BYTE_SEX, 1);
        receivedData.UnMarshal(CDRData);
        if (CDRData) {
            delete CDRData;
        }
#ifdef _APP_DATA_RECORD_
        _SEQUENCE_NUM seqNumber;
        seqNumber.lHigh = seqNum.lHigh;
        seqNumber.ulLow = seqNum.ulLow;
        this->RecordData(seqNumber);
#endif
    }
    return ret;
}

