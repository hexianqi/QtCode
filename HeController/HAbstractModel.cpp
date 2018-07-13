#include "HAbstractModel_p.h"
#include "IThread.h"
#include "IThreadCollection.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IDeviceCollection.h"
#include <QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HAbstractModelPrivate::HAbstractModelPrivate(HAbstractModel *q)
    : q_ptr(q)
{
    devices = HAppContext::getContextPointer<IDeviceCollection>("IDeviceCollection");
    threads = HAppContext::getContextPointer<IThreadCollection>("IThreadCollection");
}

HAbstractModel::HAbstractModel(QObject *parent)
    : IModel(parent), d_ptr(new HAbstractModelPrivate(this))
{
}

HAbstractModel::HAbstractModel(HAbstractModelPrivate &p, QObject *parent)
    : IModel(parent), d_ptr(&p)
{
}

HAbstractModel::~HAbstractModel()
{
    qDebug() << __func__;
    stopThread();
}

void HAbstractModel::start()
{
    initThread();
    startThread();
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

    for (auto t : d_ptr->threads->values())
        t->addAction(action);
}

void HAbstractModel::initThread()
{
    QStringList list;
    for (auto t : d_ptr->threads->values())
    {
        t->setParent(this);
        connect(t, &IThread::startFailed, this, &IModel::threadStartFailed);
        connect(t, &IThread::startFinished, [=]{ emit threadStateChanged(t->threadInfo(), 1); });
        connect(t, &IThread::stopFinished, [=]{ emit threadStateChanged(t->threadInfo(), 0); });
        connect(t, &IThread::actionFailed, this, &IModel::actionFailed);
        connect(t, &IThread::actionFinished, this, &IModel::actionFinished);
        list << t->threadInfo();
    }
    emit threadInitFinished(list);
}

void HAbstractModel::startThread()
{
    for (auto t : d_ptr->threads->values())
        t->start();
}

void HAbstractModel::stopThread()
{
    for (auto t : d_ptr->threads->values())
        t->stop();
}

HE_CONTROLLER_END_NAMESPACE
