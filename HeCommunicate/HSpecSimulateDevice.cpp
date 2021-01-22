#include "HSpecSimulateDevice_p.h"
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSpecSimulateDevice::HSpecSimulateDevice() :
    HAbstractSimulateDevice(*new HSpecSimulateDevicePrivate)
{
}

HSpecSimulateDevice::HSpecSimulateDevice(HSpecSimulateDevicePrivate &p) :
    HAbstractSimulateDevice(p)
{
}

HSpecSimulateDevice::~HSpecSimulateDevice()
{
    qDebug() << __func__;
}

QString HSpecSimulateDevice::typeName()
{
    return "HSpecSimulateDevice";
}

bool HSpecSimulateDevice::setData(HActionType action, QVector<uchar> value, int /*delay*/)
{
    Q_D(HSpecSimulateDevice);
    if (action == ACT_SET_INTEGRAL_TIME)
        d->intergalTime = (value[0] + (value[1] << 8) + (value[2] << 16) + (value[3] << 24)) / 1000.0;
    return true;
}

bool HSpecSimulateDevice::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    if (action == ACT_GET_SPECTRUM)
    {
        value.clear();
        for (int i = 0; i < 2304; i++)
        {
            auto v = int(simulate(i));
            value << uchar(v % 256);
            value << uchar(v / 256);
        }
    }
    return true;
}

double HSpecSimulateDevice::simulate(double value)
{
    Q_D(HSpecSimulateDevice);
    QRandomGenerator rg;
    if (value < 50)
        return 1000;
//    return rg.bounded(1000, 61000);     // 方法1：范围[1000, 61000]内随机

    // 方法2：与积分时间、采样点相关
    auto r = qDegreesToRadians(180.0 * value / 2304);   // 0-180度
    auto k = 600 * d->intergalTime;                     // 振幅
    auto t = k * qSin(r);
//    auto p = rg.bounded(-1000, 1000);                                       // [-1000, 1000]误差
//    auto p = 1 + rg.bounded(-1000, 1000) / 100000.0;                        // 1%误差
//    auto p = 0.9 + qSin(qDegreesToRadians(d->intergalTime * 1.8)) * 0.1;    // 误差和积分时间成sin曲线关系
    auto p = 0.9 + qSin(qDegreesToRadians(t * 180 / 60000)) * 0.1;            // 误差和采样值成sin曲线关系
    return t * p + 1000;
}

HE_COMMUNICATE_END_NAMESPACE
