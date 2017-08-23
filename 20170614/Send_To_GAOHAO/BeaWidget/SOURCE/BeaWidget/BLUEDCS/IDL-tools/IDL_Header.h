// Don't modify this file as it will be overwritten.
//
#include "dds/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "dds/MD5.h"

#ifndef IDL_Header_hh
#define IDL_Header_hh

#ifndef TimeStateInfo_defined
#define TimeStateInfo_defined

struct TimeStateInfo {
  TimeStateInfo(){}

  TimeStateInfo(const TimeStateInfo  &IDL_s);

  ~TimeStateInfo(){}

  TimeStateInfo& operator= (const TimeStateInfo &IDL_s);

  void Marshal(CDR *cdr) const;
  void UnMarshal(CDR *cdr);

  unsigned char infoFlag;
  unsigned short infoExtendFlag;
  unsigned short infoIndex;
  unsigned short infoLen;
  unsigned char uchSec;
  unsigned char uchMin;
  unsigned char uchHour;
  unsigned char uchDay;
  unsigned char uchMonth;
  unsigned char uchYearHigh;
  unsigned char uchYearLow;
  unsigned char check;
  
};

#endif




#endif /*IDL_Header_hh */
