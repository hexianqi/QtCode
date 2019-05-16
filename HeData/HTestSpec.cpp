#include "HTestSpec_p.h"
#include "HeAlgorithm/HSpecData.h"
#include "HeAlgorithm/HSpecFacade.h"
#include "HeCore/HCore.h"
#include "HeData/ISpecCalibrate.h"
#include <QtCore/QVector>
#include <QtCore/QQueue>
#include <QtCore/QReadWriteLock>
#include <QtCore/QtMath>

HE_DATA_BEGIN_NAMESPACE

HTestSpecPrivate::HTestSpecPrivate()
{
    lock = new QReadWriteLock;
    specFacade = new HSpecFacade;
    specData = new HSpecData;
    samples.resize(2);
    addData("[光谱采样等待时间]", 0);
    addData("[积分时间]", 10.0);
    addData("[采样帧溢出状态]", false);
    addData("[采样溢出状态]", 0);
    addData("[采样比率]", 0.0);
}

void HTestSpecPrivate::setCalibrate(ISpecCalibrate *p)
{
    calibrate = p;
    addData(p->testParam());
}

void HTestSpecPrivate::setIntegralTime(double value)
{
    setData("[光谱采样等待时间]", calibrate->calcCommWaitTime(value));
    setData("[积分时间]", value);
    clearCache();
}

bool HTestSpecPrivate::adjustIntegralTime()
{
    if (maxSample >= 32000 && maxSample <= 60000)
        return false;

    auto d = data("[积分时间]").toDouble();
    auto n = calibrate->checkIntegralTime(d);
    if ((maxSample < 32000 &&  n == 1) || (maxSample > 60000 && n == -1))
        return false;
    if (maxSample < 6550)
        d *= 10;
    else if (maxSample < 32000)
        d *= 0.75 / (maxSample / 65536 - 0.05);
    else
        d *= 0.67;
    setIntegralTime(d);
    return true;
}

bool HTestSpecPrivate::setSample(QVector<double> value, bool avg)
{
    samples[0] = value;
    if (avg)
        value = average(samples[0]);
    samples[1] = calibrate->preprocess(value, fitting);
    return calcSpec();
}

void HTestSpecPrivate::clearCache()
{
    sampleCache.clear();
}

void HTestSpecPrivate::resetStdCurve()
{
    samples[0] = calibrate->stdCurve();
    samples[1] = calibrate->stdCurve();
    calcSpec();
}

QVector<double> HTestSpecPrivate::sample(int type)
{
    QReadLocker locker(lock);
    if (type < 0 || type >= samples.size())
        return QVector<double>();
    return samples[type];
}

bool HTestSpecPrivate::checkFrameOverflow()
{
    bool b = calibrate->checkFrameOverflow(sampleCache.size());
    setData("[采样帧溢出状态]", b);
    return b;
}

int HTestSpecPrivate::checkSampleOverflow()
{
    int i = calibrate->checkSampleOverflow(maxSample);
    setData("[采样溢出状态]", i);
    return i;
}

