/***************************************************************************************************
**      2018-06-19  HSpecLuminous 光谱光通量数据类。
***************************************************************************************************/

#pragma once

#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HSpecLuminousPrivate;

class HSpecLuminous : public HAbstractDataItem
{
    Q_DECLARE_PRIVATE(HSpecLuminous)

public:
    explicit HSpecLuminous();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault();
    double handle(double value);

public:
    void setSelfAbsorption(const QMap<QString, double> &value);
    QMap<QString, double> selfAbsorption();

protected:
    HSpecLuminous(HSpecLuminousPrivate &p);
};

HE_END_NAMESPACE
