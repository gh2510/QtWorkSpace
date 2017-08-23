#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_attempter.h"
#include "IDL_attempterTC.h"
#include "dds/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"
#include "DDS/ValueCode.h"
class Topic;
class DataWriterListener;
class Publisher;

class V_PageAttemperDataWriter : public DataWriter {
public:
    V_PageAttemperDataWriter(Topic* topic,
               const _DATA_WRITER_QOS   *qos,
               DataWriterListener* listener,
               _STATUS_MASK mask,
               Publisher* publisher,
               unsigned long cacheLength);
    ~V_PageAttemperDataWriter();

    _RETURNCODE_T AppSet(const char *appName);

#ifdef _APP_FAULT_TOLERANT_
    _RETURNCODE_T faultTolerantSet();
#endif

#ifdef _APP_FAULT_TOLERANT_
    bool faultTolerantJudge();
#endif

#ifdef _APP_DATA_RECORD_
    _RETURNCODE_T RecordData(_SEQUENCE_NUM seqNum);
#endif

#ifdef _APP_SERVICE_MONITOR_
    _RETURNCODE_T MonitorService(_TOPIC_STATUS status);
#endif

    static int type_id() { return 0; }

    void* narrow_helper(long type_const);

    static V_PageAttemperDataWriter* Narrow(DataWriter* dataWriter);

private:
#ifdef _APP_FAULT_TOLERANT_
    bool m_ftEnable;
#endif

    char *m_appName;

public:
    _RETURNCODE_T Write(V_PageAttemper& data);

};

#endif
