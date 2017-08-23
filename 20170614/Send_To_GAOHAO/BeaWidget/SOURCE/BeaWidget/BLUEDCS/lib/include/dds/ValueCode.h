/************************************************************
** 文件名：ValueCode.h
** Copyright (c) 2011-2012 中国船舶工业系统工程研究院
** 创建人：杨猛<xusen@seu.edu.cn>
** 日  期：2012-07-02
** 修改人：无
** 日  期：无
** 描  述：ValueCode头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef VALUECODE_H
#define VALUECODE_H

#include<vector>
using std::vector;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;
#include "dds/CDR.h"
#include "dds/TypeCode.h"

#if defined(VXWORKS) || defined(_DDS_LIB_FILE) || defined(KYLIN)
class ValueCode
#else
class DDS_DLL ValueCode
#endif
{
public:
	TypeCode *m_pType;             //CDR pValue's type
	CDR *m_pStream;               //CDR pValue
	char *m_pValue;
	TypeCode *m_pValue_Type;
	char *pName;
	bool bStop;
	vector<unsigned long> Index;
	vector<unsigned long> Value_Index;

	ValueCode();
	~ValueCode();
	void reset();
	bool One_Dim_Index(unsigned long &ulLen);
	bool Basic_Value(bool bSkip, bool bDel);
	bool Nested_Value(bool bSkip, bool bDel);

	bool Set_Typecode(TypeCode Typecode);
	bool Set_Cdr(CDR *pStream);

	inline bool Member_Value()
	{
		return Nested_Value(false, true);
	}
	inline void OutputInd(short sIndentation, ostringstream &tc_out)
	{
		for(int I = 0;I < sIndentation;I++)
			tc_out << "    ";
	}
	string Output_Type();
	string Output_Value();
private:
	vector<string> m_Tc_Vct;
	void _Output_Type(TypeCode *pTc, char *pName, bool bAlias, ostringstream &Tc_out, bool bDel_Tc, bool bDel_Name);
	void _Output_Value(int Indentation, TypeCode *pTc, char *pName, bool bAlias, ostringstream &Tc_out, bool bDel_Tc, bool bDel_Name);
};
#endif