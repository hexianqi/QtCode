/***************************************************************************************************
**      2018-06-19  ISpecCalibrate 光谱校准接口。
***************************************************************************************************/

#ifndef ISPECCALIBRATE_H
#define ISPECCALIBRATE_H

#include "HDataGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class ISpecCalibrate : public IInitializeable
{
public:
    virtual QVariantMap testParam() = 0;
    virtual QVector<double> preprocess(QVector<double> value, bool fitting = true) = 0;
    virtual QPolygonF calcEnergy(QVector<double> value) = 0;
    virtual double calcLuminous(double value) = 0;
    virtual int calcCommWaitTime(double &value) = 0;
    virtual bool isOverFrame(int size) = 0;
    virtual int checkOverflow(double value) = 0;

public:
    virtual void readContent(QDataStream &) = 0;
    virtual void writeContent(QDataStream &) = 0;
};

HE_DATA_END_NAMESPACE



#endif // ISPECCALIBRATE_H
