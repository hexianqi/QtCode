#include "HProtocolDemo_p.h"
#include <QtCore/QVector>
#include <QtCore/QMutex>
#include <QtCore/QLibrary>

HProtocolDemoPrivate::HProtocolDemoPrivate() :
    mutex(new QMutex)
{
}

void HProtocolDemoPrivate::loadDll()
{
//    lib.reset(new QLibrary("CYUSB.dll"));
//    if (!lib->load())
//        return;

//    open = FunOpen(lib->resolve("OpenProtocol"));
//    close = FunClose(lib->resolve("CloseProtocol"));
//    isLoaded = true;
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
    return E_OK;
}

HErrorType HProtocolDemo::setSmooth(int times, int range)
{
    return E_OK;
}

HErrorType HProtocolDemo::setStdCurve(QVector<double> value)
{
    return E_OK;
}

HErrorType HProtocolDemo::getSpectrumSample(QVector<double> &value)
{
    return E_OK;
}

HErrorType HProtocolDemo::getSpectrumEnergy(QPolygonF &value)
{
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
