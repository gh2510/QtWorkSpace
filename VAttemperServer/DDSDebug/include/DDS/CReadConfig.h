/************************************************************
** �ļ�����CReadConfig.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2011-01-22
** �޸��ˣ���
** ��  �ڣ���
** ��  ����CReadConfigͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
/*����
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
#define RETURNCODE_READ_CONFG_FAILED 1 /*�������ļ�ʧ��*/
#define RETURNCODE_NO_FILE 2 /*û�ҵ���û�������ļ�*/
#define RETURNCODE_NOT_FIND 3 /*�������ļ���û�ҵ���Ӧ���򡢼���*/
#define RETURNCODE_IS_REMARK 4 /*ע����*/
#define RETURNCODE_READLINE_FAILED 5 /*��ȡһ��ʧ��*/
#define RETURNCODE_NOT_SECTION 6 /*������������*/
#define RETURNCODE_NO_EQUAL 7 /*û�еȺ�*/

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

    //���ļ��ж���ָ������ָ���������ַ������ͼ�ֵ
    _RETURNCODE_T GetConfigStr(const char* pSection, const char* pKeyName, char* pKeyValue, unsigned int ulLength,const char* pFilename);
    //���ļ��ж���ָ������ָ�����������ͼ�ֵ
    _RETURNCODE_T GetConfigInt(const char* pSection, const char* pKeyName, int* pKeyValue, const char* pFilename);

private:
    //���ļ��ж�һ��
    _RETURNCODE_T Readline(char* pLine, FILE* pStream);
    //�Ƿ���ע������
    _RETURNCODE_T IsRemark(const char* pLine);
    //��ȡ����
    _RETURNCODE_T GetSection(const char* pLine, char* pSection);
    //��ȡ��ֵ
    _RETURNCODE_T GetKey(const char* pLine, char* pKeyName, char* pKeyValue);
};

#endif
