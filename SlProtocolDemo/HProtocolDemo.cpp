#include "HProtocolDemo_p.h"
#include <QtCore/QVector>
#include <QtCore/QMutex>
#include <QtCore/QLibrary>
#include <QtGui/QPolygonF>

HProtocolDemoPrivate::HProtocolDemoPrivate() :
    mutex(new QMutex)
{
}

void HProtocolDemoPrivate::loadDll()
{
    lib.reset(new QLibrary("ProtocolSl.dll"));
    if (!lib->load())
        return;

    open = FunOpen(lib->resolve("OpenProtocol"));
    close = FunClose(lib->resolve("CloseProtocol"));
    setIntegralTime = FunSetIntegralTime(lib->resolve("SetIntegralTime"));
    setSmooth = FunSetSmooth(lib->resolve("SetSmooth"));
    getSpectrumSample = FunGetSpectrumSample(lib->resolve("GetSpectrumSample"));
    getSpectrumEnergy = FunGetSpectrumEnergy(lib->resolve("GetSpectrumEnergy"));
    pelsToWave = FunPelsToWave(lib->resolve("PelsToWave"));
    setStdCurve = FunSetStdCurve(lib->resolve("SetStdCurve"));
    isLoaded = true;
}

void HProtocolDemoPrivate::unloadDLL()
{
    if (lib == nullptr)
        return;
    lib->unload();
    isLoaded = false;
}

HProtocolDemo::HProtocolDemo() :
    d_ptr(new HProtocolDemoPrivate)
{
    d_ptr->loadDll();
}

HProtocolDemo::~HProtocolDemo()
{
    close();
    d_ptr->unloadDLL();
}

void HProtocolDemo::initialize(QVariantMap /*param*/)
{

}

QString HProtocolDemo::typeName()
{
    return "HProtocolDemo";
}

void HProtocolDemo::setDevice(IDevice *)
{
}

HErrorType HProtocolDemo::open()
{
    QMutexLocker locker(d_ptr->mutex);
    if (!d_ptr->isLoaded || !d_ptr->open())
        return E_DEVICE_INVALID;
    return E_OK;
}

HErrorType HProtocolDemo::close()
{
    if (d_ptr->isLoaded)
        d_ptr->close();
    return E_OK;
}

HErrorType HProtocolDemo::setIntegralTime(double value)
{
    if (!d_ptr->setIntegralTime(value))
        return E_DEVICE_INVALID;
    return E_OK;
}

HErrorType HProtocolDemo::setSmooth(int times, int range)
{
    if (!d_ptr->setSmooth(times, range))
        return E_DEVICE_INVALID;
    return E_OK;
}

HErrorType HProtocolDemo::setStdCurve(QVector<double> value)
{
    if (!d_ptr->setStdCurve(value.data(), value.size()))
        return E_DEVICE_INVALID;
    return E_OK;
}

HErrorType HProtocolDemo::getSpectrumSample(QVector<double> &value)
{
    int buff[3000];
    int size = 3000;
    double temp;

    if (!d_ptr->getSpectrumSample(buff, &size, &temp, true))
        return E_DEVICE_INVALID;
    value.clear();
    for (int i = 0; i < size; i++)
        value << buff[i] * 1.0;
    return E_OK;
}

HErrorType HProtocolDemo::getSpectrumEnergy(QPolygonF &value, double *percent)
{
    double buff[3000];
    int size = 3000;

    if (!d_ptr->getSpectrumEnergy(buff, &size, percent))
        return E_DEVICE_INVALID;
    value.clear();
    for (int i = 0; i < size; i++)
        value << QPointF(d_ptr->pelsToWave(i), buff[i]);
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, int, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, uchar, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, uint, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, QVector<int>, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, QVector<uchar>, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::setData(HActionType, QVector<uint>, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, int &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, uchar &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, uint &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, QVector<int> &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, QVector<uchar> &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, QVector<uint> &, int)
{
    return E_OK;
}

HErrorType HProtocolDemo::getData(HActionType, QVector<double> &, int)
{
    return E_OK;
}
