#include "HSlSimulation_p.h"
#include <QtCore/QtMath>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSlSimulation::HSlSimulation() :
    HAbstractDevice(*new HSlSimulationPrivate)
{
}

HSlSimulation::HSlSimulation(HSlSimulationPrivate &p) :
    HAbstractDevice(p)
{
}

HSlSimulation::~HSlSimulation()
{
    qDebug() << __func__;
}

QString HSlSimulation::typeName()
{
    return "HSlSimulation";
}

HErrorType HSlSimulation::open()
{
    return E_OK;
}

HErrorType HSlSimulation::close()
{
    return E_OK;
}

HErrorType HSlSimulation::setData(HActionType action, QVector<uchar> value, int /*delay*/)
{
    Q_D(HSlSimulation);
    if (action == ACT_SET_INTEGRAL_TIME)
        d->intergalTime = (value[0] + value[1] * 256 + value[2] * 256 * 256 + value[3] * 256 * 256 * 256) / 1000.0;
    return E_OK;
}

HErrorType HSlSimulation::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    if (action == ACT_GET_SPECTRUM)
    {
        value.clear();
        for (int i = 0; i < 2304; i++)
        {
            int v = static_cast<int>(simulate(i));
            value << static_cast<uchar>(v % 256);
            value << static_cast<uchar>(v / 256);
        }
    }
    return E_OK;
}

double HSlSimulation::simulate(double v)
{
    Q_D(HSlSimulation);
    if (v < 50)
        return 1000;

    auto r = qDegreesToRadians(180.0 * v / 2304);
    auto k = 600 * d->intergalTime;
    auto t = k * qSin(r);
//    auto p = 1 + ((qrand() % 2000) - 1000) / 100000.0;                    // 1%误差
//    auto p = (qrand() % 2000) - 1000;                                     // [-1000, 1000]误差
//    auto p = 0.9 + qSin(qDegreesToRadians(d->intergalTime * 1.8)) * 0.1;    // 和积分时间成sin曲线关系
    auto p = 0.9 + qSin(qDegreesToRadians(t * 180 / 60000)) * 0.1;          // 和采样值成sin曲线关系
    return t * p + 1000;
}

HE_COMMUNICATE_END_NAMESPACE
