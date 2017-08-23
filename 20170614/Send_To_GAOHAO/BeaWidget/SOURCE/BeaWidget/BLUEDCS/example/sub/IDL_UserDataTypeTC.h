// Don't modify this file as it will be overwritten.
//


#ifndef IDL_UserDataTypeTC_hh
#define IDL_UserDataTypeTC_hh

#include "dds/TypeCode.h"
//	This file can only be used on current platform

#define ORBUS_LITTLE_ENDIAN

#if     defined (ORBUS_BIG_ENDIAN)
#       define  MAKE_BIG_LONG(a,b,c,d) \
            ((((a) & 0xff) << 24) | (((b) & 0xff) << 16) \
             | (((c) & 0xff) <<  8) | ((d) & 0xff))
#       define  BIG_ENDIAN_LONG(x)      (x)
#else   // ORBUS_LITTLE_ENDIAN
#       define  MAKE_BIG_LONG(a,b,c,d) \
            ((((d) & 0xff) << 24) | (((c) & 0xff) << 16) \
             | (((b) & 0xff) <<  8) | ((a) & 0xff))
#       define BYTE_FROM(n,integer)    (((integer)>>(8*(n)))&0xff)
#       define BIG_ENDIAN_LONG(integer) \
            MAKE_BIG_LONG (BYTE_FROM(3,integer), BYTE_FROM(2,integer),\
                BYTE_FROM(1,integer), BYTE_FROM(0,integer))
#endif

static long oc_myData [] = {
  0,
  BIG_ENDIAN_LONG (15),
  MAKE_BIG_LONG ('I', 'D', 'L', ':'),
  MAKE_BIG_LONG ('m', 'y', 'D', 'a'),
  MAKE_BIG_LONG ('t', 'a', ':', '1'),
  MAKE_BIG_LONG ('.', '0',  0 ,  0 ),
  BIG_ENDIAN_LONG (7),
  MAKE_BIG_LONG ('m', 'y', 'D', 'a'),
  MAKE_BIG_LONG ('t', 'a',  0 ,  0 ),
  BIG_ENDIAN_LONG (3),
  BIG_ENDIAN_LONG (2),
  MAKE_BIG_LONG ('x',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_short),
  BIG_ENDIAN_LONG (2),
  MAKE_BIG_LONG ('y',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_short),
  BIG_ENDIAN_LONG (6),
  MAKE_BIG_LONG ('c', 'o', 'l', 'o'),
  MAKE_BIG_LONG ('r',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_string),
  BIG_ENDIAN_LONG (0),
};

static TypeCode tc_myData = TypeCode(tk_struct, sizeof(oc_myData), (unsigned char *)&oc_myData);





#endif /*IDL_UserDataTypeTC_hh */
