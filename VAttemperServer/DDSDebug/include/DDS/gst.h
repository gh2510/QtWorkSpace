/************************************************************
** 文件名：gst.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<635584332@qq.com>
** 日  期：2012-07-05
** 修改人：无
** 日  期：无
** 描  述：gst头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef GST_H
#define GST_H


#include "dds/bison1.hpp"

#include "dds/typecode.h"

#include "dds/CDR.h"

#include "dds/valuecode.h"

enum _NODE_TYPE {NL,FID,CID,PID};//枚举类型非叶、id和非id
//enum TCkind {tc_char,tc_bool,tc_int,tc_float};//暂时代替typecode表示类型

#define MAX_STRING_LEN 50 //字符串的最大长度


//接下来是运行的_INDEX_STRUCT
struct _INDEX_STRUCT
{
	int iNum;//[]中的数字
	_INDEX_STRUCT* pNext;//对应[][]...这种情况
};
//



/////统一表示的fieldnamepart类型
struct _FIELD_NAME_PART
{
	char* pName;//存储id的Name如:a[]中的a
	_INDEX_STRUCT* pIndexpart;//存储id的索引如:a[]中的[]
	_FIELD_NAME_PART* pNext;//对应处理a.b这种情况
};
/////

struct _AST
{
	_NODE_TYPE Nodetype;//节点类型：表示是叶节点还是非叶节点
	int iOptype;//表示这个节点代表的运算符类型
	struct _AST *pl;
	struct _AST *pr;
};


//采用统一的数据结构_ANY_DATD
//包含两个属性：Kind和pValue
//Kind表示pValue的类型
//pValue为采用char*形式存储具体值
struct _ANY_DATD
{
	//Kind采用TCKIND类型
	_TC_KIND Kind;
	char* pValue;
};
struct _END_NODE_CI
{
	_NODE_TYPE Nodetype;//表明节点类型
	_ANY_DATD Data;//非id节点存储的数据信息
};

//id节点
struct _END_NODE_I
{
	_NODE_TYPE Nodetype;//表明节点类型
	//Name属性表示id用于查询具体的值
	//char* pName;//pName指针一定要注意空指针的情况
	//之后统一使用FieldName结构来处理
	_FIELD_NAME_PART* pId;//用_FIELD_NAME_PART结构统一表示a,a[],a.b,a[].b[]等数据结构
};


//创建parameter中节点
struct _END_NODE_P
{
	_NODE_TYPE Nodetype;//表明节点类型
	//接下来的int表示数组中的第几个
	int iIndex;//数组中的第几个
};

struct _AST* NewEndNodeCI(char* pData,_TC_KIND Kind);
struct _AST* NewEndNodeI(_FIELD_NAME_PART* pName);
struct _AST* NewEndNodeP(int iIndex);//建立EndNodeP的终结点
struct _AST* NewAstNl(int iOptype,struct _AST* pl,struct _AST* pr);//iOptype代表操作符类型
//_ANY_DATD eval(struct _AST* a,ValueCode* pVc,_ANY_DATD[]);//对于语法书进行遍历以及计算
//现在将eval的参数改为三个root,valuecode,parameter


//extern ValueCode* pVc;//查询数据类实例



////////测试indexpart的NewIndexpart函数
struct _INDEX_STRUCT* NewIndexpart(int iNum);//只要数字，pNext在规约的时候再处理
//

////以下是建立_FIELD_NAME_PART部分的函数
struct _FIELD_NAME_PART* NewFieldNamePart(char* pName,struct _INDEX_STRUCT* pIndex);//输入参数是id,index.
////



int EditDistance(const char* pSource,const char* pTarget);//计算编辑距离

//////设计一个用来保存树根的全局变量
extern struct _AST* pRoot;

///index测试专用
extern struct _INDEX_STRUCT* pIndextestnode;


#endif