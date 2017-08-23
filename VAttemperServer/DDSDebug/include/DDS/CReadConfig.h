/************************************************************
** 文件名：CReadConfig.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2011-01-22
** 修改人：无
** 日  期：无
** 描  述：CReadConfig头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
/*样例
#comment    pLine

#pSection    begin
[section_1]
key1 = value1;
key2   =   value2;

[section_2]
key1   =   value3;
key2   =   value4;

*/

#ifndef _CREADCONFIG_H_INCLUDED_
#define _CREADCONFIG_H_INCLUDED_

#define CFG_LINE 1024
#define RETURNCODE_READ_CONFG_FAILED 1 /*读配置文件失败*/
#define RETURNCODE_NO_FILE 2 /*没找到或没打开配置文件*/
#define RETURNCODE_NOT_FIND 3 /*在配置文件中没找到相应的域、键名*/
#define RETURNCODE_IS_REMARK 4 /*注释行*/
#define RETURNCODE_READLINE_FAILED 5 /*读取一行失败*/
#define RETURNCODE_NOT_SECTION 6 /*不是域名所在*/
#define RETURNCODE_NO_EQUAL 7 /*没有等号*/

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ReturnCode.h"

class CReadConfig 
{
public: 
    CReadConfig() {}
    virtual ~CReadConfig() {}

    //从文件中读出指定域名指定键名的字符串类型键值
    _RETURNCODE_T GetConfigStr(const char* pSection, const char* pKeyName, char* pKeyValue, unsigned int ulLength,const char* pFilename);
    //从文件中读出指定域名指定键名的整型键值
    _RETURNCODE_T GetConfigInt(const char* pSection, const char* pKeyName, int* pKeyValue, const char* pFilename);

private:
    //从文件中读一行
    _RETURNCODE_T Readline(char* pLine, FILE* pStream);
    //是否是注释行行
    _RETURNCODE_T IsRemark(const char* pLine);
    //获取域名
    _RETURNCODE_T GetSection(const char* pLine, char* pSection);
    //获取键值
    _RETURNCODE_T GetKey(const char* pLine, char* pKeyName, char* pKeyValue);
};

#endif
