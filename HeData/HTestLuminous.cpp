#include "HTestLuminous_p.h"
#include "ILuminousCalibrate.h"
#include "ILuminousCalibrateCollection.h"

HE_DATA_BEGIN_NAMESPACE

HTestLuminousPrivate::HTestLuminousPrivate()
{
    addData("[光模块]", 0);
    addData("[光档位数]", 0);
    addData("[光测试类型]", "[光通量]");
    addData("[光通道]", 2);
    addData("[光档位]", 0);
    addData("[光采样值]", 0);
    addData("[光采样比率]", 0.0);
}

HTestLuminous::HTestLuminous() :
    ITestLuminous(*new HTestLuminousPrivate)
{
}

HTestLuminous::HTestLuminous(HTestLuminousPrivate &p) :
    ITestLuminous(p)
{
}

QString HTestLuminous::typeName()
{
    return "HTestLuminous";
}

void HTestLuminous::setData(QString type, QVariant value)
{
    if (type == "[光模块]")
        return setModule(value.toInt());
    if (type == "[光测试类型]")
        return setType(value.toString());
    if (type == "[光档位]")
        return setGears(value.toInt());
    if (type == "[光采样值]")
        return setSample(value.toInt());
    return ITestLuminous::setData(type, value);
}

bool HTestLuminous::setCalibrate(ILuminousCalibrateCollection *p)
{
    Q_D(HTestLuminous);
    if (p->size() < 1)
        return false;
    d->collection = p;
    setModule(0);
    return true;
}

QVariant HTestLuminous::handleOperation(QString type, QVariant value)
{
    if (type == "<匹配光档位>")
        return matchGears();
    return HTestData::handleOperation(type, value);
}

void HTestLuminous::setModule(int value)
{
    Q_D(HTestLuminous);
    value = qBound(0, value, d->collection->size() - 1);
    d->calibrate = d->collection->itemAt(value);
    d->setData("[光模块]", value);
    d->setData("[光档位数]", d->calibrate->totalGears());
    for (auto k : d->calibrate->keys())
        d->addData(k, 0);
}

void HTestLuminous::setType(QString value)
{
    Q_D(HTestLuminous);
    if (!d->calibrate->contains(value))
        return;
    d->setData("[光测试类型]", value);
    d->setData("[光通道]", value == "[光亮度]" || value == "[光强度]" ? 1 : 2);
}

void HTestLuminous::setGears(int value)
{
    Q_D(HTestLuminous);
    value = qBound(0, value, d->calibrate->totalGears() - 1);
    d->setData("[光档位]", value);
}

void HTestLuminous::setSample(double value)
{
    Q_D(HTestLuminous);
    auto type = data("[光测试类型]").toString();
    auto gears = data("[光档位]").toInt();
    d->setData("[光采样值]", value);
    d->setData("[光采样比率]", value / 655.35);
    d->setData(type, d->calibrate->toReal(value, type, gears));
}

bool HTestLuminous::matchGears()
{
    Q_D(HTestLuminous);

    auto sample = data("[光采样值]").toDouble();
    if (sample >= 6000 && sample <= 61000)
        return false;

    auto gears = data("[光档位]").toInt();
    if (sample < 6000)
        gears += 1;
    if (sample > 61000)
        gears -= 1;
    if (gears < 0 || gears >= d->calibrate->totalGears())
        return false;

    d->setData("[光档位]", gears);
    return true;
}

HE_DATA_END_NAMESPACE
