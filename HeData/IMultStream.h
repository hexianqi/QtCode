/***************************************************************************************************
**      2020-09-30  IMultStream 多流接口。
***************************************************************************************************/

#pragma once

#include "HAbstractStream.h"

HE_DATA_BEGIN_NAMESPACE

class IMultStream : public HAbstractStream
{
public:
    using HAbstractStream::HAbstractStream;

public:
    // 添加流
    virtual void addStream(QString suffix, IStream *, bool def = true) = 0;
};

HE_DATA_END_NAMESPACE
