/************************************************************
** 文件名：Filter.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-07-05
** 修改人：无
** 日  期：无
** 描  述：Filter头文件
** 版  本：Version 0.1
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
	Filter(const char* pExpression);//由expression来进行语法树的初始构造
	~Filter();//析构语法树
	bool EvaluateData();//计算是否应该过滤当前数据
	//在contentfilteredtopic的set函数中已经实现了对于m_pFilter中parameter的修改
	Parameterlist Parameters;//parameters参数也存储在这里
	void Set_Typecode(TypeCode cTypecode);
	void Set_Cdr(CDR *pStream);
	
private:
	struct _AST* pGst;//存储生成的语法树的根部
	bool BuildGrammaTree(const char* pExpression);//作为Filter的私有函数确保封装性
	int Yyparse(void);//确保封装性
	_ANY_DATD Eval(struct _AST* pAst,Parameterlist Parameters);//为了区分错误类型加入一个int型的参数
	int iWrongkind;//记录在过滤过程中出现的错误
	ValueCode* pVc;
};
#endif