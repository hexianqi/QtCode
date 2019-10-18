#include "HControllerFactory_p.h"
#include "HSpecThread.h"
#include "HThreadCollection.h"
#include "HSpecModel.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HControllerFactory::HControllerFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HControllerFactoryPrivate)
{
    registerClass();
}

HControllerFactory::HControllerFactory(HControllerFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HControllerFactory::~HControllerFactory()
{
    qDebug() << __func__;
}

void HControllerFactory::initialize(QVariantMap /*param*/)
{
}

QString HControllerFactory::typeName()
{
    return "HControllerFactory";
}

IThread *HControllerFactory::createThread(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IThread>(type, param, this);
}

IThreadCollection *HControllerFactory::createThreadCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HThreadCollection;
    p->initialize(param);
    return p;
}

IModel *HControllerFactory::createModel(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IModel>(type, param, this);
}

void HControllerFactory::registerClass()
{
    HObjectFactory::registerClass<HSpecThread>("HSpecThread");
    HObjectFactory::registerClass<HSpecModel>("HSpecModel");
}

HE_CONTROLLER_END_NAMESPACE
