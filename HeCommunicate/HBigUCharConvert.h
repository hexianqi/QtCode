/***************************************************************************************************
**      2023-05-26  HBigUCharConvert 高位编址转换类（高字节在前）。
***************************************************************************************************/

#pragma once

#include "HAbstractUCharConvert.h"

HE_BEGIN_NAMESPACE

class HBigUCharConvertPrivate;

class HBigUCharConvert : public HAbstractUCharConvert
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBigUCharConvert)

public:
    explicit HBigUCharConvert(QObject *parent = nullptr);
    ~HBigUCharConvert() override;

public:
    QString typeName() override;

protected:
    QVector<uchar> toVector(int value) override;
    QVector<uchar> toVector(uint value) override;
    QVector<uchar> toVector(double value) override;
    int toInt(QVector<uchar> data, int pos = 0) override;
    double toDouble(QVector<uchar> data, int pos = 0) override;
    uint toUInt(QVector<uchar> data, int pos = 0) override;

protected:
    HBigUCharConvert(HBigUCharConvertPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

