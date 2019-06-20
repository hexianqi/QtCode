#include "HWaitFactory_p.h"
#include "HCircleWait.h"
#include "HLineWait.h"
#include "HTaichiWait.h"
#include "HPieWait.h"
#include "HDonutWait.h"
#include "HZoomCircleWait.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HWaitFactory::HWaitFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HWaitFactoryPrivate)
{
    registerClass();
}

HWaitFactory::HWaitFactory(HWaitFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HWaitFactory::~HWaitFactory()
{
    qDebug() << __func__;
}

void HWaitFactory::initialize(QVariantMap /*param*/)
{

}

QString HWaitFactory::typeName()
{
    return "HWaitFactory";
}

QStringList HWaitFactory::keys()
{
    return d_ptr->aliass.keys();
}

QString HWaitFactory::alias(QString type)
{
    return d_ptr->aliass.value(type, type);
}

IWait *HWaitFactory::create(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<IWait>(type, param, this);
    if (p == nullptr)
    {
        p = new HCircleWait(this);
        p->initialize(param);
    }
    return p;
}

void HWaitFactory::registerClass()
{
    HObjectFactory::registerClass<HCircleWait>("HCircleWait");
    HObjectFactory::registerClass<HLineWait>("HLineWait");
    HObjectFactory::registerClass<HTaichiWait>("HTaichiWait");
    HObjectFactory::registerClass<HPieWait>("HPieWait");
    HObjectFactory::registerClass<HDonutWait>("HDonutWait");
    HObjectFactory::registerClass<HZoomCircleWait>("HZoomCircleWait");
    d_ptr->aliass.insert("HCircleWait", tr("圈状"));
    d_ptr->aliass.insert("HLineWait", tr("线状"));
    d_ptr->aliass.insert("HTaichiWait", tr("太极图"));
    d_ptr->aliass.insert("HPieWait", tr("饼状"));
    d_ptr->aliass.insert("HDonutWait", tr("环状"));
    d_ptr->aliass.insert("HZoomCircleWait", tr("缩放"));
}

HE_CONTROL_END_NAMESPACE
