#include "HTestElec_p.h"
#include "IElecCalibrate.h"
#include "IElecCalibrateCollection.h"
#include "IElecCalibrateItemCollection.h"
#include <QtCore/QVector>

HE_DATA_BEGIN_NAMESPACE

HTestElecPrivate::HTestElecPrivate()
{
    addData("[电模块]", 0);
    addData("[电源模式]", 0);
    addData("[输出电压_档位]", 0);
    addData("[输出电流_档位]", 0);
    addData("[实测电压_档位]", 0);
    addData("[实测电流_档位]", 0);
    addData("[反向电压_档位]", 0);
    addData("[反向漏流_档位]", 0);
    addData("[输出电压]", 0.0);
    addData("[输出电流]", 0.0);
    addData("[实测电压]", 0.0);
    addData("[实测电流]", 0.0);
    addData("[反向电压]", 0.0);
    addData("[反向漏流]", 0.0);
    addData("[电功率]", 0.0);
    addData("[输出电压_F]", 0.0);
    addData("[输出电流_F]", 0.0);
    addData("[实测电压_F]", 0.0);
    addData("[实测电流_F]", 0.0);
    addData("[反向电压_F]", 0.0);
    addData("[反向漏流_F]", 0.0);
    addData("[触发状态]", 0);
}

HTestElec::HTestElec() :
    ITestElec(*new HTestElecPrivate)
{
}

HTestElec::HTestElec(HTestElecPrivate &p) :
    ITestElec(p)
{
}

QString HTestElec::typeName()
{
    return "HTestElec";
}

void HTestElec::setData(QString type, QVariant value)
{
    if (type == "[电模块]")
        return setModule(value.toInt());
    if (type == "[输出电压_档位]")
        return setGears(OutputVoltage, value.toInt());
    if (type == "[输出电流_档位]")
        return setGears(OutputCurrent, value.toInt());
    if (type == "[实测电压_档位]")
        return setGears(MeasuredVoltage, value.toInt());
    if (type == "[实测电流_档位]")
        return setGears(MeasuredCurrent, value.toInt());
    if (type == "[反向电压_档位]")
        return setGears(ReverseVoltage, value.toInt());
    if (type == "[反向漏流_档位]")
        return setGears(ReverseCurrent, value.toInt());
    if (type == "[输出电压]")
        return setParam(OutputVoltage, value.toDouble());
    if (type == "[输出电流]")
        return setParam(OutputCurrent, value.toDouble());
    if (type == "[反向电压]")
        return setParam(ReverseVoltage, value.toDouble());
    if (type == "[实测电压_F]")
        return setParam(MeasuredVoltage, value.toDouble());
    if (type == "[实测电流_F]")
        return setParam(MeasuredCurrent, value.toDouble());
    if (type == "[反向漏流_F]")
        return setParam(ReverseCurrent, value.toDouble());
    return ITestElec::setData(type, value);
}

bool HTestElec::setCalibrate(IElecCalibrateCollection *p)
{
    Q_D(HTestElec);
    if (p->size() < 1)
        return false;
    d->collection = p;
    setModule(0);
    return true;
}

void HTestElec::setModule(int value)
{
    Q_D(HTestElec);
    value = qBound(0, value, d->collection->size() - 1);
    d->calibrate = d->collection->itemAt(value);
    d->setData("[电模块]", value);
}

void HTestElec::setGears(HElecType type, int value)
{
    Q_D(HTestElec);
    value = qBound(0, value, d->calibrate->itemCollection(type)->size() - 1);
    if (type == OutputVoltage)
        d->setData("[输出电压_档位]", value);
    if (type == OutputCurrent)
        d->setData("[输出电流_档位]", value);
    if (type == MeasuredVoltage)
        d->setData("[实测电压_档位]", value);
    if (type == MeasuredCurrent)
        d->setData("[实测电流_档位]", value);
    if (type == ReverseVoltage)
        d->setData("[反向电压_档位]", value);
    if (type == ReverseCurrent)
        d->setData("[反向漏流_档位]", value);
    d->gears.insert(type, value);
    calcRelation(type);
}

void HTestElec::setParam(HElecType type, double value)
{
    Q_D(HTestElec);
    if (type == OutputVoltage)
        d->setData("[输出电压]", value);
    if (type == OutputCurrent)
        d->setData("[输出电流]", value);
    if (type == ReverseVoltage)
        d->setData("[反向电压]", value);
    if (type == MeasuredVoltage)
        d->setData("[实测电压_F]", value);
    if (type == MeasuredCurrent)
        d->setData("[实测电流_F]", value);
    if (type == ReverseCurrent)
        d->setData("[反向漏流_F]", value);
    d->values.insert(type, value);
    calcRelation(type);
}

void HTestElec::calcRelation(HElecType type)
{
    Q_D(HTestElec);
    auto value = d->values.value(type, 0);
    auto gears = d->gears.value(type, 0);
    if (type == OutputVoltage)
        d->setData("[输出电压_F]", d->calibrate->toFiction(value, type, gears));
    if (type == OutputCurrent)
        d->setData("[输出电流_F]", d->calibrate->toFiction(value, type, gears));
    if (type == ReverseVoltage)
        d->setData("[反向电压_F]", d->calibrate->toFiction(value, type, gears));
    if (type == MeasuredVoltage)
    {
        d->setData("[实测电压]", d->calibrate->toReal(value, type, gears));
        d->setData("[电功率]" , data("[实测电压]").toDouble() * data("[实测电流]").toDouble() / 1000.0);
    }
    if (type == MeasuredCurrent)
    {
        d->setData("[实测电流]", d->calibrate->toReal(value, type, gears));
        d->setData("[电功率]" , data("[实测电压]").toDouble() * data("[实测电流]").toDouble() / 1000.0);
    }
    if (type == ReverseCurrent)
        d->setData("[反向漏流]", d->calibrate->toReal(value, type, gears));
}

HE_DATA_END_NAMESPACE
