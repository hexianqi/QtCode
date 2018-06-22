/***************************************************************************************************
**      2018-06-19  HTestSpec 测试光谱数据类。
***************************************************************************************************/

#ifndef HTESTSPEC_H
#define HTESTSPEC_H

#include "HTestData.h"
#include "ITestSpec.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HTestSpecPrivate;

class HTestSpec : public HTestData, public ITestSpec
{
    Q_DECLARE_PRIVATE(HTestSpec)

public:
    explicit HTestSpec();
    ~HTestSpec();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setCalibrate(ISpecCalibrate *) override;
    virtual void setIntegralTime(double value) override;
    virtual bool setSample(QVector<double> value, bool avg = false) override;
    virtual void clearQueue() override;

protected:
    HTestSpec(HTestSpecPrivate &p);
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTSPEC_H
