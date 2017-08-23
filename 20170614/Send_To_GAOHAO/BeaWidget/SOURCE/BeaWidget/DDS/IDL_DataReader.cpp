#include "IDL_DataReader.h"

TimeStateInfoDataReader::TimeStateInfoDataReader(
               TopicDescription* topic,
               const _DATA_READER_QOS *qos,
               DataReaderListener* listener,
               _STATUS_MASK mask,
               Subscriber* subscriber,
               unsigned long cacheLength) :
       DataReader(topic, qos, listener, mask, subscriber, cacheLength) {
    m_appName = NULL;
}

TimeStateInfoDataReader::~TimeStateInfoDataReader() {
}

_RETURNCODE_T TimeStateInfoDataReader::AppSet(const char *appName) {
    if (appName == NULL) {
        return RETURNCODE_APPSET_FAILED;
    }
    m_appName = const_cast<char*>(appName);
    return RETURNCODE_OK;
}

void* TimeStateInfoDataReader::narrow_helper(long type_const) {
    void *rval = NULL; 
    if (type_const == (long)type_id) 
        rval = this; 
    return rval; 
}

TimeStateInfoDataReader* TimeStateInfoDataReader::Narrow(DataReader* dataReader) {
    if (!dataReader) { return NULL; }
    TimeStateInfoDataReader *aTimeStateInfoDataReader = (TimeStateInfoDataReader *)dataReader->narrow_helper((long)&TimeStateInfoDataReader::type_id);
    return aTimeStateInfoDataReader;
}

_RETURNCODE_T TimeStateInfoDataReader::Read_Next_Sample(TimeStateInfo& receivedData) {
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
    }
    return ret;
}

