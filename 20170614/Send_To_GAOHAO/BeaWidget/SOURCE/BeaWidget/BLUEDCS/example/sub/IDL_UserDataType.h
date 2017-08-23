// Don't modify this file as it will be overwritten.
//
#include "dds/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/MD5.h"

#ifndef IDL_UserDataType_hh
#define IDL_UserDataType_hh

#ifndef myData_defined
#define myData_defined

struct myData {
  myData(){}

  myData(const myData  &IDL_s);

  ~myData(){}

  myData& operator= (const myData &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  short x;
  short y;
  char* color;
  
};

#endif




#endif /*IDL_UserDataType_hh */
