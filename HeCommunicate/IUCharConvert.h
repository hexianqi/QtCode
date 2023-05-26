/***************************************************************************************************
**      2023-05-25  IUCharConvert uchar转换器
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IUCharConvert : public IInitializeable
{
public:
    virtual void setDigits(QVariant::Type, int) = 0;
    virtual int digits(QVariant::Type) = 0;

public:
    virtual QVector<uchar> toUChar(uchar value) = 0;
    virtual QVector<uchar> toUChar(QVariant value) = 0;
    virtual QVector<uchar> toUChar(QVariantList value) = 0;

public:
    virtual uchar toValue(QVector<uchar> data) = 0;
    virtual QVariant toValue(QVariant::Type type, QVector<uchar> data, int pos = 0) = 0;
    virtual QVariantList toValues(QVariant::Type type, QVector<uchar> data, int size) = 0;
};

HE_END_NAMESPACE
