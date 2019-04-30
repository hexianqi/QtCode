#include "HGuiFactory_p.h"
#include "HSimpleTestSetWidget.h"
#include "HAction.h"
#include "HTestHandler.h"
#include "HSpecCalibrateHandler.h"
#include "HGradeEditHandler.h"
#include "HGradeSelectHandler.h"
#include "HAdjustEditHandler.h"
#include "HAdjustSelectHandler.h"
#include "HeCore/HFactory.h"
#include "HeCore/HObjectFactory.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HGuiFactory::HGuiFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HGuiFactoryPrivate)
{
    registerClass();
}

HGuiFactory::HGuiFactory(HGuiFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
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

ITestSetWidget *HGuiFactory::createTestSetWidget(QString type, QVariantMap param)
{
    return HFactory::createObject<ITestSetWidget>(type, param);
}

IGuiHandler *HGuiFactory::createHandler(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<IGuiHandler>(type, param, this);
    if (p == nullptr)
    {
        p = new HTestHandler(this);
        p->initialize(param);
    }
    return p;
}

HAction *HGuiFactory::createAction(QString text, QString type, QVariantMap param)
{
    auto action = new HAction(this);
    action->setText(text);
    action->setHandler(createHandler(type, param));
    return action;
}

void HGuiFactory::registerClass()
{
    HFactory::registerClass<HSimpleTestSetWidget>("HSimpleTestSetWidget");
    HObjectFactory::registerClass<HTestHandler>("HTestHandler");
    HObjectFactory::registerClass<HSpecCalibrateHandler>("HSpecCalibrateHandler");
    HObjectFactory::registerClass<HGradeEditHandler>("HGradeEditHandler");
    HObjectFactory::registerClass<HGradeSelectHandler>("HGradeSelectHandler");
    HObjectFactory::registerClass<HAdjustEditHandler>("HAdjustEditHandler");
    HObjectFactory::registerClass<HAdjustSelectHandler>("HAdjustSelectHandler");
}

HE_GUI_END_NAMESPACE
