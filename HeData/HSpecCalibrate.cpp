#include "HSpecCalibrate_p.h"
#include "HSpecSetting.h"
#include "HSpecFitting.h"
#include "HSpecStdCurve.h"
#include "HSpecPelsWave.h"
#include "HSpecLuminous.h"
#include <QPolygonF>
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibratePrivate::HSpecCalibratePrivate()
{
    setting = new HSpecSetting;
    fitting = new HSpecFitting;
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

void HSpecCalibrate::initialize(QVariantMap param)
{
    Q_UNUSED(param)
}

QString HSpecCalibrate::typeName()
{
    return "HSpecCalibrate";
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
    {
        value = d_ptr->fitting->handle(value);
        value = d_ptr->setting->smoothCurve(value);
    }
    return value;
}

QPolygonF HSpecCalibrate::calcEnergy(QVector<double> value)
{
    double x,y;
    QPolygonF poly;
    auto curve = d_ptr->stdCurve->data();
    auto size = qMin(curve.size(), value.size());

    if (size <= 0)
        return poly;
    for (int i = 0; i < size; i++)
    {
        x = d_ptr->pelsWave->toWave(i);
        if (value[i] < 50)
            y = 0;
        else if (curve[i] < 50)
            y = 1;
        else
            y = value[i] / curve[i];
        poly.append(QPointF(x,y));
    }
    poly = d_ptr->setting->interpolateEnergy(poly);
    return d_ptr->setting->shieldEnergy(poly);
}

double HSpecCalibrate::calcLuminous(double value)
{
    return d_ptr->luminous->handle(value);
}

int HSpecCalibrate::calcCommWaitTime(double &value)
{
    return d_ptr->setting->calcCommWaitTime(value);
}

bool HSpecCalibrate::isOverFrame(int size)
{
    return d_ptr->setting->isOverFrame(size);
}

int HSpecCalibrate::checkOverflow(double value)
{
    return d_ptr->setting->checkOverflow(value);
}

void HSpecCalibrate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> *d_ptr->setting;
    s >> *d_ptr->pelsWave;
    s >> *d_ptr->stdCurve;
    s >> *d_ptr->fitting;
    s >> *d_ptr->luminous;
}

void HSpecCalibrate::writeContent(QDataStream &s)
{
    s << typeName();
    s << quint32(1);
    s << *d_ptr->setting;
    s << *d_ptr->pelsWave;
    s << *d_ptr->stdCurve;
    s << *d_ptr->fitting;
    s << *d_ptr->luminous;
}

HE_DATA_END_NAMESPACE
