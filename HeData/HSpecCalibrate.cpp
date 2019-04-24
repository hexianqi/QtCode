#include "HSpecCalibrate_p.h"
#include "HSpecSetting.h"
#include "HSpecFittingLinear.h"
#include "HSpecFittingTest.h"
#include "HSpecStdCurve.h"
#include "HSpecPelsWave.h"
#include "HSpecLuminous.h"
#include <QtCore/QDataStream>
#include <QtGui/QPolygonF>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibratePrivate::HSpecCalibratePrivate()
{
    setting = new HSpecSetting;
    fitting = new HSpecFittingTest;
    stdCurve = new HSpecStdCurve;
    pelsWave = new HSpecPelsWave;
    luminous = new HSpecLuminous;
}

HSpecCalibrate::HSpecCalibrate()
    : d_ptr(new HSpecCalibratePrivate)
{
}

HSpecCalibrate::HSpecCalibrate(HSpecCalibratePrivate &p)
    : d_ptr(&p)
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

IDataItem *HSpecCalibrate::item(QString type)
{
    if (type == "HSpecSetting")
        return d_ptr->setting;
    if (type == "HSpecFitting")
        return d_ptr->fitting;
    if (type == "HSpecStdCurve")
        return d_ptr->stdCurve;
    if (type == "HSpecPelsWave")
        return d_ptr->pelsWave;
    if (type == "HSpecLuminous")
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
    if (fitting)
        value = d_ptr->fitting->handle(value);
    return d_ptr->setting->smoothCurve(value);
}

QPolygonF HSpecCalibrate::calcEnergy(QVector<double> value)
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
    return d_ptr->setting->interpEnergy(poly);
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

bool HSpecCalibrate::checkFrameOverflow(int size)
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

void HSpecCalibrate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    d_ptr->setting->readContent(s);
    d_ptr->pelsWave->readContent(s);
    d_ptr->stdCurve->readContent(s);
    d_ptr->fitting->readContent(s);
    d_ptr->luminous->readContent(s);
}

void HSpecCalibrate::writeContent(QDataStream &s)
{
    s << quint32(1);
    d_ptr->setting->writeContent(s);
    d_ptr->pelsWave->writeContent(s);
    d_ptr->stdCurve->writeContent(s);
    d_ptr->fitting->writeContent(s);
    d_ptr->luminous->writeContent(s);
}

HE_DATA_END_NAMESPACE
