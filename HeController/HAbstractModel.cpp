#include "HAbstractModel_p.h"
#include "IThread.h"
#include "IThreadCollection.h"
#include "HDelayThread.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/IDeviceCollection.h"
#include "HeData/IConfigManage.h"
#include "HeData/IFileStream.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HAbstractModelPrivate::HAbstractModelPrivate(HAbstractModel *q) :
    q_ptr(q)
{
    initialized = false;
    configFileName = HAppContext::getContextValue<QString>("ConfigFileName");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    devices = HAppContext::getContextPointer<IDeviceCollection>("IDeviceCollection");
    threads = HAppContext::getContextPointer<IThreadCollection>("IThreadCollection");
}

HAbstractModel::HAbstractModel(QObject *parent) :
    IModel(parent),
    d_ptr(new HAbstractModelPrivate(this))
{
}

HAbstractModel::HAbstractModel(HAbstractModelPrivate &p, QObject *parent) :
    IModel(parent),
    d_ptr(&p)
{
}

HAbstractModel::~HAbstractModel()
{
    qDebug() << __func__;
    if (d_ptr->initialized)
    {
        stopDelayThread();
        stopWorkThread();
    }
}

void HAbstractModel::start()
{
    if (d_ptr->initialized)
        return;

    initDelayThread();
    initWorkThread();
    syncMachine(d_ptr->configManage->contain());
    d_ptr->initialized = true;
}

void HAbstractModel::addAction(HActionType action, ulong delay)
{
    if (action >= 0x10000000)
    {
        emit actionFinished(action);
        return;
    }

    if (!d_ptr->devices->isSupport(action))
        return;

    if (delay > 30)
    {
        d_ptr->delayThread->addAction(action, delay);
        return;
    }

    for (auto t : d_ptr->threads->values())
        t->addAction(action);
}

bool HAbstractModel::openFile()
{
    QString fileName;
    if (!d_ptr->configManage->fileStream()->openFile("", ".", &fileName))
        return false;
    setConfigFile(fileName);
    syncTestData(d_ptr->configManage->contain());
    return true;
}

bool HAbstractModel::saveFile()
{
    return d_ptr->configManage->fileStream()->writeFile(d_ptr->configFileName);
}

bool HAbstractModel::saveAsFile()
{
    QString fileName;
    if (!d_ptr->configManage->fileStream()->saveAsFile("", ".", &fileName))
        return false;
    setConfigFile(fileName);
    return true;
}

bool HAbstractModel::importFile(quint32 type)
{
    if (!d_ptr->configManage->importPart(type))
        return false;
    syncTestData(type);
    return true;
}

bool HAbstractModel::exportFile(quint32 type)
{
    return d_ptr->configManage->exportPart(type);
}

void HAbstractModel::setConfigFile(QString fileName)
{
    d_ptr->configFileName = fileName;
    HAppContext::setContextValue("ConfigFileName", fileName);
}

void HAbstractModel::initDelayThread()
{
    d_ptr->delayThread = new HDelayThread(this);
    d_ptr->delayThread->start();
}

void HAbstractModel::stopDelayThread()
{
    d_ptr->delayThread->stop();
}

void HAbstractModel::initWorkThread()
{
    QStringList list;
    for (auto t : d_ptr->threads->values())
    {
        t->setParent(this);
        connect(t, &IThread::startFailed, this, &HAbstractModel::threadStartFailed);
        connect(t, &IThread::startFinished, [=]{ emit threadStateChanged(t->threadInfo(), 1); });
        connect(t, &IThread::stopFinished, [=]{ emit threadStateChanged(t->threadInfo(), 0); });
        connect(t, &IThread::actionFailed, this, &HAbstractModel::actionFailed);
        connect(t, &IThread::actionFinished, this, &HAbstractModel::actionFinished);
        list << t->threadInfo();
    }
    emit threadInitFinished(list);
    for (auto t : d_ptr->threads->values())
        t->start();
}

void HAbstractModel::stopWorkThread()
{
    for (auto t : d_ptr->threads->values())
        t->stop();
}

HE_CONTROLLER_END_NAMESPACE
