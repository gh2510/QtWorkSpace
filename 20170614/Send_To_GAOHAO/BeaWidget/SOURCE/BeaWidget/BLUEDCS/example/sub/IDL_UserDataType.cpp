// Don't modify this file as it will be overwritten.
//
#include "IDL_UserDataType.h"

myData::myData(const myData &IDL_s){
  x = IDL_s.x;
  y = IDL_s.y;
  color = IDL_s.color;
}

myData& myData::operator= (const myData &IDL_s){
  if (this == &IDL_s) return *this;
  x = IDL_s.x;
  y = IDL_s.y;
  color = IDL_s.color;
  return *this;
}

void myData::Marshal(CDR *cdr) const {
  cdr->PutShort(x);
  cdr->PutShort(y);
  cdr->PutString(color);
}

void myData::UnMarshal(CDR *cdr){
  cdr->GetShort(x);
  cdr->GetShort(y);
  {
    char *IDL_str;
    cdr->GetString(IDL_str);
    if(color != NULL )
    {
        color = NULL;
    }
    color = IDL_str;
  }
}

