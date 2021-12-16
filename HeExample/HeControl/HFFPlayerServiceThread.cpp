#include "HFFPlayerServiceThread_p.h"
#include "HFFPlayerService.h"

HE_BEGIN_NAMESPACE

HFFPlayerServiceThreadPrivate::HFFPlayerServiceThreadPrivate(HFFPlayerService *service)
{
    this->service = service;
}

HFFPlayerServiceThread::HFFPlayerServiceThread(HFFPlayerService *service) :
    QThread(service),
    d_ptr(new HFFPlayerServiceThreadPrivate(service))
{
}

HFFPlayerServiceThread::~HFFPlayerServiceThread()
{
    shutdown();
}

void HFFPlayerServiceThread::shutdown()
{
    if (!d_ptr->running)
        return;
    clearTask();
    enqueueTask(Shutdown);
    wait(1000);
}

void HFFPlayerServiceThread::addTask(Task value)
{
    enqueueTask(value);
}

void HFFPlayerServiceThread::clearTask()
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->cache.clear();
}

void HFFPlayerServiceThread::enqueueTask(Task value)
{
    QMutexLocker locker(&d_ptr->mutex);
    d_ptr->cache.enqueue(value);
    d_ptr->cond.wakeOne();
}

HFFPlayerServiceThread::Task HFFPlayerServiceThread::dequeueTask()
{
    QMutexLocker locker(&d_ptr->mutex);
    if (d_ptr->cache.isEmpty())
        d_ptr->cond.wait(&d_ptr->mutex);
    return d_ptr->cache.dequeue();
}

void HFFPlayerServiceThread::run()
{
    Task task;
    d_ptr->running = true;

    while (1)
    {
        task = dequeueTask();
        if (task == Shutdown)
            break;
        if (task == SetSource)
        {
            d_ptr->service->doSetSource();
            continue;
        }
        if (task == Play)
        {
            d_ptr->service->doPlay();
            continue;
        }
        if (task == Pause)
        {
            d_ptr->service->doPause();
            continue;
        }if (task == Stop)
        {
            d_ptr->service->doStop();
            continue;
        }
    }
    d_ptr->running = false;
}

HE_END_NAMESPACE
