#include "HEffectFactory_p.h"
#include "HBlindsEffect.h"
#include "HFadeEffect.h"
#include "HFlipEffect.h"
#include "HMoveEffect.h"
#include "HSplitEffect.h"
#include "HeCore/HObjectFactory.h"
#include <QtWidgets/QActionGroup>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HEffectFactory::HEffectFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HEffectFactoryPrivate)
{
    registerClass();
}

HEffectFactory::HEffectFactory(HEffectFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HEffectFactory::~HEffectFactory()
{
    qDebug() << __func__;
}

void HEffectFactory::initialize(QVariantMap /*param*/)
{

}

QString HEffectFactory::typeName()
{
    return "HEffectFactory";
}

QStringList HEffectFactory::keys()
{
    return d_ptr->aliass.keys();
}

IShaderEffect *HEffectFactory::create(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<IShaderEffect>(type, param, this);
    if (p == nullptr)
    {
        p = new HFadeEffect(this);
        p->initialize(param);
    }
    return p;
}

QActionGroup *HEffectFactory::toActionGroup()
{
    auto group = new QActionGroup(this);
    for (auto it = d_ptr->aliass.begin(); it != d_ptr->aliass.end(); it++)
    {
        auto action = group->addAction(it.value());
        action->setCheckable(true);
        action->setData(it.key());
    }
    return group;
}

void HEffectFactory::registerClass()
{
    HObjectFactory::registerClass<HBlindsEffect>("HBlindsEffect");
    HObjectFactory::registerClass<HFadeEffect>("HFadeEffect");
    HObjectFactory::registerClass<HFlipEffect>("HFlipEffect");
    HObjectFactory::registerClass<HMoveEffect>("HMoveEffect");
    HObjectFactory::registerClass<HSplitEffect>("HSplitEffect");
    d_ptr->aliass.insert("HBlindsEffect", tr("百叶窗"));
    d_ptr->aliass.insert("HFadeEffect", tr("渐变"));
    d_ptr->aliass.insert("HFlipEffect", tr("翻滚"));
    d_ptr->aliass.insert("HMoveEffect", tr("移动"));
    d_ptr->aliass.insert("HSplitEffect", tr("分割"));
}

HE_CONTROL_END_NAMESPACE
