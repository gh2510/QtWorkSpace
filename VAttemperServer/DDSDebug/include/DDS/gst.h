/************************************************************
** �ļ�����gst.h
** Copyright (c) 2011-2012 �й�������ҵϵͳ�����о�Ժ
** �����ˣ�����<635584332@qq.com>
** ��  �ڣ�2012-07-05
** �޸��ˣ���
** ��  �ڣ���
** ��  ����gstͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef GST_H
#define GST_H


#include "dds/bison1.hpp"

#include "dds/typecode.h"

#include "dds/CDR.h"

#include "dds/valuecode.h"

enum _NODE_TYPE {NL,FID,CID,PID};//ö�����ͷ�Ҷ��id�ͷ�id
//enum TCkind {tc_char,tc_bool,tc_int,tc_float};//��ʱ����typecode��ʾ����

#define MAX_STRING_LEN 50 //�ַ�������󳤶�


//�����������е�_INDEX_STRUCT
struct _INDEX_STRUCT
{
	int iNum;//[]�е�����
	_INDEX_STRUCT* pNext;//��Ӧ[][]...�������
};
//



/////ͳһ��ʾ��fieldnamepart����
struct _FIELD_NAME_PART
{
	char* pName;//�洢id��Name��:a[]�е�a
	_INDEX_STRUCT* pIndexpart;//�洢id��������:a[]�е�[]
	_FIELD_NAME_PART* pNext;//��Ӧ����a.b�������
};
/////

struct _AST
{
	_NODE_TYPE Nodetype;//�ڵ����ͣ���ʾ��Ҷ�ڵ㻹�Ƿ�Ҷ�ڵ�
	int iOptype;//��ʾ����ڵ��������������
	struct _AST *pl;
	struct _AST *pr;
};


//����ͳһ�����ݽṹ_ANY_DATD
//�����������ԣ�Kind��pValue
//Kind��ʾpValue������
//pValueΪ����char*��ʽ�洢����ֵ
struct _ANY_DATD
{
	//Kind����TCKIND����
	_TC_KIND Kind;
	char* pValue;
};
struct _END_NODE_CI
{
	_NODE_TYPE Nodetype;//�����ڵ�����
	_ANY_DATD Data;//��id�ڵ�洢��������Ϣ
};

//id�ڵ�
struct _END_NODE_I
{
	_NODE_TYPE Nodetype;//�����ڵ�����
	//Name���Ա�ʾid���ڲ�ѯ�����ֵ
	//char* pName;//pNameָ��һ��Ҫע���ָ������
	//֮��ͳһʹ��FieldName�ṹ������
	_FIELD_NAME_PART* pId;//��_FIELD_NAME_PART�ṹͳһ��ʾa,a[],a.b,a[].b[]�����ݽṹ
};


//����parameter�нڵ�
struct _END_NODE_P
{
	_NODE_TYPE Nodetype;//�����ڵ�����
	//��������int��ʾ�����еĵڼ���
	int iIndex;//�����еĵڼ���
};

struct _AST* NewEndNodeCI(char* pData,_TC_KIND Kind);
struct _AST* NewEndNodeI(_FIELD_NAME_PART* pName);
struct _AST* NewEndNodeP(int iIndex);//����EndNodeP���ս��
struct _AST* NewAstNl(int iOptype,struct _AST* pl,struct _AST* pr);//iOptype�������������
//_ANY_DATD eval(struct _AST* a,ValueCode* pVc,_ANY_DATD[]);//�����﷨����б����Լ�����
//���ڽ�eval�Ĳ�����Ϊ����root,valuecode,parameter


//extern ValueCode* pVc;//��ѯ������ʵ��



////////����indexpart��NewIndexpart����
struct _INDEX_STRUCT* NewIndexpart(int iNum);//ֻҪ���֣�pNext�ڹ�Լ��ʱ���ٴ���
//

////�����ǽ���_FIELD_NAME_PART���ֵĺ���
struct _FIELD_NAME_PART* NewFieldNamePart(char* pName,struct _INDEX_STRUCT* pIndex);//���������id,index.
////



int EditDistance(const char* pSource,const char* pTarget);//����༭����

//////���һ����������������ȫ�ֱ���
extern struct _AST* pRoot;

///index����ר��
extern struct _INDEX_STRUCT* pIndextestnode;


#endif