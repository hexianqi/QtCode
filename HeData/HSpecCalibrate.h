/***************************************************************************************************
**      2018-06-19  HSpecCalibrate 光谱校准数据类。
***************************************************************************************************/

#ifndef HSPECCALIBRATE_H
#define HSPECCALIBRATE_H

#include "ISpecCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecCalibratePrivate;

class HSpecCalibrate : public ISpecCalibrate
{
public:
    explicit HSpecCalibrate();
    ~HSpecCalibrate();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;
    virtual QVariantMap testParam() override;
    virtual QVector<double> preprocess(QVector<double> value, bool fitting = true) override;
    virtual QPolygonF calcEnergy(QVector<double> value) override;
    virtual double calcLuminous(double value) override;
    virtual int calcCommWaitTime(double &value) override;
    virtual bool isOverFrame(int size) override;
    virtual int checkOverflow(double value) override;

public:
    virtual void readContent(QDataStream &) override;
    virtual void writeContent(QDataStream &) override;

protected:
    HSpecCalibrate(HSpecCalibratePrivate &p);

protected:
    QScopedPointer<HSpecCalibratePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATE_H
