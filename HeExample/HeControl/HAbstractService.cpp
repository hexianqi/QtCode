#include "HAbstractService_p.h"

HE_BEGIN_NAMESPACE

HAbstractService::HAbstractService(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractServicePrivate)
{
}

HAbstractService::HAbstractService(HAbstractServicePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractService::~HAbstractService() = default;

bool HAbstractService::start()
{
    if (d_ptr->running)
        return false;
    d_ptr->running = true;
    return true;
}

bool HAbstractService::stop()
{
    if (!d_ptr->running)
        return false;
    d_ptr->running = false;
    return true;
}

bool HAbstractService::isRunning()
{
    return d_ptr->running;
}

HE_END_NAMESPACE
