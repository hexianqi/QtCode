#include "HAbstractThread_p.h"
#include "IActionStrategy.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeCore/HException.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QSettings>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutexLocker>

HE_BEGIN_NAMESPACE

HAbstractThreadPrivate::HAbstractThreadPrivate()
{
    mutex = new QMutex;
    waitConditionAction = new QWaitCondition;
    testData = HAppContext::getContextPointer<ITestData>("ITestData");
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
    int i;
    HActionType action;

    d_ptr->running = true;
    if (!openProtocol())
    {
        d_ptr->running = false;
        return;
    }

    forever
    {
        action = d_ptr->dequeueAction();
        if (action == ACT_EXIT)
            break;

        for (i = d_ptr->retry; i >= 0; i--)
        {
            try
            {
                if (handleAction(action))
                {
                    emit actionFinished(action);
                    break;
                }
            }
            catch (HException &e)
            {
                if (i == 0)
                    emit actionFailed(action, e.message());
            }
            msleep(d_ptr->sleepTime);
        }
    }
    closeProtocol();
    d_ptr->running = false;
}

bool HAbstractThread::checkAction(HActionType action)
{
    return action < 0x00000100 || isSupport(action);
}

bool HAbstractThread::handleAction(HActionType action)
{
    for (auto v : d_ptr->strategys)
    {
        if (v->isSupport(action))
            return v->handle(action);
    }
    throw HException(E_THREAD_NO_HANDLE);
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

bool HAbstractThread::openProtocol()
{
    QList<IProtocol *> list;
    for (auto p : d_ptr->protocols)
    {
        try
        {
            p->open();
            list.append(p);
        }
        catch (HException &e)
        {
            for (auto item : list)
                item->close();
            emit startFailed(p->portType(), e.message());
            return false;
        }
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
    settings->setIniCodec("utf-8");
    settings->beginGroup("Thread");
    d_ptr->retry = settings->value("Retry", 3).toInt();
    d_ptr->sleepTime = settings->value("SleepTime", 1000).toUInt();
    settings->endGroup();
}

void HAbstractThread::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    auto settings = new QSettings(fileName, QSettings::IniFormat, this);
    settings->setIniCodec("utf-8");
    settings->beginGroup("Thread");
    settings->setValue("Retry", d_ptr->retry);
    settings->setValue("SleepTime", d_ptr->sleepTime);
    settings->endGroup();
}

HE_END_NAMESPACE
