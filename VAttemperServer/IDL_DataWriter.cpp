#include "IDL_DataWriter.h"

V_PageAttemperDataWriter::V_PageAttemperDataWriter(
               Topic* topic,
               const _DATA_WRITER_QOS *qos,
               DataWriterListener* listener,
               _STATUS_MASK mask,
               Publisher* publisher,
               unsigned long cacheLength) :
       DataWriter(topic, qos, listener, mask, publisher, cacheLength) {
#ifdef _APP_FAULT_TOLERANT_
    m_ftEnable = true;
#endif
    m_appName = NULL;
}

V_PageAttemperDataWriter::~V_PageAttemperDataWriter() {
#ifdef _APP_SERVICE_MONITOR_
    this->MonitorService(STOPPUBLISH);
#endif
}

_RETURNCODE_T V_PageAttemperDataWriter::AppSet(const char *appName) {
    if (appName == NULL) {
        return RETURNCODE_APPSET_FAILED;
    }
    m_appName = const_cast<char*>(appName);
#ifdef _APP_FAULT_TOLERANT_
    this->faultTolerantSet();
#endif
#ifdef _APP_SERVICE_MONITOR_
    this->MonitorService(PUBLISHED);
#endif
    return RETURNCODE_OK;
}

#ifdef _APP_FAULT_TOLERANT_
_RETURNCODE_T V_PageAttemperDataWriter::faultTolerantSet() {
    int ft = FT_SendJudge(m_appName);
    if (ft != -301) {
        m_ftEnable = true;
    }
    return RETURNCODE_OK;
}
#endif

#ifdef _APP_FAULT_TOLERANT_
bool V_PageAttemperDataWriter::faultTolerantJudge() {
    if (m_ftEnable) {
        int ft = FT_SendJudge(m_appName);
        if (ft == 1) {
            return true;
        }
    }
    return false;
}
#endif

#ifdef _APP_DATA_RECORD_
_RETURNCODE_T V_PageAttemperDataWriter::RecordData(_SEQUENCE_NUM seqNum) {
    if (m_appName == NULL) {
        return RETURNCODE_APP_NOTSET;
    }
    unsigned long domainId = this->GetDomainParticipant()->GetDomainId()
;    string topic_name = this->m_pRelatedTopic->Get_Name();
    char *topicName = const_cast<char*>(topic_name.c_str());
    _TIME_T time = DomainParticipant::GetCurrentTime();
    _TIMESTAMP_T timestamp;
    timestamp.lSecond = time.lSecond;
    timestamp.ulNanosec = time.ulNanosec;
    if(this->GetDomainParticipant()->GetRecordAgent() == 1) return this->GetDomainParticipant()->GetMonitorRecordAgent()->SendRecordInfo(domainId,m_appName, topicName, timestamp, SEND, seqNum);
    return RETURNCODE_OK;
}
#endif

#ifdef _APP_SERVICE_MONITOR_
_RETURNCODE_T V_PageAttemperDataWriter::MonitorService(_TOPIC_STATUS status) {
    if (m_appName == NULL) {
        return RETURNCODE_APP_NOTSET;
    }
    unsigned long domainId = this->GetDomainParticipant()->GetDomainId();
    string topic_name = this->m_pRelatedTopic->Get_Name();
    string type_name = this->m_pRelatedTopic->Get_Type_Name();
    char *topicName = const_cast<char*>(topic_name.c_str());
    char *typeName = const_cast<char*>(type_name.c_str());
	   ValueCode *vc = new ValueCode();
    vc->Set_Typecode(tc_V_PageAttemper);
    string type_Code = vc->Output_Type();
    char* typeCode = const_cast<char*>(type_Code.c_str());
    if(this->GetDomainParticipant()->GetMonitorAgent() == 1)
        return this->GetDomainParticipant()->GetMonitorRecordAgent()->SendTopicInfo(m_appName, topicName, typeName, typeCode, domainId, status);
    return RETURNCODE_OK;
}
#endif

void* V_PageAttemperDataWriter::narrow_helper(long type_const) {
    void *rval = NULL; 
    if (type_const == (long)type_id) 
        rval = this; 
    return rval; 
}

V_PageAttemperDataWriter* V_PageAttemperDataWriter::Narrow(DataWriter* dataWriter) {
    if (!dataWriter) {
        return NULL;
    }

    V_PageAttemperDataWriter *aV_PageAttemperDataWriter = (V_PageAttemperDataWriter *)dataWriter->narrow_helper((long)&V_PageAttemperDataWriter::type_id);
    return aV_PageAttemperDataWriter;
}

_RETURNCODE_T V_PageAttemperDataWriter::Write(V_PageAttemper& data){
    char *buf = new char[DEFAULT_CDRSIZE];
    CDR* CDRData = NULL;
    _SEQUENCE_NUMBER_T seqNum;
    _RETURNCODE_T ret = RETURNCODE_OK;
    CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
    data.Marshal(CDRData);
    char* myData = CDRData->GetBufferPtr();
    int typeSize = CDRData->GetContentLen();
    _CACHE_CHANGE* myCacheChange = NULL;
#ifdef _APP_FAULT_TOLERANT_
    if (this->faultTolerantJudge()) {
#endif
        ret = this->WriteToCache(myData, typeSize, ALIVE, HANDLE_NIL, seqNum);
#ifdef _APP_DATA_RECORD_
        if (ret == RETURNCODE_OK) {
            _SEQUENCE_NUM seqNumber;
            seqNumber.lHigh = seqNum.lHigh;
            seqNumber.ulLow = seqNum.ulLow;
            this->RecordData(seqNumber);
        }
#endif
#ifdef _APP_FAULT_TOLERANT_
    }
#endif
    if (CDRData) {
        delete CDRData;
    }
    return ret;
}

