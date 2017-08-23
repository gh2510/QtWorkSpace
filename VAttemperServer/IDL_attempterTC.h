// Don't modify this file as it will be overwritten.
//


#ifndef IDL_attempterTC_hh
#define IDL_attempterTC_hh

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

static long oc_V_PageAttemper [] = {
  0,
  BIG_ENDIAN_LONG (23),
  MAKE_BIG_LONG ('I', 'D', 'L', ':'),
  MAKE_BIG_LONG ('V', '_', 'P', 'a'),
  MAKE_BIG_LONG ('g', 'e', 'A', 't'),
  MAKE_BIG_LONG ('t', 'e', 'm', 'p'),
  MAKE_BIG_LONG ('e', 'r', ':', '1'),
  MAKE_BIG_LONG ('.', '0',  0 ,  0 ),
  BIG_ENDIAN_LONG (15),
  MAKE_BIG_LONG ('V', '_', 'P', 'a'),
  MAKE_BIG_LONG ('g', 'e', 'A', 't'),
  MAKE_BIG_LONG ('t', 'e', 'm', 'p'),
  MAKE_BIG_LONG ('e', 'r',  0 ,  0 ),
  BIG_ENDIAN_LONG (3),
  BIG_ENDIAN_LONG (7),
  MAKE_BIG_LONG ('p', 'a', 'g', 'e'),
  MAKE_BIG_LONG ('I', 'd',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_short),
  BIG_ENDIAN_LONG (9),
  MAKE_BIG_LONG ('p', 'a', 'g', 'e'),
  MAKE_BIG_LONG ('N', 'a', 'm', 'e'),
  0,
  BIG_ENDIAN_LONG (tk_array),
  BIG_ENDIAN_LONG (12),
  BIG_ENDIAN_LONG (0),
  BIG_ENDIAN_LONG (tk_char),
  BIG_ENDIAN_LONG (40),
  BIG_ENDIAN_LONG (3),
  MAKE_BIG_LONG ('I', 'P',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_array),
  BIG_ENDIAN_LONG (12),
  BIG_ENDIAN_LONG (0),
  BIG_ENDIAN_LONG (tk_char),
  BIG_ENDIAN_LONG (15),
};

static TypeCode tc_V_PageAttemper = TypeCode(tk_struct, sizeof(oc_V_PageAttemper), (unsigned char *)&oc_V_PageAttemper);





#endif /*IDL_attempterTC_hh */
