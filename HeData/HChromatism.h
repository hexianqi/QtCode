/***************************************************************************************************
**      2019-05-20  HChromatism 色容差数据。
***************************************************************************************************/

#pragma once

#include "IChromatism.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismPrivate;

class HChromatism : public IChromatism
{
    Q_DECLARE_PRIVATE(HChromatism)

public:
    explicit HChromatism();
    ~HChromatism();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    double calcSdcm(double tc, QPointF xy) override;
    QVariantMap toMap() override;

protected:
    HChromatism(HChromatismPrivate &);

protected:
    bool matching(double tc);
};

HE_DATA_END_NAMESPACE
