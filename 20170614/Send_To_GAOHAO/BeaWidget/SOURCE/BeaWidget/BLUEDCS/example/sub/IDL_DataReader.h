#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_UserDataType.h"
#include "IDL_UserDataTypeTC.h"
#include "dds/ValueCode.h"
#include "dds/TypeCode.h"
#include "dds/DataReader.h"
#include "dds/Subscriber.h"
#include "dds/DomainParticipant.h"
#include "dds/Topic.h"
#include "dds/CDR.h"
#include "APP/APP.h"
using std::string;

typedef vector<myData> myDataSeq;

class myDataDataReader : public DataReader {
public:
    myDataDataReader(TopicDescription* topic,
                    const _DATA_READER_QOS *qos,
                    DataReaderListener* listener,
                    _STATUS_MASK mask,
                    Subscriber* subscriber,
                    unsigned long cacheLength);

    ~myDataDataReader();

    _RETURNCODE_T AppSet(const char *appName);

    static int type_id() { return 0; }

    void* narrow_helper(long type_const);

    _RETURNCODE_T read(myDataSeq& receivedDataSeq, long maxSamples);
    static myDataDataReader* Narrow(DataReader* dataReader);

private:
    char *m_appName;

public:
    _RETURNCODE_T Read_Next_Sample(myData& receivedData);

};

#endif
