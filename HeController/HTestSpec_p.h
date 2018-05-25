#ifndef HTESTSPEC_P_H
#define HTESTSPEC_P_H

#include "HTestSpec.h"
#include "HTestData_p.h"
#include "HeAlgorithm/HSpectrumFacade.h"
#include <QVector>
#include <QQueue>

class QReadWriteLock;

HE_ALGORITHM_BEGIN_NAMESPACE
class HSpectrumFacade;
HE_ALGORITHM_END_NAMESPACE
HE_ALGORITHM_USE_NAMESPACE


HE_CONTROLLER_BEGIN_NAMESPACE

class HTestSpecPrivate : public HTestDataPrivate
{
public:
    HTestSpecPrivate();

public:
    void setCalibrate(ISpecCalibrate *);
    void setIntegralTime(double value);
    bool setSample(QVector<double> value, bool avg = false);
    void clearQueue();

public:
    QVector<double> average(QVector<double> value);
    bool calcSpectrum();
    void calcMaxSample();
    bool isOverFrame();
    int checkOverflow();
    void clearResult();

public:
    QReadWriteLock *lock;
    HSpectrumFacade *spectrumFacade;
    ISpecCalibrate *calibrate;
    bool fitting = true;
    double maxSample = 0;
    QVector<QVector<double> > samples;
    QQueue<QVector<double> > sampleCache;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTESTSPEC_P_H
