#include "HControllerFactory_p.h"
#include "HThreadCollection.h"
#include "HSpecThread.h"
#include "HSpecElecThread.h"
#include "HIntegrateThread.h"
#include "HSpecModel.h"
#include "HSpecElecModel.h"
#include "HIntegrateModel.h"
#include "HSpecStrategy.h"
#include "HElecStrategy.h"
#include "HLuminousStrategy.h"
#include "HMotorStrategy.h"
#include "HPowerFactorStrategy.h"
#include "HMemento.h"
#include "HMementoCollection.h"
#include "HeCore/HObjectFactory.h"

HE_BEGIN_NAMESPACE

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

HControllerFactory::~HControllerFactory() = default;

void HControllerFactory::initialize(QVariantMap /*param*/)
{
}

QString HControllerFactory::typeName()
{
    return "HControllerFactory";
}

IThread *HControllerFactory::createThread(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IThread>(type, param, parent);
}

IThreadCollection *HControllerFactory::createThreadCollection(QString /*type*/, QVariantMap param)
{
    auto p = new HThreadCollection;
    p->initialize(param);
    return p;
}

IModel *HControllerFactory::createModel(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IModel>(type, param, parent);
}

IActionStrategy *HControllerFactory::createStrategy(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IActionStrategy>(type, param, parent);
}

IMemento *HControllerFactory::createMemento(QString /*type*/, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    auto p = new HMemento(parent);
    p->initialize(param);
    return p;
}

IMementoCollection *HControllerFactory::createMementoCollection(QString /*type*/, QVariantMap param)
{
    auto p = new HMementoCollection;
    p->initialize(param);
    return p;
}

void HControllerFactory::registerClass()
{
    HObjectFactory::registerClass<HSpecThread>("HSpecThread");
    HObjectFactory::registerClass<HSpecElecThread>("HSpecElecThread");
    HObjectFactory::registerClass<HIntegrateThread>("HIntegrateThread");
    HObjectFactory::registerClass<HSpecModel>("HSpecModel");
    HObjectFactory::registerClass<HSpecElecModel>("HSpecElecModel");
    HObjectFactory::registerClass<HIntegrateModel>("HIntegrateModel");
    HObjectFactory::registerClass<HSpecStrategy>("HSpecStrategy");
    HObjectFactory::registerClass<HElecStrategy>("HElecStrategy");
    HObjectFactory::registerClass<HLuminousStrategy>("HLuminousStrategy");
    HObjectFactory::registerClass<HMotorStrategy>("HMotorStrategy");
    HObjectFactory::registerClass<HPowerFactorStrategy>("HPowerFactorStrategy");
}

HE_END_NAMESPACE
