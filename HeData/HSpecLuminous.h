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
    ~HSpecLuminous();

public:
    virtual void restoreDefault() override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

public:
    double handle(double value);

protected:
    HSpecLuminous(HSpecLuminousPrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HSPECLUMINOUS_H
