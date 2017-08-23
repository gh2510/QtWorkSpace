/************************************************************
** 文件名：datalistener.h
** Copyright (c) 2017 仁谷系统集成
** 创建人：尚超<itshangchao@qq.com>
** 日  期：2017-06-01
** 描  述：datalistener头文件,监听主题到来信息，解析数据到其他模块
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#pragma once
#include "DDS_API.h"

class TimeStateInfo_Listener : public DataReaderListener
{
public:
    _RETURNCODE_T On_Data_Available(DataReader *pDataReader);
};
