#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_

#include <string>
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_attempter.h"
#include "IDL_attempterTC.h"
#include "dds/TypeSupport.h"
#include "dds/DomainParticipant.h"
class DomainParticipant;

#include "IDL_Agent.h"
class V_PageAttemperTypeSupport : public TypeSupport {
public:
    static _RETURNCODE_T register_type(DomainParticipant* domainParticipant, string typeName) {
        Agent *newAgent = NULL;
        try {
            newAgent = new V_PageAttemperAgent(domainParticipant, typeName);
        }
        catch (_RETURNCODE_T &ret) { 
            if (ret == RETURNCODE_REGISTER_TYPE_EXISTED) { delete newAgent; } 
        }
        domainParticipant->InsertRegisteredTypeCode(&tc_V_PageAttemper, typeName);
        return RETURNCODE_OK;
    }

    static char* get_type_name() { return "V_PageAttemper";}
};

#endif
