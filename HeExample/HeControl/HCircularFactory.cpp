#include "HCircularFactory_p.h"
#include "HBearingCircular.h"
#include "HBubbleCircular.h"
#include "HCircleCircular.h"
#include "HZoomCircleCircular.h"
#include "HDonutCircular.h"
#include "HInfiniteCircular.h"
#include "HLineCircular.h"
#include "HPetalCircular.h"
#include "HPieCircular.h"
#include "HTaichiCircular.h"
#include "HWheelCircular.h"
#include "HeCore/HObjectFactory.h"
#include <QtWidgets/QActionGroup>
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

QActionGroup *HCircularFactory::toActionGroup()
{
    auto group = new QActionGroup(this);
    for (auto it = d_ptr->aliass.begin(); it != d_ptr->aliass.end(); it++)
    {
        auto action = group->addAction(it.value());
        action->setCheckable(true);
        action->setData(it.key());
    }
    if (!group->actions().isEmpty())
        group->actions().at(0)->setChecked(true);
    return group;
}

void HCircularFactory::registerClass()
{
    HObjectFactory::registerClass<HBearingCircular>("HBearingCircular");
    HObjectFactory::registerClass<HBubbleCircular>("HBubbleCircular");
    HObjectFactory::registerClass<HCircleCircular>("HCircleCircular");
    HObjectFactory::registerClass<HDonutCircular>("HDonutCircular");
    HObjectFactory::registerClass<HInfiniteCircular>("HInfiniteCircular");
    HObjectFactory::registerClass<HLineCircular>("HLineCircular");
    HObjectFactory::registerClass<HPetalCircular>("HPetalCircular");
    HObjectFactory::registerClass<HPieCircular>("HPieCircular");
    HObjectFactory::registerClass<HTaichiCircular>("HTaichiCircular");
    HObjectFactory::registerClass<HWheelCircular>("HWheelCircular");
    HObjectFactory::registerClass<HZoomCircleCircular>("HZoomCircleCircular");
    d_ptr->aliass.insert("HBearingCircular", tr("轴承状"));
    d_ptr->aliass.insert("HBubbleCircular", tr("气泡状"));
    d_ptr->aliass.insert("HCircleCircular", tr("圈状"));
    d_ptr->aliass.insert("HDonutCircular", tr("环状"));
    d_ptr->aliass.insert("HInfiniteCircular", tr("无限状"));
    d_ptr->aliass.insert("HLineCircular", tr("线状"));
    d_ptr->aliass.insert("HPetalCircular", tr("花瓣状"));
    d_ptr->aliass.insert("HPieCircular", tr("饼状"));
    d_ptr->aliass.insert("HTaichiCircular", tr("太极图"));
    d_ptr->aliass.insert("HWheelCircular", tr("轮子"));
    d_ptr->aliass.insert("HZoomCircleCircular", tr("缩放"));
}

HE_CONTROL_END_NAMESPACE
