#include "HSpecCalibrate_p.h"
#include "IDataFactory.h"
#include "HDataHelper.h"
#include "HSpecSetting.h"
#include "HSpecFittingLinear.h"
#include "HSpecFittingPolynom.h"
#include "HSpecFittingTest.h"
#include "HSpecStdCurve.h"
#include "HSpecPelsWave.h"
#include "HSpecLuminous.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QDataStream>
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibratePrivate::HSpecCalibratePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    setting = new HSpecSetting;
    fitting = new HSpecFittingPolynom;
    stdCurve = new HSpecStdCurve;
    pelsWave = new HSpecPelsWave;
    luminous = new HSpecLuminous;
}

HSpecCalibrate::HSpecCalibrate() :
    d_ptr(new HSpecCalibratePrivate)
{
}

HSpecCalibrate::HSpecCalibrate(HSpecCalibratePrivate &p) :
    d_ptr(&p)
{
}

HSpecCalibrate::~HSpecCalibrate()
{
}

void HSpecCalibrate::initialize(QVariantMap /*param*/)
{
}

QString HSpecCalibrate::typeName()
{
    return "HSpecCalibrate";
}

void HSpecCalibrate::readContent(QDataStream &s)
{
    quint32 version;
    QString type;
    s >> version;
    d_ptr->setting->readContent(s);
    d_ptr->pelsWave->readContent(s);
    d_ptr->stdCurve->readContent(s);
    d_ptr->luminous->readContent(s);
    s >> type;
    d_ptr->fitting = d_ptr->factory->createSpecFitting(type);
    d_ptr->fitting->readContent(s);
}

void HSpecCalibrate::writeContent(QDataStream &s)
{
    s << quint32(1);
    d_ptr->setting->writeContent(s);
    d_ptr->pelsWave->writeContent(s);
    d_ptr->stdCurve->writeContent(s);
    d_ptr->luminous->writeContent(s);
    s << d_ptr->fitting->typeName();
    d_ptr->fitting->writeContent(s);
}

QVector<uchar> HSpecCalibrate::toBinaryData()
{
    auto r =  QVector<uchar>() << HDataHelper::writeUInt16(0)       // 大小
                               << HDataHelper::writeUInt16(1)       // 版本
                               << d_ptr->setting->toBinaryData()
                               << d_ptr->pelsWave->toBinaryData()
                               << d_ptr->fitting->toBinaryData();
    r[0] = uchar(r.size() / 256);
    r[1] = uchar(r.size() % 256);
    return r;
}

bool HSpecCalibrate::fromBinaryData(QVector<uchar> data)
{
    int pos = 0;
    int version = 0;
    if (!HDataHelper::checkHead(data, pos, version))
        return false;
    if (!d_ptr->setting->fromBinaryData(data, pos))
        return false;
    if (!d_ptr->pelsWave->fromBinaryData(data, pos))
        return false;
    if (!d_ptr->fitting->fromBinaryData(data, pos))
        return false;
    return true;
}

void HSpecCalibrate::setFitting(HSpecFitting *p)
{
    d_ptr->fitting = p;
}

IDataItem *HSpecCalibrate::item(HSpecType type)
{
    if (type == Setting)
        return d_ptr->setting;
    if (type == Fitting)
        return d_ptr->fitting;
    if (type == StdCurve)
        return d_ptr->stdCurve;
    if (type == PelsWave)
        return d_ptr->pelsWave;
    if (type == Luminous)
        return d_ptr->luminous;
    return nullptr;
}

QVariantMap HSpecCalibrate::testParam()
{
    return d_ptr->setting->testParam();
}

QVector<double> HSpecCalibrate::preprocess(QVector<double> value, bool fitting)
{
    if (value.size() < 1)
        return value;

    value = d_ptr->setting->dealBotton(value);
    value = d_ptr->setting->smoothCurve(value);
    if (fitting)
        value = d_ptr->fitting->handle(value);
    return value;
}

QPolygonF HSpecCalibrate::calcEnergy(QVector<double> value, double offset)
{
    double x,y;
    QPolygonF poly;
    auto curve = stdCurve();
    auto size = qMin(curve.size(), value.size());

    if (size <= 0)
        return poly;

    for (int i = 0; i < size; i++)
    {
        x = pelsToWave(i);
        if (value[i] < 50)
            y = 0;
        else if (curve[i] < 50)
            y = 1;
        else
            y = value[i] / curve[i];
        poly.append(QPointF(x, y));
    }
    return d_ptr->setting->interpEnergy(poly, offset);
}

double HSpecCalibrate::calcLuminous(double value)
{
    return d_ptr->luminous->handle(value);
}

int HSpecCalibrate::calcCommWaitTime(double &value)
{
    return d_ptr->setting->calcCommWaitTime(value);
}

int HSpecCalibrate::checkIntegralTime(double value)
{
    return d_ptr->setting->checkIntegralTime(value);
}

int HSpecCalibrate::checkFrameOverflow(int size)
{
    return d_ptr->setting->checkFrameOverflow(size);
}

int HSpecCalibrate::checkSampleOverflow(double value)
{
    return d_ptr->setting->checkSampleOverflow(value);
}

double HSpecCalibrate::pelsToWave(double value)
{
    return d_ptr->pelsWave->handle(value);
}

QVector<double> HSpecCalibrate::stdCurve()
{
    return d_ptr->stdCurve->curve();
}

void HSpecCalibrate::setStdCurve(QVector<double> value)
{
    d_ptr->stdCurve->setCurve(value);
}

HE_DATA_END_NAMESPACE
