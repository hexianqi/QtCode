#include "HDelayThread_p.h"
#include "IModel.h"
#include <QtCore/QWaitCondition>
#include <QtCore/QMutexLocker>

HE_BEGIN_NAMESPACE

HDelayThreadPrivate::HDelayThreadPrivate(IModel *p)
{
    mutex = new QMutex;
    waitConditionAction = new QWaitCondition;
    model = p;
}

void HDelayThreadPrivate::enqueueAction(HActionType action, ulong delay)
{
    if (!running)
        return;

    QMutexLocker locker(mutex);
    ulong total = 0;
    for (auto action : actionCache)
        total += action.second;
    delay = (delay > total) ? delay - total : 0;
    actionCache.enqueue(qMakePair(action, delay));
    waitConditionAction->wakeOne();
}

QPair<HActionType, ulong> HDelayThreadPrivate::dequeueAction()
{
    QMutexLocker locker(mutex);
    if (actionCache.isEmpty())
        waitConditionAction->wait(mutex);
    return actionCache.dequeue();
}

void HDelayThreadPrivate::clearAction()
{
    QMutexLocker locker(mutex);
    actionCache.clear();
}

HDelayThread::HDelayThread(IModel *parent) :
    QThread(parent),
    d_ptr(new HDelayThreadPrivate(parent))
{
}

HDelayThread::~HDelayThread()
{
    stop();
}

void HDelayThread::stop()
{
    if (!d_ptr->running)
        return;
    d_ptr->clearAction();
    d_ptr->enqueueAction(ACT_EXIT, 0);
    wait(100);
}

void HDelayThread::addAction(HActionType action, ulong delay)
{
    d_ptr->enqueueAction(action, delay);
}

void HDelayThread::clearAction()
{
    d_ptr->clearAction();
}

void HDelayThread::run()
{
    d_ptr->running = true;
    forever
    {
        auto action = d_ptr->dequeueAction();
        if (action.first == ACT_EXIT)
            break;
        msleep(action.second);
        d_ptr->model->addAction(action.first);
    }
    d_ptr->running = false;
}

HE_END_NAMESPACE
