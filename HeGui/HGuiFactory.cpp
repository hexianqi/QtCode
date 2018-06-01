#include "HGuiFactory_p.h"
#include "HeCore/HObjectFactory.h"
#include "HAction.h"
#include "HTestHandler.h"
#include <QDebug>

HE_GUI_BEGIN_NAMESPACE

HGuiFactory::HGuiFactory(QObject *parent)
    : QObject(parent), d_ptr(new HGuiFactoryPrivate)
{
    registerClass();
}

HGuiFactory::HGuiFactory(HGuiFactoryPrivate &p)
    : d_ptr(&p)
{
    registerClass();
}

HGuiFactory::~HGuiFactory()
{
    qDebug() << __func__;
}

void HGuiFactory::initialize(QVariantMap /*param*/)
{
}

QString HGuiFactory::typeName()
{
    return "HGuiFactory";
}

IGuiHandler *HGuiFactory::createHandler(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<IGuiHandler>(type, param, this);
    if (p == nullptr)
        p = new HTestHandler(this);
    return p;
}

HAction *HGuiFactory::createAction(QString text, QString type, QVariantMap param)
{
    auto action = new HAction;
    action->setText(text);
    action->setHandler(createHandler(type, param));
    return action;
}

void HGuiFactory::registerClass()
{
    HObjectFactory::registerClass<HTestHandler>("HTestHandler");
//    HFactory::registerClass<HDeviceSL>("HDeviceSL");
}

HE_GUI_END_NAMESPACE
