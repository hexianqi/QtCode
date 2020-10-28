/***************************************************************************************************
**      2018-06-19  HTestSpec 测试光谱数据类。
***************************************************************************************************/

#ifndef HTESTSPEC_H
#define HTESTSPEC_H

#include "HTestData.h"
#include "ITestSpec.h"

HE_DATA_BEGIN_NAMESPACE

class HTestSpecPrivate;

class HE_DATA_EXPORT HTestSpec : public ITestSpec
{
    Q_DECLARE_PRIVATE(HTestSpec)

public:
    explicit HTestSpec();

public:
    QString typeName() override;

public:
    void setData(QString type, QVariant value) override;
    QString toString(QString type) override;
    QVariant handleOperation(QString type, QVariant value = QVariant()) override;

public:
    void setCalibrate(ISpecCalibrate *) override;
    bool setSample(QVector<double> value, bool avg = false) override;
    void setFitting(bool b) override;

public:
    double sample(int type, int pel) override;
    QVector<double> sample(int type) override;
    QPolygonF samplePoly(int type) override;
    QPointF sampleMax(int type, double a, double b) override;

public:
    double pelsToWave(double value) override;
    bool setRam(QVector<uchar> value) override;
    QVector<uchar> getRam() override;

protected:
    HTestSpec(HTestSpecPrivate &p);
};

HE_DATA_END_NAMESPACE

#endif // HTESTSPEC_H
