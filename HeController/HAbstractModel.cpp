#include "HAbstractModel_p.h"
#include "IThread.h"
#include "HeCommunicate/HDeviceCollection.h"

HE_CONTROLLER_USE_NAMESPACE

HAbstractModelPrivate::HAbstractModelPrivate()
{
 //   devices = new HDeviceCollection();
}

HAbstractModel::HAbstractModel(QObject *parent)
    : IModel(parent), d_ptr(new HAbstractModelPrivate)
{
}

HAbstractModel::HAbstractModel(HAbstractModelPrivate &p, QObject *parent)
    : IModel(parent), d_ptr(&p)
{
}

HAbstractModel::~HAbstractModel()
{
}

void HAbstractModel::initialize(QVariantMap param)
{
    Q_UNUSED(param)
//    if (param.contains("runMode"))
//        d_ptr->runMode = param.value("iRunMode", 2).toInt();
//    if (param.contains("retry"))
//        d_ptr->retry = param.value("retry", 3).toInt();
//    if (param.contains("sleepTime"))
//        d_ptr->sleepTime = param.value("sleepTime", 1000).toUInt();
}

void HAbstractModel::addAction(HActionType action)
{
    if (action >= 0x10000000)
    {
        emit actionFinished(action);
        return;
    }

    if (!d_ptr->devices->isSupport(action))
        return;

    for (auto t : d_ptr->threads)
        t->addAction(action);
}

IDevice *HAbstractModel::device(QString name)
{
    return d_ptr->devices->value(name);
}

void HAbstractModel::initThread()
{
    QStringList list;
    for (auto t : d_ptr->threads.values())
    {
        connect(t, &IThread::startFailed, this, &IModel::deviceFailed);
        connect(t, &IThread::startFinished, [=]{ emit threadStateChanged(t->threadInfo(), 1); });
        connect(t, &IThread::stopFinished, [=]{ emit threadStateChanged(t->threadInfo(), 0); });
        connect(t, &IThread::actionFailed, this, &IModel::actionFailed);
        connect(t, &IThread::actionFinished, this, &IModel::actionFinished);
        list << t->threadInfo();
    }
    emit initThreadFinished(list);
}

void HAbstractModel::startThread()
{
    for (auto t : d_ptr->threads)
        t->start();
}

void HAbstractModel::stopThread()
{
    for (auto t : d_ptr->threads)
        t->stop();
}
