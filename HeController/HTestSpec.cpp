#include "HTestSpec_p.h"
#include "HeAlgorithm/HSpectrumData.h"
#include "HeAlgorithm/HSpectrumFacade.h"
#include "HeData/ISpecCalibrate.h"
#include <QVector>
#include <QQueue>
#include <QReadWriteLock>

HE_CONTROLLER_BEGIN_NAMESPACE

HTestSpecPrivate::HTestSpecPrivate()
{
    lock = new QReadWriteLock;
    spectrumFacade = new HSpectrumFacade;
    samples.resize(2);
    addData("[光谱采样等待时间]", 0);
    addData("[积分时间]", 10);
}

void HTestSpecPrivate::setCalibrate(ISpecCalibrate *p)
{
    calibrate = p;
    QMapIterator<QString, QVariant> i(calibrate->testParam());
    while (i.hasNext())
    {
        i.next();
        addData(i.key(), i.value());
    }
}

void HTestSpecPrivate::setIntegralTime(double value)
{
    setData("[光谱采样等待时间]", calibrate->calcCommWaitTime(value));
    setData("[积分时间]", value);
    clearCache();
}

bool HTestSpecPrivate::setSample(QVector<double> value, bool avg)
{
    samples[0] = value;
    if (avg)
        value = average(samples[0]);
    samples[1] = calibrate->preprocess(value, fitting);
    return calcSpectrum();
}

QVector<double> HTestSpecPrivate::average(QVector<double> value)
{
    int i,j;
    if (isOverFrame())
        sampleCache.dequeue();
    sampleCache.enqueue(value);

    for (i = 0; i < value.size(); i++)
    {
        auto avg = 0.0;
        for (j = 0; j < sampleCache.size(); j++)
            avg += sampleCache[j][i];
        value[i] = avg / j;
    }
    return value;
}

bool HTestSpecPrivate::calcSpectrum()
{
    QWriteLocker locker(lock);

    calcMaxSample();
    if (checkOverflow() != 0)
        return false;

    HSpectrumData *sp = new HSpectrumData;
    sp->Energy = calibrate->calcEnergy(samples[1]);
    if(sp->Energy.isEmpty())
        return false;
    spectrumFacade->calcSpectrum(sp);
    sp->Luminous = calibrate->calcLuminous(sp->VisionEnergy / data("[积分时间]").toDouble());
//    m_pSpectrum->SDCM = m_pChromatism->calcSdcm(m_pSpectrum->ColorTemperature, m_pSpectrum->CoordinateXy);
    addData("[峰值波长]", sp->PeakWave);
    addData("[峰值带宽]", sp->Bandwidth);
    addData("[主波长]", sp->DominantWave);
    addData("[色纯度]", sp->ColorPurity);
    addData("[色温]", sp->ColorTemperature);
    addData("[显色指数]", sp->RenderingIndexAvg);
    addData("[显色指数Rx]", QVariant::fromValue(sp->RenderingIndex.toList()));
    addData("[色坐标]", sp->CoordinateUv);
    addData("[色坐标uv]", sp->CoordinateUv);
    addData("[色坐标uvp]", sp->CoordinateUvp);
    addData("[Duv]", sp->Duv);
    addData("[红色比]", sp->RedRatio);
    addData("[蓝色比]", sp->BlueRatio);
    addData("[绿色比]", sp->GreenRadio);
    addData("[光谱光通量]", sp->Luminous);
    addData("[色容差]", sp->SDCM);
    return true;
}

void HTestSpecPrivate::calcMaxSample()
{
    maxSample = 0;
    for (int i = 0; i < samples[0].size(); i++)
        maxSample = qMax(maxSample, samples[0][i]);
}

bool HTestSpecPrivate::isOverFrame()
{
    return calibrate->isOverFrame(sampleCache.size());
}

int HTestSpecPrivate::checkOverflow()
{
    return calibrate->checkOverflow(maxSample);
}

void HTestSpecPrivate::clearCache()
{
    sampleCache.clear();
}


HTestSpec::HTestSpec()
    : HTestData(*new HTestSpecPrivate)
{
}

HTestSpec::HTestSpec(HTestSpecPrivate &p)
    : HTestData(p)
{
}

HTestSpec::~HTestSpec()
{
}

void HTestSpec::initialize(QVariantMap param)
{
    HTestData::initialize(param);
}

QString HTestSpec::typeName()
{
    return "HTestSpec";
}

void HTestSpec::setCalibrate(ISpecCalibrate *p)
{
    Q_D(HTestSpec);
    d->setCalibrate(p);
}

void HTestSpec::setIntegralTime(double value)
{
    Q_D(HTestSpec);
    d->setIntegralTime(value);
}

bool HTestSpec::setSample(QVector<double> value, bool avg)
{
    Q_D(HTestSpec);
    if (value.size() < 1)
        return false;
    return d->setSample(value, avg);
}

HE_CONTROLLER_END_NAMESPACE
