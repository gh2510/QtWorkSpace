#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_Header.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
class DomainParticipant;

#include "IDL_Agent.h"
class TimeStateInfoTypeSupport : public TypeSupport {
public:
    static _RETURNCODE_T register_type(DomainParticipant* domainParticipant, string typeName) {
        Agent *newAgent = NULL;
        try {
            newAgent = new TimeStateInfoAgent(domainParticipant, typeName);
        }
        catch (_RETURNCODE_T &ret) { 
            if (ret == RETURNCODE_REGISTER_TYPE_EXISTED) { delete newAgent; } 
        }
        domainParticipant->InsertRegisteredTypeCode(&tc_TimeStateInfo, typeName);
        return RETURNCODE_OK;
    }

    static char* get_type_name() { return "TimeStateInfo";}
};

#endif
