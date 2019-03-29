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
    ~HTestSpec() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setCalibrate(ISpecCalibrate *) override;
    void setIntegralTime(double value) override;
    bool adjustIntegralTime() override;
    bool setSample(QVector<double> value, bool avg = false) override;
    void setFitting(bool b) override;
    void clearCache() override;
    void resetStdCurve() override;

public:
    double sample(int type, int pel) override;
    QVector<double> sample(int type) override;
    QPointF sampleMax(int type, double a, double b) override;
    QPolygonF samplePoly(int type) override;
    QPolygonF energy() override;
    double pelsToWave(double value) override;

protected:
    HTestSpec(HTestSpecPrivate &p);
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTSPEC_H
