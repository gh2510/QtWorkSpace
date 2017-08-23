#include "IDL_DataWriter.h"

TimeStateInfoDataWriter::TimeStateInfoDataWriter(
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

TimeStateInfoDataWriter::~TimeStateInfoDataWriter() {
}

_RETURNCODE_T TimeStateInfoDataWriter::AppSet(const char *appName) {
    if (appName == NULL) {
        return RETURNCODE_APPSET_FAILED;
    }
    m_appName = const_cast<char*>(appName);
#ifdef _APP_FAULT_TOLERANT_
    this->faultTolerantSet();
#endif
    return RETURNCODE_OK;
}

#ifdef _APP_FAULT_TOLERANT_
_RETURNCODE_T TimeStateInfoDataWriter::faultTolerantSet() {
    int ft = FT_SendJudge(m_appName);
    if (ft != -301) {
        m_ftEnable = true;
    }
    return RETURNCODE_OK;
}
#endif

#ifdef _APP_FAULT_TOLERANT_
bool TimeStateInfoDataWriter::faultTolerantJudge() {
    if (m_ftEnable) {
        int ft = FT_SendJudge(m_appName);
        if (ft == 1) {
            return true;
        }
    }
    return false;
}
#endif

void* TimeStateInfoDataWriter::narrow_helper(long type_const) {
    void *rval = NULL; 
    if (type_const == (long)type_id) 
        rval = this; 
    return rval; 
}

TimeStateInfoDataWriter* TimeStateInfoDataWriter::Narrow(DataWriter* dataWriter) {
    if (!dataWriter) {
        return NULL;
    }

    TimeStateInfoDataWriter *aTimeStateInfoDataWriter = (TimeStateInfoDataWriter *)dataWriter->narrow_helper((long)&TimeStateInfoDataWriter::type_id);
    return aTimeStateInfoDataWriter;
}

_RETURNCODE_T TimeStateInfoDataWriter::Write(TimeStateInfo& data){
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
#ifdef _APP_FAULT_TOLERANT_
    }
#endif
    if (CDRData) {
        delete CDRData;
    }
    return ret;
}

