#include "HAbstractThread_p.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QSettings>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutexLocker>

HE_CONTROLLER_BEGIN_NAMESPACE

HAbstractThreadPrivate::HAbstractThreadPrivate()
{
    mutex = new QMutex;
    waitConditionAction = new QWaitCondition;
}

void HAbstractThreadPrivate::enqueueAction(HActionType action)
{
    QMutexLocker locker(mutex);
    actionCache.enqueue(action);
    waitConditionAction->wakeOne();
}

HActionType HAbstractThreadPrivate::dequeueAction()
{
    QMutexLocker locker(mutex);
    if (actionCache.isEmpty())
        waitConditionAction->wait(mutex);
    return actionCache.dequeue();
}

void HAbstractThreadPrivate::clearAction()
{
    QMutexLocker locker(mutex);
    actionCache.clear();
}

HAbstractThread::HAbstractThread(QObject *parent) :
    IThread(parent),
    d_ptr(new HAbstractThreadPrivate)
{
}

HAbstractThread::HAbstractThread(HAbstractThreadPrivate &p, QObject *parent) :
    IThread(parent),
    d_ptr(&p)
{
}

HAbstractThread::~HAbstractThread()
{
    writeSettings();
    stop();
}

void HAbstractThread::initialize(QVariantMap /*param*/)
{
    readSettings();
}

void HAbstractThread::stop()
{
    if (!d_ptr->running)
        return;
    d_ptr->clearAction();
    d_ptr->enqueueAction(ACT_EXIT);
    wait(1000);
}

void HAbstractThread::addAction(HActionType action)
{
    if (!checkAction(action))
        return;
    d_ptr->enqueueAction(action);
}

void HAbstractThread::clearAction()
{
    d_ptr->clearAction();
}

void HAbstractThread::run()
{
    d_ptr->running = true;
    if (d_ptr->runMode == 0)
        debugMode();
    if (d_ptr->runMode == 1)
        offlineMode();
    if (d_ptr->runMode == 2)
        normalMode();
    d_ptr->running = false;
}

bool HAbstractThread::checkAction(HActionType action)
{
    return action < 0x00000100 || isSupport(action);
}

HErrorType HAbstractThread::handleAction(HActionType action)
{
    for (auto v : d_ptr->strategys)
    {
        if (v->isSupport(action))
            return v->handle(action);
    }
    return E_THREAD_NO_HANDLE;
}

bool HAbstractThread::isSupport(HActionType action)
{
    if (d_ptr->actionSupport.contains(action))
        return true;
    for (auto v : d_ptr->strategys)
    {
        if (v->isSupport(action))
            return true;
    }
    return false;
}

void HAbstractThread::debugMode()
{
    HActionType action;
    HErrorType error;

    openProtocol();
    forever
    {
        action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        error = handleAction(action);
        if (error != E_OK)
            emit actionFailed(action, error);
        emit actionFinished(action);
    }
    closeProtocol();
}

void HAbstractThread::offlineMode()
{
    forever
    {
        auto action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        emit actionFinished(action);
    }
}

void HAbstractThread::normalMode()
{
    int i;
    HActionType action;
    HErrorType error;

    if (!openProtocol())
        return;

    error = E_OK;
    forever
    {
        action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;
        for (i = 0; i < d_ptr->retry; i++)
        {
            error = handleAction(action);
            if (error == E_OK)
            {
                emit actionFinished(action);
                break;
            }
            msleep(d_ptr->sleepTime);
        }
        if (i >= d_ptr->retry)
        {
            emit actionFailed(action, error);
            break;
        }
    }
    closeProtocol();
}

bool HAbstractThread::openProtocol()
{
    QList<IProtocol *> list;
    for (auto i = d_ptr->protocols.begin(); i != d_ptr->protocols.end(); i++)
    {
        auto error = i.value()->open();
        if (error != E_OK)
        {
            for (auto item : list)
                item->close();
            emit startFailed(tr("\n设备“%1”连接失败！错误原因“%2”。\n").arg(i.key(), HCore::toComment(error)));
            return false;
        }
        list.append(i.value());
    }
    emit startFinished();
    return true;
}

void HAbstractThread::closeProtocol()
{
    for (auto p : d_ptr->protocols)
        p->close();
    emit stopFinished();
}

void HAbstractThread::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("Thread");
    d_ptr->runMode = settings->value("iRunMode", 2).toInt();
    d_ptr->retry = settings->value("iRetry", 3).toInt();
    d_ptr->sleepTime = settings->value("iSleepTime", 1000).toUInt();
    settings->endGroup();
}

void HAbstractThread::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->beginGroup("Thread");
    settings->setValue("iRunMode", d_ptr->runMode);
    settings->setValue("iRetry", d_ptr->retry);
    settings->setValue("iSleepTime", d_ptr->sleepTime);
    settings->endGroup();
}

HE_CONTROLLER_END_NAMESPACE
