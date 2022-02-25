#include "HAbstractModel_p.h"
#include "IThread.h"
#include "IThreadCollection.h"
#include "HDelayThread.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/IStream.h"

HE_BEGIN_NAMESPACE

HAbstractModelPrivate::HAbstractModelPrivate()
{
    initialized = false;
    configFileName = HAppContext::getContextValue<QString>("ConfigFileName");
    configManage = HAppContext::getContextPointer<IConfigManage>("IConfigManage");
    threads = HAppContext::getContextPointer<IThreadCollection>("IThreadCollection");
}

HAbstractModel::HAbstractModel(QObject *parent) :
    IModel(parent),
    d_ptr(new HAbstractModelPrivate)
{
}

HAbstractModel::HAbstractModel(HAbstractModelPrivate &p, QObject *parent) :
    IModel(parent),
    d_ptr(&p)
{
}

HAbstractModel::~HAbstractModel()
{
    if (d_ptr->initialized)
    {
        stopDelayThread();
        stopWorkThread();
    }
}

void HAbstractModel::initialize(QVariantMap /*param*/)
{
}

void HAbstractModel::start()
{
    if (d_ptr->initialized)
        return;

    initDelayThread();
    initWorkThread();
    syncDeviceAll();
    d_ptr->initialized = true;
}

void HAbstractModel::addAction(HActionType action, ulong delay)
{
    if (action >= 0xE0000000)
    {
        emit actionFinished(action);
        return;
    }

    if (delay > 30)
    {
        d_ptr->delayThread->addAction(action, delay);
        return;
    }

    for (auto t : d_ptr->threads->values())
        t->addAction(action);
}

void HAbstractModel::syncDeviceAll()
{
    syncDevice(d_ptr->configManage->contain());
}

bool HAbstractModel::openFile()
{
    QString fileName;
    if (!d_ptr->configManage->stream()->openFile("", ".", &fileName))
        return false;
    setConfigFile(fileName);
    syncTestData(d_ptr->configManage->contain());
    return true;
}

bool HAbstractModel::saveFile()
{
    return d_ptr->configManage->stream()->writeFile(d_ptr->configFileName);
}

bool HAbstractModel::saveAsFile()
{
    QString fileName;
    if (!d_ptr->configManage->stream()->saveAsFile("", ".", &fileName))
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

void HAbstractModel::setConfigFile(const QString &/*fileName*/)
{
//    d_ptr->configFileName = fileName;
//    HAppContext::setContextValue("ConfigFileName", fileName);
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
        connect(t, &IThread::startFinished, this, [=]{ emit threadStateChanged(t->threadInfo(), 1); });
        connect(t, &IThread::stopFinished, this, [=]{ emit threadStateChanged(t->threadInfo(), 0); });
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

HE_END_NAMESPACE
