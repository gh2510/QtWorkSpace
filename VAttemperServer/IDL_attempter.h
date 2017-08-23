// Don't modify this file as it will be overwritten.
//
#include "dds/Cdr.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/MD5.h"

#ifndef IDL_attempter_hh
#define IDL_attempter_hh

#ifndef V_PageAttemper_defined
#define V_PageAttemper_defined

struct V_PageAttemper {
  V_PageAttemper()
  {
        }

  V_PageAttemper(const V_PageAttemper  &IDL_s);

  ~V_PageAttemper()
  {
  }

  V_PageAttemper& operator= (const V_PageAttemper &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  short pageId;
  char pageName[40];
  char IP[15];
  
};

#endif




#endif /*IDL_attempter_hh */
