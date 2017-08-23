// Don't modify this file as it will be overwritten.
//
#include "IDL_Header.h"

TimeStateInfo::TimeStateInfo(const TimeStateInfo &IDL_s){
  infoFlag = IDL_s.infoFlag;
  infoExtendFlag = IDL_s.infoExtendFlag;
  infoIndex = IDL_s.infoIndex;
  infoLen = IDL_s.infoLen;
  uchSec = IDL_s.uchSec;
  uchMin = IDL_s.uchMin;
  uchHour = IDL_s.uchHour;
  uchDay = IDL_s.uchDay;
  uchMonth = IDL_s.uchMonth;
  uchYearHigh = IDL_s.uchYearHigh;
  uchYearLow = IDL_s.uchYearLow;
  check = IDL_s.check;
}

TimeStateInfo& TimeStateInfo::operator= (const TimeStateInfo &IDL_s){
  if (this == &IDL_s) return *this;
  infoFlag = IDL_s.infoFlag;
  infoExtendFlag = IDL_s.infoExtendFlag;
  infoIndex = IDL_s.infoIndex;
  infoLen = IDL_s.infoLen;
  uchSec = IDL_s.uchSec;
  uchMin = IDL_s.uchMin;
  uchHour = IDL_s.uchHour;
  uchDay = IDL_s.uchDay;
  uchMonth = IDL_s.uchMonth;
  uchYearHigh = IDL_s.uchYearHigh;
  uchYearLow = IDL_s.uchYearLow;
  check = IDL_s.check;
  return *this;
}

void TimeStateInfo::Marshal(CDR *cdr) const {
  cdr->PutOctet(infoFlag);
  cdr->PutUShort(infoExtendFlag);
  cdr->PutUShort(infoIndex);
  cdr->PutUShort(infoLen);
  cdr->PutOctet(uchSec);
  cdr->PutOctet(uchMin);
  cdr->PutOctet(uchHour);
  cdr->PutOctet(uchDay);
  cdr->PutOctet(uchMonth);
  cdr->PutOctet(uchYearHigh);
  cdr->PutOctet(uchYearLow);
  cdr->PutOctet(check);
}

void TimeStateInfo::UnMarshal(CDR *cdr){
  cdr->GetOctet(infoFlag);
  cdr->GetUShort(infoExtendFlag);
  cdr->GetUShort(infoIndex);
  cdr->GetUShort(infoLen);
  cdr->GetOctet(uchSec);
  cdr->GetOctet(uchMin);
  cdr->GetOctet(uchHour);
  cdr->GetOctet(uchDay);
  cdr->GetOctet(uchMonth);
  cdr->GetOctet(uchYearHigh);
  cdr->GetOctet(uchYearLow);
  cdr->GetOctet(check);
}

