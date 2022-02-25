#pragma once

#include "HTestSpec.h"
#include "HTestData_p.h"
#include <QtCore/QVector>
#include <QtCore/QQueue>

class QReadWriteLock;

HE_BEGIN_NAMESPACE

class HSpecFacade;
class HSpecData;
class ISpecCalibrate;

class HTestSpecPrivate : public HTestDataPrivate
{
public:
    HTestSpecPrivate();

public:
    void setCalibrate(ISpecCalibrate *);
    bool setIntegralTime(double value);
    bool matchIntegralTime();
    bool setSample(QVector<double> value, bool avg = false);
    void useStdCurve();
    void setStdCurve();
    void clearCache();

public:
    QVector<double> sample(int type);

public:
    int checkFrameOverflow();
    int checkSampleOverflow();
    QVector<double> average(QVector<double> value);
    void calcMaxSample();
    bool calcSpec();
    QString renderingIndex();
    QString energy();

public:
    QReadWriteLock *lock = nullptr;
    ISpecCalibrate *calibrate = nullptr;
    HSpecFacade *specFacade = nullptr;
    HSpecData *specData = nullptr;
    bool fitting = true;
    double maxSample = 0;
    QVector<QVector<double>> samples;
    QQueue<QVector<double>> sampleCache;
};

HE_END_NAMESPACE
