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
    addData("[CCD偏差]", 55.0);
    addData("[光谱采样等待时间]", 0);
    addData("[积分时间]", 10.0);
    addData("[光谱采样帧溢出状态]", -1);
    addData("[光谱采样溢出状态]", 0);
    addData("[光谱采样比率]", 0.0);
    addData("[自动查找波段]", false);
    addData("[蓝光范围]", QPointF(380.0, 450.0));
    addData("[荧光范围]", QPointF(450.0, 780.0));
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

bool HTestSpecPrivate::matchIntegralTime()
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
        value = average(samples.at(0));
    samples[1] = calibrate->preprocess(value, fitting);
    return calcSpec();
}

void HTestSpecPrivate::clearCache()
{
    sampleCache.clear();
}

void HTestSpecPrivate::useStdCurve()
{
    samples[0] = calibrate->stdCurve();
    samples[1] = calibrate->stdCurve();
    calcSpec();
}

void HTestSpecPrivate::setStdCurve()
{
    calibrate->setStdCurve(sample(1));
}

QVector<double> HTestSpecPrivate::sample(int type)
{
    QReadLocker locker(lock);
    if (type < 0 || type >= samples.size())
        return QVector<double>();
    return samples[type];
}

int HTestSpecPrivate::checkFrameOverflow()
{
    int i = calibrate->checkFrameOverflow(sampleCache.size());
    setData("[光谱采样帧溢出状态]", i);
    return i;
}

int HTestSpecPrivate::checkSampleOverflow()
{
    int i = calibrate->checkSampleOverflow(maxSample);
    setData("[光谱采样溢出状态]", i);
    return i;
}

QVector<double> HTestSpecPrivate::average(QVector<double> value)
{
    int i,j;
    if (checkFrameOverflow() >= 0)
        sampleCache.dequeue();
    sampleCache.enqueue(value);
    checkFrameOverflow();

    for (i = 0; i < value.size(); i++)
    {
        auto avg = 0.0;
        for (j = 0; j < sampleCache.size(); j++)
            avg += sampleCache.at(j).at(i);
        value[i] = avg / j;
    }
    return value;
}

void HTestSpecPrivate::calcMaxSample()
{
    maxSample = 0;
    for (double i : samples.at(0))
        maxSample = qMax(maxSample, i);
    setData("[光谱采样比率]", maxSample / 655.35);
}

bool HTestSpecPrivate::calcSpec()
{
    QWriteLocker locker(lock);

    calcMaxSample();
    if (checkSampleOverflow() != 0)
        return false;

    specData->clear();
    specData->Energy = calibrate->calcEnergy(samples[1], 0);
    if(specData->Energy.isEmpty())
        return false;
    specFacade->calcSpectrum(specData);
    auto time = data("[积分时间]").toDouble();
    auto visionFlux = specData->VisionFlux;
    auto visionEfficien = specData->VisionEfficien;
    auto luminousFlux = calibrate->calcLuminous(visionFlux / time);
    auto luminousPower = visionEfficien < 0.00001 ? 0.0 : 1000 * luminousFlux / visionEfficien;
    auto synthetic = calibrate->calcSynthetic(specData->Energy, time, data("[自动查找波段]").toBool(), data("[蓝光范围]").toPointF(), data("[荧光范围]").toPointF());
    // 测试数据LED对不起来，作弊一下；
    // 峰值波长 >= 700 时，认为是卤钨灯，不需要重新计算；
    // 其他的认为是LED，需要加‘色温偏差’进行重新计算；
    if (specData->PeakWave < 700)
    {
        specData->Energy = calibrate->calcEnergy(samples[1], data("[CCD偏差]").toDouble());
        specFacade->calcSpectrum(specData);
    }
    addData(synthetic);
    addData("[明视觉光通量]", visionFlux);
    addData("[明视觉光效率]", visionEfficien);
    addData("[光谱光通量]", luminousFlux);
    addData("[光功率]", luminousPower);
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
    addData("[红色比]", specData->RedRatio);
    addData("[蓝色比]", specData->BlueRatio);
    addData("[绿色比]", specData->GreenRatio);
    addData("[显色指数Ra]", specData->RenderingIndexAvg);
    addData("[显色指数R9]", specData->RenderingIndex.at(8));
    addData("[显色指数Rx]", renderingIndex());
    addData("[光谱能量曲线]", specData->EnergyPercent);
    return true;
}

