// Don't modify this file as it will be overwritten.
//


#ifndef IDL_HeaderTC_hh
#define IDL_HeaderTC_hh

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

static long oc_TimeStateInfo [] = {
  0,
  BIG_ENDIAN_LONG (22),
  MAKE_BIG_LONG ('I', 'D', 'L', ':'),
  MAKE_BIG_LONG ('T', 'i', 'm', 'e'),
  MAKE_BIG_LONG ('S', 't', 'a', 't'),
  MAKE_BIG_LONG ('e', 'I', 'n', 'f'),
  MAKE_BIG_LONG ('o', ':', '1', '.'),
  MAKE_BIG_LONG ('0',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (14),
  MAKE_BIG_LONG ('T', 'i', 'm', 'e'),
  MAKE_BIG_LONG ('S', 't', 'a', 't'),
  MAKE_BIG_LONG ('e', 'I', 'n', 'f'),
  MAKE_BIG_LONG ('o',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (12),
  BIG_ENDIAN_LONG (9),
  MAKE_BIG_LONG ('i', 'n', 'f', 'o'),
  MAKE_BIG_LONG ('F', 'l', 'a', 'g'),
  0,
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (15),
  MAKE_BIG_LONG ('i', 'n', 'f', 'o'),
  MAKE_BIG_LONG ('E', 'x', 't', 'e'),
  MAKE_BIG_LONG ('n', 'd', 'F', 'l'),
  MAKE_BIG_LONG ('a', 'g',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_ushort),
  BIG_ENDIAN_LONG (10),
  MAKE_BIG_LONG ('i', 'n', 'f', 'o'),
  MAKE_BIG_LONG ('I', 'n', 'd', 'e'),
  MAKE_BIG_LONG ('x',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_ushort),
  BIG_ENDIAN_LONG (8),
  MAKE_BIG_LONG ('i', 'n', 'f', 'o'),
  MAKE_BIG_LONG ('L', 'e', 'n',  0 ),
  BIG_ENDIAN_LONG (tk_ushort),
  BIG_ENDIAN_LONG (7),
  MAKE_BIG_LONG ('u', 'c', 'h', 'S'),
  MAKE_BIG_LONG ('e', 'c',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (7),
  MAKE_BIG_LONG ('u', 'c', 'h', 'M'),
  MAKE_BIG_LONG ('i', 'n',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (8),
  MAKE_BIG_LONG ('u', 'c', 'h', 'H'),
  MAKE_BIG_LONG ('o', 'u', 'r',  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (7),
  MAKE_BIG_LONG ('u', 'c', 'h', 'D'),
  MAKE_BIG_LONG ('a', 'y',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (9),
  MAKE_BIG_LONG ('u', 'c', 'h', 'M'),
  MAKE_BIG_LONG ('o', 'n', 't', 'h'),
  0,
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (12),
  MAKE_BIG_LONG ('u', 'c', 'h', 'Y'),
  MAKE_BIG_LONG ('e', 'a', 'r', 'H'),
  MAKE_BIG_LONG ('i', 'g', 'h',  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (11),
  MAKE_BIG_LONG ('u', 'c', 'h', 'Y'),
  MAKE_BIG_LONG ('e', 'a', 'r', 'L'),
  MAKE_BIG_LONG ('o', 'w',  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_octet),
  BIG_ENDIAN_LONG (6),
  MAKE_BIG_LONG ('c', 'h', 'e', 'c'),
  MAKE_BIG_LONG ('k',  0 ,  0 ,  0 ),
  BIG_ENDIAN_LONG (tk_octet),
};

static TypeCode tc_TimeStateInfo = TypeCode(tk_struct, sizeof(oc_TimeStateInfo), (unsigned char *)&oc_TimeStateInfo);





#endif /*IDL_HeaderTC_hh */
