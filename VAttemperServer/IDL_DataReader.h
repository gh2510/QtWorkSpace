#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_attempter.h"
#include "IDL_attempterTC.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/ContentFilteredTopic.h"
#include "rtps/Filter.h"
#include "dds/CDR.h"
#include "APP/APP.h"
using std::string;

typedef vector<V_PageAttemper> V_PageAttemperSeq;

class V_PageAttemperDataReader : public DataReader {
public:
    V_PageAttemperDataReader(TopicDescription* topic,
                    const _DATA_READER_QOS *qos,
                    DataReaderListener* listener,
                    _STATUS_MASK mask,
                    Subscriber* subscriber,
                    unsigned long cacheLength);

    ~V_PageAttemperDataReader();

    _RETURNCODE_T AppSet(const char *appName);

#ifdef _APP_DATA_RECORD_
    _RETURNCODE_T RecordData(_SEQUENCE_NUM seqNum);
#endif

#ifdef _APP_SERVICE_MONITOR_
    _RETURNCODE_T MonitorService(_TOPIC_STATUS status);
#endif

    static int type_id() { return 0; }

    void* narrow_helper(long type_const);

    _RETURNCODE_T read(V_PageAttemperSeq& receivedDataSeq, long maxSamples);
    static V_PageAttemperDataReader* Narrow(DataReader* dataReader);

private:
    char *m_appName;

public:
    _RETURNCODE_T Read_Next_Sample(V_PageAttemper& receivedData);

};

#endif
