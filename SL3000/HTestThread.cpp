#include "HTestThread_p.h"

HTestThreadPrivate::HTestThreadPrivate()
{

}

HTestThread::HTestThread(int index, QObject *parent) :
    QThread(parent),
    d_ptr(new HTestThreadPrivate)
{
    d_ptr->index = index;
}

HTestThread::~HTestThread()
{
    stop();
}

void HTestThread::stop()
{
    if (!d_ptr->running)
        return;
//    d_ptr->clearAction();
//    d_ptr->enqueueAction(ACT_EXIT);
    wait(1000);
}

void HTestThread::run()
{
    d_ptr->running = true;


    d_ptr->running = false;

}