QVector<double> HTestSpecPrivate::average(QVector<double> value)
{
    int i,j;
    if (checkFrameOverflow())
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

void HTestSpecPrivate::calcMaxSample()
{
    maxSample = 0;
    for (int i = 0; i < samples[0].size(); i++)
        maxSample = qMax(maxSample, samples[0][i]);
    setData("[采样比率]", maxSample * 100.0 / 65535);
}

bool HTestSpecPrivate::calcSpec()
{
    QWriteLocker locker(lock);

    calcMaxSample();
    if (checkSampleOverflow() != 0)
        return false;

    specData->clear();
    specData->Energy = calibrate->calcEnergy(samples[1]);
    if(specData->Energy.isEmpty())
        return false;
    specFacade->calcSpectrum(specData);
    specData->LuminousFlux = calibrate->calcLuminous(specData->VisionEnergy / data("[积分时间]").toDouble());
    specData->LuminousPower = specData->LuminousFlux * specData->VisionEnergyRatio;
//    m_pSpectrum->SDCM = m_pChromatism->calcSdcm(m_pSpectrum->ColorTemperature, m_pSpectrum->CoordinateXy);
    addData("[峰值波长]", specData->PeakWave);
    addData("[峰值带宽]", specData->Bandwidth);
    addData("[主波长]", specData->DominantWave);
    addData("[色纯度]", specData->ColorPurity);
    addData("[色温]", specData->ColorTemperature);
    addData("[色坐标]", specData->CoordinateXy);
    addData("[色坐标x]", specData->CoordinateXy.x());
    addData("[色坐标y]", specData->CoordinateXy.y());
    addData("[色坐标uv]", specData->CoordinateUv);
    addData("[色坐标u]", specData->CoordinateUv.x());
    addData("[色坐标v]", specData->CoordinateUv.y());
    addData("[色坐标uvp]", specData->CoordinateUvp);
    addData("[色坐标up]", specData->CoordinateUvp.x());
    addData("[色坐标vp]", specData->CoordinateUvp.y());
    addData("[Duv]", specData->Duv);
    addData("[明视觉能量]", specData->VisionEnergy);
    addData("[红色比]", specData->RedRatio);
    addData("[蓝色比]", specData->BlueRatio);
    addData("[绿色比]", specData->GreenRatio);
    addData("[显色指数]", specData->RenderingIndexAvg);
    addData("[显色指数Rx]", renderingIndexS());
    addData("[光谱光通量]", specData->LuminousFlux);
    addData("[光功率]", specData->LuminousPower);
    addData("[色容差]", specData->SDCM);
    return true;
}

QString HTestSpecPrivate::renderingIndexS()
{
    QStringList list;
    for (int i = 0; i < specData->RenderingIndex.size(); i++)
    {
        if (i != 0 && i % 4 == 0)
            list << " ";
        list << HCore::toString("[显色指数Rx]", specData->RenderingIndex[i]);
    }
    return list.join(" ");
}

QString HTestSpecPrivate::energyS()
{
    QStringList list;
    for (auto p : specData->EnergyPercent)
        list << HCore::toString("[波长]", p.x()) + ":" +  HCore::toString("[光谱能量百分比]", p.x());
    return list.join(",");
}

HTestSpec::HTestSpec() :
    ITestSpec(*new HTestSpecPrivate)
{
}

HTestSpec::HTestSpec(HTestSpecPrivate &p) :
    ITestSpec(p)
{
}

HTestSpec::~HTestSpec()
{
}

QString HTestSpec::typeName()
{
    return "HTestSpec";
}

QVariant HTestSpec::data(QString type)
{
    Q_D(HTestSpec);
    if (type == "[光谱能量数据]")
        return d->energyS();
    return HTestData::data(type);
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

bool HTestSpec::adjustIntegralTime()
{
    Q_D(HTestSpec);
    return d->adjustIntegralTime();
}

bool HTestSpec::setSample(QVector<double> value, bool avg)
{
    Q_D(HTestSpec);
    if (value.size() < 1)
        return false;
    return d->setSample(value, avg);
}

void HTestSpec::setFitting(bool b)
{
    Q_D(HTestSpec);
    d->fitting = b;
}

void HTestSpec::clearCache()
{
    Q_D(HTestSpec);
    d->clearCache();
}

void HTestSpec::resetStdCurve()
{
    Q_D(HTestSpec);
    d->resetStdCurve();
}

double HTestSpec::sample(int type, int pel)
{
    auto s = sample(type);
    if (s.isEmpty() || pel < 0 || pel >= s.size())
        return 0;
    return s[pel];
}

QVector<double> HTestSpec::sample(int type)
{
    Q_D(HTestSpec);
    return d->sample(type);
}

QPointF HTestSpec::sampleMax(int type, double a, double b)
{
    auto s = sample(type);
    if (s.isEmpty())
        return QPointF();
    if (a > b)
        qSwap(a, b);
    int f = qBound(0, qFloor(a), s.size());
    int l = qBound(0, qCeil(b), s.size());
    double x = 0.0;
    double y = 0.0;
    for (int i = f; i < l; i++)
    {
        if (y < s[i])
        {
            x = i;
            y = s[i];
        }
    }
    return QPointF(x, y);
}

QPolygonF HTestSpec::samplePoly(int type)
{
    auto s = sample(type);
    if (s.isEmpty())
        return QPolygonF();

    QPolygonF r;
    for (int i = 0; i < s.size(); i++)
        r << QPointF(i, s[i]);
    return r;
}

QPolygonF HTestSpec::energy()
{
    Q_D(HTestSpec);
    return d->specData->EnergyPercent;
}

double HTestSpec::pelsToWave(double value)
{
    Q_D(HTestSpec);
    return d->calibrate->pelsToWave(value);
}

HE_DATA_END_NAMESPACE
