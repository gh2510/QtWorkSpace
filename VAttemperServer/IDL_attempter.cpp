// Don't modify this file as it will be overwritten.
//
#include "IDL_attempter.h"

V_PageAttemper::V_PageAttemper(const V_PageAttemper &IDL_s){
  pageId = IDL_s.pageId;
  {
    char* IDL_elem1 = (char*)pageName;
    char* IDL_elem2 = (char*)IDL_s.pageName;
    for (unsigned long IDL_i = 0; IDL_i < 40; IDL_i++, IDL_elem1++,IDL_elem2++)
      *IDL_elem1 = *IDL_elem2;
  }
  {
    char* IDL_elem1 = (char*)IP;
    char* IDL_elem2 = (char*)IDL_s.IP;
    for (unsigned long IDL_i = 0; IDL_i < 15; IDL_i++, IDL_elem1++,IDL_elem2++)
      *IDL_elem1 = *IDL_elem2;
  }
}

V_PageAttemper& V_PageAttemper::operator= (const V_PageAttemper &IDL_s){
  if (this == &IDL_s) return *this;
  pageId = IDL_s.pageId;
  {
    char* IDL_elem1 = (char*)pageName;
    char* IDL_elem2 = (char*)IDL_s.pageName;
    for (unsigned long IDL_i = 0; IDL_i < 40; IDL_i++, IDL_elem1++,IDL_elem2++)
      *IDL_elem1 = *IDL_elem2;
  }
  {
    char* IDL_elem1 = (char*)IP;
    char* IDL_elem2 = (char*)IDL_s.IP;
    for (unsigned long IDL_i = 0; IDL_i < 15; IDL_i++, IDL_elem1++,IDL_elem2++)
      *IDL_elem1 = *IDL_elem2;
  }
  return *this;
}

void V_PageAttemper::Marshal(CDR *cdr) const {
  cdr->PutShort(pageId);
  {
    char *IDL_elem = (char *) pageName;
    for (unsigned long IDL_i = 0; IDL_i < 40; IDL_i++, IDL_elem++)
      cdr->PutChar((*IDL_elem));
  }

  {
    char *IDL_elem = (char *) IP;
    for (unsigned long IDL_i = 0; IDL_i < 15; IDL_i++, IDL_elem++)
      cdr->PutChar((*IDL_elem));
  }

}

void V_PageAttemper::UnMarshal(CDR *cdr){
  cdr->GetShort(pageId);
  {
    char *IDL_elem = (char *) pageName;
    for (unsigned long IDL_i = 0; IDL_i < 40; IDL_i++, IDL_elem++)
      cdr->GetChar((*IDL_elem));
  }

  {
    char *IDL_elem = (char *) IP;
    for (unsigned long IDL_i = 0; IDL_i < 15; IDL_i++, IDL_elem++)
      cdr->GetChar((*IDL_elem));
  }

}