QString HTestSpecPrivate::renderingIndex()
{
    QStringList list;
    for (int i = 0; i < specData->RenderingIndex.size(); i++)
    {
        if (i != 0 && i % 5 == 0)
            list << " ";
        list << HCore::toString("[显色指数Rx]", specData->RenderingIndex[i]);
    }
    return list.join(" ");
}

QString HTestSpecPrivate::energy()
{
    auto poly = data("[光谱能量曲线]").value<QPolygonF>();
    QStringList list;
    for (auto p : poly)
        list << HCore::toString("[光谱波长]", p.x()) + ":" +  HCore::toString("[光谱能量百分比]", p.y());
    return list.join(",");
}

HTestSpec::HTestSpec() :
    HTestData(*new HTestSpecPrivate)
{
}

HTestSpec::HTestSpec(HTestSpecPrivate &p) :
    HTestData(p)
{
}

QString HTestSpec::typeName()
{
    return "HTestSpec";
}

void HTestSpec::setData(QString type, QVariant value)
{
    Q_D(HTestSpec);
    if (type == "[积分时间]")
        return d->setIntegralTime(value.toDouble());
    if (type == "[光谱采样值]")
    {
        setSample(value.value<QVector<double>>());
        return;
    }
    return HTestData::setData(type, value);
}

QString HTestSpec::toString(QString type)
{
    Q_D(HTestSpec);
    if (type == "[光谱能量数据]")
        return d->energy();
    return HTestData::toString(type);
}

QVariant HTestSpec::handleOperation(QString type, QVariant value)
{
    Q_D(HTestSpec);
    if (type == "<匹配积分时间>")
        return d->matchIntegralTime();
    if (type == "<清空光谱采样缓存>")
    {
        d->clearCache();
        return true;
    }
    if (type == "<使用标准光谱曲线>")
    {
        d->useStdCurve();
        return true;
    }
    if (type == "<设置标准光谱曲线>")
    {
        d->setStdCurve();
        return true;
    }
    return HTestData::handleOperation(type, value);
}

bool HTestSpec::setCalibrate(void *p)
{
    Q_D(HTestSpec);
    auto c = static_cast<ISpecCalibrate *>(p);
    if (c == nullptr)
        return false;
    d->setCalibrate(c);
    return true;
}

bool HTestSpec::setSample(QVector<double> value, bool avg)
{
    Q_D(HTestSpec);
    if (value.isEmpty())
        return false;
    return d->setSample(value, avg);
}

void HTestSpec::setFitting(bool b)
{
    Q_D(HTestSpec);
    d->fitting = b;
}

double HTestSpec::sample(int type, int pel)
{
    auto s = sample(type);
    if (pel < 0 || pel >= s.size())
        return 0.0;
    return s.at(pel);
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
        return {};
    if (a > b)
        qSwap(a, b);
    int f = qBound(0, qFloor(a), s.size());
    int l = qBound(0, qCeil(b), s.size());
    double x = 0.0;
    double y = 0.0;
    for (int i = f; i < l; i++)
    {
        if (y < s.at(i))
        {
            x = i;
            y = s.at(i);
        }
    }
    return {x, y};
}

QPolygonF HTestSpec::samplePoly(int type)
{
    auto s = sample(type);
    if (s.isEmpty())
        return QPolygonF();

    QPolygonF r;
    for (int i = 0; i < s.size(); i++)
        r << QPointF(i, s.at(i));
    return r;
}

double HTestSpec::pelsToWave(double value)
{
    Q_D(HTestSpec);
    return d->calibrate->pelsToWave(value);
}

bool HTestSpec::setRam(QVector<uchar> value)
{
    Q_D(HTestSpec);
    return d->calibrate->fromBinaryData(value);
}

QVector<uchar> HTestSpec::getRam()
{
    Q_D(HTestSpec);
    return d->calibrate->toBinaryData();
}

HE_DATA_END_NAMESPACE
