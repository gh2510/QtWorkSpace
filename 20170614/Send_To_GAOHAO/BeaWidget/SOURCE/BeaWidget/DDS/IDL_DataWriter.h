#ifndef _IDL_DATAWRITER_H_INCLUDED_
#define _IDL_DATAWRITER_H_INCLUDED_
#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_Header.h"
#include "IDL_HeaderTC.h"
#include "dds/ValueCode.h"
#include "dds/TypeCode.h"
#include "dds/DataWriter.h"
#include "dds/Publisher.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"
class Topic;
class DataWriterListener;
class Publisher;

class TimeStateInfoDataWriter : public DataWriter {
public:
    TimeStateInfoDataWriter(Topic* topic,
               const _DATA_WRITER_QOS   *qos,
               DataWriterListener* listener,
               _STATUS_MASK mask,
               Publisher* publisher,
               unsigned long cacheLength);
    ~TimeStateInfoDataWriter();

    _RETURNCODE_T AppSet(const char *appName);

#ifdef _APP_FAULT_TOLERANT_
    _RETURNCODE_T faultTolerantSet();
#endif

#ifdef _APP_FAULT_TOLERANT_
    bool faultTolerantJudge();
#endif

    static int type_id() { return 0; }

    void* narrow_helper(long type_const);

    static TimeStateInfoDataWriter* Narrow(DataWriter* dataWriter);

private:
#ifdef _APP_FAULT_TOLERANT_
    bool m_ftEnable;
#endif

    char *m_appName;

public:
    _RETURNCODE_T Write(TimeStateInfo& data);

};

#endif
