/************************************************************
** �ļ�����Filter.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-07-05
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Filterͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef FILTER_H
#define FILTER_H

#include <string.h>
#include "dds/cdr.h"

#include "BasicTypes.h"
#include "dds/valuecode.h"
#include "dds/gst.h"
#include "dds/bison1.hpp"
#include <iostream>

typedef list<_ANY_DATD> Parameterlist; 

class Filter
{
public:
	Filter(const char* pExpression);//��expression�������﷨���ĳ�ʼ����
	~Filter();//�����﷨��
	bool EvaluateData();//�����Ƿ�Ӧ�ù��˵�ǰ����
	//��contentfilteredtopic��set�������Ѿ�ʵ���˶���m_pFilter��parameter���޸�
	Parameterlist Parameters;//parameters����Ҳ�洢������
	void Set_Typecode(TypeCode cTypecode);
	void Set_Cdr(CDR *pStream);
	
private:
	struct _AST* pGst;//�洢���ɵ��﷨���ĸ���
	bool BuildGrammaTree(const char* pExpression);//��ΪFilter��˽�к���ȷ����װ��
	int Yyparse(void);//ȷ����װ��
	_ANY_DATD Eval(struct _AST* pAst,Parameterlist Parameters);//Ϊ�����ִ������ͼ���һ��int�͵Ĳ���
	int iWrongkind;//��¼�ڹ��˹����г��ֵĴ���
	ValueCode* pVc;
};
#endif