#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_Header.h"
#include "IDL_HeaderTC.h"
#include "dds/ValueCode.h"
#include "dds/TypeCode.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"
using std::string;

typedef vector<TimeStateInfo> TimeStateInfoSeq;

class TimeStateInfoDataReader : public DataReader {
public:
    TimeStateInfoDataReader(TopicDescription* topic,
                    const _DATA_READER_QOS *qos,
                    DataReaderListener* listener,
                    _STATUS_MASK mask,
                    Subscriber* subscriber,
                    unsigned long cacheLength);

    ~TimeStateInfoDataReader();

    _RETURNCODE_T AppSet(const char *appName);

    static int type_id() { return 0; }

    void* narrow_helper(long type_const);

    _RETURNCODE_T read(TimeStateInfoSeq& receivedDataSeq, long maxSamples);
    static TimeStateInfoDataReader* Narrow(DataReader* dataReader);

private:
    char *m_appName;

public:
    _RETURNCODE_T Read_Next_Sample(TimeStateInfo& receivedData);

};

#endif
