/***************************************************************************************************
**      2018-06-19  HSpecLuminous 光谱光通量数据类。
***************************************************************************************************/

#ifndef HSPECLUMINOUS_H
#define HSPECLUMINOUS_H

#include "HAbstractCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecLuminousPrivate;

class HSpecLuminous : public HAbstractCalibrateItem
{
    Q_DECLARE_PRIVATE(HSpecLuminous)

public:
    explicit HSpecLuminous();
    ~HSpecLuminous() override;

public:
    void restoreDefault() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    double handle(double value);

protected:
    HSpecLuminous(HSpecLuminousPrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECLUMINOUS_H
