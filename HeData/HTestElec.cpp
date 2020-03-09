#include "HTestElec_p.h"
#include "IElecCalibrate.h"
#include "IElecCalibrateCollection.h"
#include "IElecCalibrateItemCollection.h"
#include <QtCore/QVector>

HE_DATA_BEGIN_NAMESPACE

HTestElec::HTestElec() :
    ITestElec(*new HTestElecPrivate)
{
}

HTestElec::HTestElec(HTestElecPrivate &p) :
    ITestElec(p)
{
}

HTestElec::~HTestElec()
{
}

QString HTestElec::typeName()
{
    return "HTestElec";
}

bool HTestElec::setCalibrate(IElecCalibrateCollection *p)
{
    Q_D(HTestElec);
    if (p->size() < 1)
        return false;
    d->collection = p;
    setModule(d->module);
    return true;
}

void HTestElec::setModule(int value)
{
    Q_D(HTestElec);
    d->module = qBound(0, value, d->collection->size() - 1);
    d->calibrate = d->collection->itemAt(value);
    setData("[电模块]", d->module);
}

void HTestElec::setModule(QString value)
{
    Q_D(HTestElec);
    setModule(d->collection->keys().indexOf(value));
}

void HTestElec::setGears(HElecType type, int value)
{
    Q_D(HTestElec);
    value = qBound(0, value, d->calibrate->itemCollection(type)->size() - 1);
    if (type == OutputVoltage)
        setData("[输出电压_档位]", value);
    if (type == OutputCurrent)
        setData("[输出电流_档位]", value);
    if (type == MeasuredVoltage)
        setData("[实测电压_档位]", value);
    if (type == MeasuredCurrent)
        setData("[实测电流_档位]", value);
    if (type == ReverseVoltage)
        setData("[反向电压_档位]", value);
    if (type == ReverseCurrent)
        setData("[反向漏流_档位]", value);
    d->gears.insert(type, value);
}

void HTestElec::setParam(HElecType type, double value)
{
    Q_D(HTestElec);
    if (type == OutputVoltage)
    {
        setData("[输出电压]", value);
        setData("[输出电压_F]", d->calibrate->toFiction(value, type, gears(type)));
    }
    if (type == OutputCurrent)
    {
        setData("[输出电流]", value);
        setData("[输出电流_F]", d->calibrate->toFiction(value, type, gears(type)));
    }
    if (type == MeasuredVoltage)
    {
        setData("[实测电压_F]", value);
        setData("[实测电压]", d->calibrate->toReal(value, type, gears(type)));
        setData("[电功率]" , data("[实测电流]").toDouble() * data("[实测电流]").toDouble() / 1000.0);
    }
    if (type == MeasuredCurrent)
    {
        setData("[实测电流_F]", value);
        setData("[实测电流]", d->calibrate->toReal(value, type, gears(type)));
        setData("[电功率]" , data("[实测电流]").toDouble() * data("[实测电流]").toDouble() / 1000.0);
    }
    if (type == ReverseVoltage)
    {
        setData("[反向电压]", value);
        setData("[反向电压_F]", d->calibrate->toFiction(value, type, gears(type)));
    }
    if (type == ReverseCurrent)
    {
        setData("[反向漏流_F]", value);
        setData("[反向漏流]", d->calibrate->toReal(value, type, gears(type)));
    }
}

void HTestElec::setSample(QVector<int> value)
{
    if (value.size() > 0)
        setParam(MeasuredVoltage, value.at(0));
    if (value.size() > 1)
        setParam(MeasuredCurrent, value.at(1));
    if (value.size() > 2)
        setParam(ReverseCurrent, value.at(2));
}

int HTestElec::gears(HElecType type)
{
    Q_D(HTestElec);
    return d->gears.value(type, 0);
}

HE_DATA_END_NAMESPACE
