/**
 * @file MD5.h
 * @brief MD5头文件 计算MD5
 * @author Yangmeng<635584332@qq.com>
 * @version 0.1
 * @History
 *  1.创建于2011-08-25
 */

#ifndef _DDS_MD5_H_INCLUDED_
#define _DDS_MD5_H_INCLUDED_

#include "BasicTypes.h"

#ifdef __alpha
typedef unsigned int uint32;
#else
typedef unsigned long uint32;
#endif

#include <string.h> /* for memcpy() */

struct MD5Context {
    uint32 buf[4];
    uint32 bits[2];
    unsigned char in[64];
};

void MD5Init(struct MD5Context *context);
void MD5Update(struct MD5Context *context, unsigned char const *buf, unsigned len);
void MD5Final(unsigned char digest[16], struct MD5Context *context);
void MD5Transform(uint32 buf[4], uint32 const in[16]);
//计算字符串src的MD5
#if defined(VXWORKS) || defined(_DDS_LIB_FILE)
void computeMD5(char* src, unsigned len, unsigned char* result);
#else
DDS_DLL void computeMD5(char* src, unsigned len, unsigned char* result);
#endif
/*
 * This is needed to make RSAREF happy on some MS-DOS compilers.
 */
typedef struct MD5Context MD5_CTX;

#endif
