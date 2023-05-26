/***************************************************************************************************
**      2023-05-26  HLittleUCharConvert
***************************************************************************************************/

#pragma once

#include "HAbstractUCharConvert.h"

HE_BEGIN_NAMESPACE

class HLittleUCharConvertPrivate;

class HLittleUCharConvert : public HAbstractUCharConvert
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLittleUCharConvert)

public:
    explicit HLittleUCharConvert(QObject *parent = nullptr);
    ~HLittleUCharConvert() override;

public:
    QString typeName() override;

public:
    QVector<uchar> toVector(int value) override;
    QVector<uchar> toVector(uint value) override;
    QVector<uchar> toVector(double value) override;
    int toInt(QVector<uchar> data, int pos = 0) override;
    double toDouble(QVector<uchar> data, int pos = 0) override;
    uint toUInt(QVector<uchar> data, int pos = 0) override;

protected:
    HLittleUCharConvert(HLittleUCharConvertPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

