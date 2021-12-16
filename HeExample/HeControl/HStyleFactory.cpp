#include "HStyleFactory_p.h"
#include "HFlatStyle.h"
#include "HQssStyle.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QSet>

HE_BEGIN_NAMESPACE

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

HStyleFactory::~HStyleFactory() = default;

void HStyleFactory::initialize(QVariantMap /*param*/)
{
}

QString HStyleFactory::typeName()
{
    return "HStyleFactory";
}

IStyle *HStyleFactory::createStyle(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IStyle>(type, param, this);
}

IQssStyle *HStyleFactory::createQssStyle(QString type, QVariantMap param)
{
//    return HObjectFactory::createObject<IQssStyle>(type, param, this);
    Q_UNUSED(type);
    auto p = new HQssStyle(this);
    p->initialize(param);
    return p;
}

QStringList HStyleFactory::styles()
{
    return d_ptr->styles;
}

void HStyleFactory::registerClass()
{
    auto b = HObjectFactory::keys().toSet();
    HObjectFactory::registerClass<HFlatStyle>("HFlatStyle");
    HObjectFactory::registerClass<HQssStyle>("HQssStyle");
    d_ptr->styles = HObjectFactory::keys().toSet().subtract(b).toList();
}

HE_END_NAMESPACE
