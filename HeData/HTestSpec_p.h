#ifndef HTESTSPEC_P_H
#define HTESTSPEC_P_H

#include "HTestSpec.h"
#include "HTestData_p.h"
#include "HeAlgorithm/HAlgorithmGlobal.h"
#include <QtCore/QVector>
#include <QtCore/QQueue>

class QReadWriteLock;

HE_ALGORITHM_BEGIN_NAMESPACE
class HSpecFacade;
class HSpecData;
HE_ALGORITHM_END_NAMESPACE
HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

class HE_DATA_EXPORT HTestSpecPrivate : public HTestDataPrivate
{
public:
    HTestSpecPrivate();

public:
    void setCalibrate(ISpecCalibrate *);
    void setIntegralTime(double value);
    bool adjustIntegralTime();
    bool setSample(QVector<double> value, bool avg = false);
    void resetStdCurve();
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

HE_DATA_END_NAMESPACE

#endif // HTESTSPEC_P_H
