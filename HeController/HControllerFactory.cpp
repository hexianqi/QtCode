#include "HControllerFactory_p.h"
#include "HThreadCollection.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HControllerFactory::HControllerFactory()
    : d_ptr(new HControllerFactoryPrivate)
{
}

HControllerFactory::HControllerFactory(HControllerFactoryPrivate &p)
    : d_ptr(&p)
{
}

HControllerFactory::~HControllerFactory()
{
}

void HControllerFactory::initialize(QVariantMap param)
{
    Q_UNUSED(param)
}

IThreadCollection *HControllerFactory::createThreadCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IThreadCollection *p = new HThreadCollection;
    p->initialize(param);
    return p;
}

HE_CONTROLLER_END_NAMESPACE
