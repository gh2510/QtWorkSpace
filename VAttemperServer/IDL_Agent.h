#ifndef _IDL_AGENT_H_INCLUDED_
#define _IDL_AGENT_H_INCLUDED_

#include "dds/Agent.h"
#include "IDL_attempter.h"
class DataWriter;
class DataReader;
class DomainParticipant;
class Topic;
class DataWriterListener;
class DataReaderListener;
class Publisher;
class Subscriber;

#include "IDL_DataReader.h"
#include "IDL_DataWriter.h"

class V_PageAttemperAgent : public Agent {
public:
    V_PageAttemperAgent(DomainParticipant *domainParticipant, string name)  :
        Agent(domainParticipant, name) { }
    ~V_PageAttemperAgent() {}

    DataWriter *CreateDataWriter(Topic* topic,
                                 const _DATA_WRITER_QOS *qos,
                                 DataWriterListener* listener,
                                 _STATUS_MASK mask,
                                 Publisher* publisher,
                                 unsigned long cacheLength) {
        DataWriter *newDataWriter = new V_PageAttemperDataWriter(topic, qos, listener, mask, publisher, cacheLength);
        return newDataWriter;
    }

    DataReader *CreateDataReader(TopicDescription* topic,
                                 const _DATA_READER_QOS *qos,
                                 DataReaderListener* listener,
                                 _STATUS_MASK mask,
                                 Subscriber* subscriber,
                                 unsigned long cacheLength) {
        DataReader *newDataReader = new V_PageAttemperDataReader(topic, qos, listener, mask, subscriber, cacheLength);
        return newDataReader;
    }

};

#endif
