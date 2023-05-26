/***************************************************************************************************
**      2019-04-08  HAbstractCodec 抽象编码类。
***************************************************************************************************/

#pragma once

#include "ICodec.h"

HE_BEGIN_NAMESPACE

class HAbstractCodecPrivate;

class HAbstractCodec : public QObject, public ICodec
{
    Q_OBJECT

public:
    explicit HAbstractCodec(QObject *parent = nullptr);
    ~HAbstractCodec() override;

protected:
    HAbstractCodec(HAbstractCodecPrivate &, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractCodecPrivate> d_ptr;
};

HE_END_NAMESPACE
