/***************************************************************************************************
**      2018-06-19  HSpecStdCurve 光谱标准曲线数据类。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HSpecStdCurvePrivate;

class HSpecStdCurve : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecStdCurve)

public:
    explicit HSpecStdCurve();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault();
    void setCurve(const QVector<double> &value);
    QVector<double> curve();

protected:
    HSpecStdCurve(HSpecStdCurvePrivate &p);
};

HE_END_NAMESPACE
