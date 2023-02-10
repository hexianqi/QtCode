#include "HTestData1000RGB_p.h"

HTestData1000RGBPrivate::HTestData1000RGBPrivate()
{
    sourceIo.fill(0, 5);
    outputCurrentF.fill(0, 4);
    outputCurrentR.fill(0, 4);
    addData("[电模块]", 0);
    addData("[电源模式]", 0);
    addData("[电源开关]", QVariant::fromValue(sourceIo));
    addData("[电流_档位数]", 2);
    addData("[电流_档位]", 0);
    addData("[输出电压]", 0.0);
    addData("[输出电压_F]", 0.0);
    addData("[反向电压]", 0.0);
    addData("[反向电压_F]", 0.0);
    addData("[实测电压_F]", 0.0);
    addData("[实测电流_F]", 0.0);
    addData("[反向漏流_F]", 0.0);
    addData("[输出电流-R]", 0.0);
    addData("[输出电流-G]", 0.0);
    addData("[输出电流-B]", 0.0);
    addData("[输出电流-W]", 0.0);
    addData("[实测电压-R]", 0.0);
    addData("[实测电压-G]", 0.0);
    addData("[实测电压-B]", 0.0);
    addData("[实测电压-W]", 0.0);
    addData("[实测电流-R]", 0.0);
    addData("[实测电流-G]", 0.0);
    addData("[实测电流-B]", 0.0);
    addData("[实测电流-W]", 0.0);
    addData("[反向漏流-R]", 0.0);
    addData("[反向漏流-G]", 0.0);
    addData("[反向漏流-B]", 0.0);
    addData("[反向漏流-W]", 0.0);
}

HTestData1000RGB::HTestData1000RGB() :
    HTestData(*new HTestData1000RGBPrivate)
{
}

QString HTestData1000RGB::typeName()
{
    return "HTestRGB";
}

bool HTestData1000RGB::setCalibrate(void *p)
{
    Q_D(HTestData1000RGB);
    auto c = static_cast<IElecCalibrateCollection *>(p);
    if (c == nullptr || c->size() < 1)
        return false;
    d->collection = c;
    setModule(0);
    setCurrentGears(0);
    return true;
}

bool HTestData1000RGB::setData(QString type, QVariant value)
{
    Q_D(HTestData1000RGB);
    if (type == "[电模块]")
        return setModule(value.toInt());
    if (type == "[电源开关]")
    {
        auto v = value.value<QVector<int>>();
        if (v.size() < 5)
            return false;
        d->sourceIo = v;
        d->setData("[电源开关]", value);
    }
    if (type == "[输出电流_档位]" || type == "[实测电流_档位]")
        return setCurrentGears(value.toInt());
    if (type =="[电流_档位]")
    {
        d->currentGears = value.toDouble();
        d->setData("[电流_档位]", d->currentGears);
        syncCurrent();
        return true;
    }
    if (type == "[输出电压]")
    {
        auto v = value.toDouble();
        d->setData("[输出电压]", v);
        d->setData("[输出电压_F]", d->calibrate->toFiction(v, OutputVoltage, 0));
        return true;
    }
    if (type == "[反向电压]")
    {
        auto v = value.toDouble();
        d->setData("[反向电压]", v);
        d->setData("[反向电压_F]", d->calibrate->toFiction(v, ReverseVoltage, 0));
        return true;
    }
    if (type == "[输出电流_F]")
    {
        auto v = value.toDouble();
        for (int i = 0; i < 4; i++)
            d->outputCurrentF[i] = v;
        return true;
    }
    if (type == "[输出电流]")
    {
        auto v = value.toDouble();
        for (int i = 0; i < 4; i++)
            d->outputCurrentR[i] = v;
        setData("[输出电流-R]", d->outputCurrentR[0]);
        setData("[输出电流-G]", d->outputCurrentR[1]);
        setData("[输出电流-B]", d->outputCurrentR[2]);
        setData("[输出电流-W]", d->outputCurrentR[3]);
        syncCurrent();
        return true;
    }
    if (type == "[输出电流-RGBW]")
    {
        auto v = value.value<QVector<double>>();
        if (v.size() < 4)
            return false;
        d->outputCurrentR = v;
        setData("[输出电流-R]", d->outputCurrentR[0]);
        setData("[输出电流-G]", d->outputCurrentR[1]);
        setData("[输出电流-B]", d->outputCurrentR[2]);
        setData("[输出电流-W]", d->outputCurrentR[3]);
        syncCurrent();
        return true;
    }
    if (type == "[实测电压-RGBW_F]")
    {
        auto v = toReal(MeasuredVoltage, value, "[实测电压_F]");
        setData("[实测电压-R]", v[0]);
        setData("[实测电压-G]", v[1]);
        setData("[实测电压-B]", v[2]);
        setData("[实测电压-W]", v[3]);
        return true;
    }
    if (type == "[实测电流-RGBW_F]")
    {
        auto v = toReal(MeasuredCurrent, value, "[实测电流_F]", true);
        setData("[实测电流-R]", v[0]);
        setData("[实测电流-G]", v[1]);
        setData("[实测电流-B]", v[2]);
        setData("[实测电流-W]", v[3]);
        return true;
    }
    if (type == "[反向漏流-RGBW_F]")
    {
        auto v = toReal(ReverseCurrent, value, "[反向漏流_F]");
        setData("[反向漏流-R]", v[0]);
        setData("[反向漏流-G]", v[1]);
        setData("[反向漏流-B]", v[2]);
        setData("[反向漏流-W]", v[3]);
        return true;
    }
    return HTestData::setData(type, value);
}

QVariant HTestData1000RGB::data(QString type)
{
    Q_D(HTestData1000RGB);
    if (type == "[输出电流-RGBW_F]")
        return QVariant::fromValue(d->outputCurrentF);
    return HTestData::data(type);
}

bool HTestData1000RGB::setModule(int value)
{
    Q_D(HTestData1000RGB);
    value = qBound(0, value, d->collection->size() - 1);
    d->calibrate = d->collection->itemAt(value);
    d->setData("[电模块]", value);
    return true;
}

bool HTestData1000RGB::setCurrentGears(int value)
{
    Q_D(HTestData1000RGB);
    if (value < 0 || value > 16)
        return false;
    d->currentGears = value % 2;
    d->sourceIo.fill(0, 5);
    d->sourceIo[0] = value / 8;
    d->sourceIo[(value / 2) % 4 + 1] = 1;
    d->setData("[电流_档位]", d->currentGears);
    d->setData("[电源开关]", QVariant::fromValue(d->sourceIo));
    return true;
}

QVector<double> HTestData1000RGB::toReal(HElecType type, QVariant value, QString name, bool calcIndex)
{
    Q_D(HTestData1000RGB);
    QVector<double> result(4, 0);
    auto v = value.value<QVector<int>>();
    if (v.size() < 4)
        return result;
    for (int i = 0; i < 4; i++)
    {
        if (d->sourceIo.at(i + 1) == 1)
        {
            auto index = calcIndex ? d->sourceIo[0] * 8 + i * 2 + d->currentGears : 0;
            d->setData(name, v[i]);
            result[i] = d->calibrate->toReal(v[i], type, index);
        }
    }
    return result;
}

void HTestData1000RGB::syncCurrent()
{
    Q_D(HTestData1000RGB);
    for (int i = 0; i < 4; i++)
    {
        auto index = d->sourceIo[0] * 8 + i * 2 + d->currentGears;
        d->outputCurrentF[i] = d->calibrate->toFiction(d->outputCurrentR[i], OutputCurrent, index);
    }
}
