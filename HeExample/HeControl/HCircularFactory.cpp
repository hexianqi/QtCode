#include "HCircularFactory_p.h"
#include "HCircleCircular.h"
#include "HLineCircular.h"
#include "HTaichiCircular.h"
#include "HPieCircular.h"
#include "HDonutCircular.h"
#include "HWheelCircular.h"
#include "HCircleZoomCircular.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HCircularFactory::HCircularFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HCircularFactoryPrivate)
{
    registerClass();
}

HCircularFactory::HCircularFactory(HCircularFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HCircularFactory::~HCircularFactory()
{
    qDebug() << __func__;
}

void HCircularFactory::initialize(QVariantMap /*param*/)
{

}

QString HCircularFactory::typeName()
{
    return "HCircularFactory";
}

QStringList HCircularFactory::keys()
{
    return d_ptr->aliass.keys();
}

QString HCircularFactory::alias(QString type)
{
    return d_ptr->aliass.value(type, type);
}

ICircular *HCircularFactory::create(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<ICircular>(type, param, this);
    if (p == nullptr)
    {
        p = new HCircleCircular(this);
        p->initialize(param);
    }
    return p;
}

void HCircularFactory::registerClass()
{
    HObjectFactory::registerClass<HCircleCircular>("HCircleCircular");
    HObjectFactory::registerClass<HLineCircular>("HLineCircular");
    HObjectFactory::registerClass<HTaichiCircular>("HTaichiCircular");
    HObjectFactory::registerClass<HPieCircular>("HPieCircular");
    HObjectFactory::registerClass<HDonutCircular>("HDonutCircular");
    HObjectFactory::registerClass<HZoomCircleCircular>("HCircleZoomCircular");
    HObjectFactory::registerClass<HWheelCircular>("HWheelCircular");
    d_ptr->aliass.insert("HCircleCircular", tr("圈状"));
    d_ptr->aliass.insert("HLineCircular", tr("线状"));
    d_ptr->aliass.insert("HTaichiCircular", tr("太极图"));
    d_ptr->aliass.insert("HPieCircular", tr("饼状"));
    d_ptr->aliass.insert("HDonutCircular", tr("环状"));
    d_ptr->aliass.insert("HZoomCircleCircular", tr("缩放"));
    d_ptr->aliass.insert("HWheelCircular", tr("轮子"));
}

HE_CONTROL_END_NAMESPACE
