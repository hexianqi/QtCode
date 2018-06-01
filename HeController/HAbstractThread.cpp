#include "HAbstractThread_p.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeCommunicate/IProtocol.h"
#include <QSettings>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HAbstractThreadPrivate::HAbstractThreadPrivate(HAbstractThread *q)
    : q_ptr(q)
{
    mutex = new QMutex;
    waitConditionAction = new QWaitCondition;
}

void HAbstractThreadPrivate::enqueueAction(HActionType action)
{
    QMutexLocker locker(mutex);
    actionQueue.enqueue(action);
    waitConditionAction->wakeOne();
}

HActionType HAbstractThreadPrivate::dequeueAction()
{
    QMutexLocker locker(mutex);
    if (actionQueue.isEmpty())
        waitConditionAction->wait(mutex);
    return actionQueue.dequeue();
}

void HAbstractThreadPrivate::clearAction()
{
    QMutexLocker locker(mutex);
    actionQueue.clear();
}

HAbstractThread::HAbstractThread(QObject *parent)
    : IThread(parent), d_ptr(new HAbstractThreadPrivate(this))
{
    readSettings();
}

HAbstractThread::HAbstractThread(HAbstractThreadPrivate &p, QObject *parent)
    : IThread(parent), d_ptr(&p)
{
    readSettings();
}

HAbstractThread::~HAbstractThread()
{
    qDebug() << __func__;
    writeSettings();
    stop();
}

void HAbstractThread::initialize(QVariantMap param)
{
    if (param.contains("runMode"))
        d_ptr->runMode = param.value("iRunMode", 2).toInt();
    if (param.contains("retry"))
        d_ptr->retry = param.value("retry", 3).toInt();
    if (param.contains("sleepTime"))
        d_ptr->sleepTime = param.value("sleepTime", 1000).toUInt();
}

void HAbstractThread::stop()
{
    if (!d_ptr->running)
        return;
    clearAction();
    addAction(ACT_EXIT);
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
        offLineMode();
    if (d_ptr->runMode == 2)
        normalMode();
    d_ptr->running = false;
}

bool HAbstractThread::checkAction(HActionType action)
{
    return action < 0x00000100 || d_ptr->actionSupport.contains(action);
}

void HAbstractThread::readSettings()
{
    auto settings = new QSettings(HAppContext::getContextValue<QString>("Settings"), QSettings::IniFormat, this);
    settings->beginGroup("Thread");
    d_ptr->runMode = settings->value("iRunMode", 2).toInt();
    d_ptr->retry = settings->value("iRetry", 3).toInt();
    d_ptr->sleepTime = settings->value("iSleepTime", 1000).toUInt();
    settings->endGroup();
}

void HAbstractThread::writeSettings()
{
    auto settings = new QSettings(HAppContext::getContextValue<QString>("Settings"), QSettings::IniFormat, this);
    settings->beginGroup("Thread");
    settings->setValue("iRunMode", d_ptr->runMode);
    settings->setValue("iRetry", d_ptr->retry);
    settings->setValue("iSleepTime", d_ptr->sleepTime);
    settings->endGroup();
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
            actionFail(action, error);
        emit actionFinished(action);
    }
    closeProtocol();
}

void HAbstractThread::offLineMode()
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
            actionFail(action, error);
            break;
        }
    }
    closeProtocol();
}

bool HAbstractThread::openProtocol()
{
    QList<IProtocol *> list;
    for (auto key : d_ptr->protocols.keys())
    {
        auto p = d_ptr->protocols.value(key);
        auto error = p->open();
        if (error != E_OK)
        {
            for (auto item : list)
                item->close();
            emit startFailed(tr("\n设备“%1”连接失败！错误原因是“%2”\n").arg(key).arg(toComment(error)));
            return false;
        }
        list.append(p);
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

void HAbstractThread::actionFail(HActionType action, HErrorType error)
{
    emit actionFailed(action, tr("\n指令“%1”错误！错误原因是“%2”\n").arg(toComment(action)).arg(toComment(error)));
}

HE_CONTROLLER_END_NAMESPACE
