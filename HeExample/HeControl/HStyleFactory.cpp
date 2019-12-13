#include "HStyleFactory_p.h"
#include "HFlatStyle.h"
#include "HQssStyle.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HStyleFactory::HStyleFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HStyleFactoryPrivate)
{
    registerClass();
}

HStyleFactory::HStyleFactory(HStyleFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HStyleFactory::~HStyleFactory()
{
    qDebug() << __func__;
}

void HStyleFactory::initialize(QVariantMap /*param*/)
{
}

QString HStyleFactory::typeName()
{
    return "HStyleFactory";
}

QStringList HStyleFactory::keys()
{
    return d_ptr->keys;
}

IStyle *HStyleFactory::create(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IStyle>(type, param, this);
}

void HStyleFactory::registerClass()
{
    auto b = HObjectFactory::keys().toSet();
    HObjectFactory::registerClass<HFlatStyle>("HFlatStyle");
    HObjectFactory::registerClass<HQssStyle>("HQssStyle");
    d_ptr->keys = HObjectFactory::keys().toSet().subtract(b).toList();
}

HE_CONTROL_END_NAMESPACE
