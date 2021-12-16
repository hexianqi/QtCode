/***************************************************************************************************
**      2019-04-08  HAbstractCodec 抽象编码类。
***************************************************************************************************/

#pragma once

#include "ICodec.h"

HE_BEGIN_NAMESPACE

class HAbstractCodecPrivate;

class HAbstractCodec : public ICodec
{
public:
    explicit HAbstractCodec();
    virtual ~HAbstractCodec();

protected:
    HAbstractCodec(HAbstractCodecPrivate &);

protected:
    QScopedPointer<HAbstractCodecPrivate> d_ptr;
};

HE_END_NAMESPACE
