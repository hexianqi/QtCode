#include "HGuiFactory_p.h"
#include "HSimpleTestSetWidget.h"
#include "HSpecCalibrateSetWidget.h"
#include "HSpecCalibrateSetWidget2.h"
#include "HAdjustSetWidget.h"
#include "HAdjustSetWidget2.h"
#include "HTestDataEditDialog.h"
#include "HAction.h"
#include "HTestHandler.h"
#include "HSpecCalibrateHandler.h"
#include "HSpecLuminousHandler.h"
#include "HSpecTcHandler.h"
#include "HElecCalibrateHandler.h"
#include "HLuminousCalibrateHandler.h"
#include "HChromatismEditHandler.h"
#include "HChromatismSelectHandler.h"
#include "HGradeEditHandler.h"
#include "HGradeSelectHandler.h"
#include "HAdjustEditHandler.h"
#include "HAdjustSelectHandler.h"
#include "HQualityEditHandler.h"
#include "HQualitySelectHandler.h"
#include "HSqlBrowserHandler.h"
#include "HProductInfoEditHandler.h"
#include "HIVTestHandler.h"
#include "HeCore/HObjectFactory.h"
#include "HeCore/HWidgetFactory.h"
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
    qDebug() << endl << __func__;
}

void HGuiFactory::initialize(QVariantMap /*param*/)
{
}

QString HGuiFactory::typeName()
{
    return "HGuiFactory";
}

ITestSetWidget *HGuiFactory::createTestSetWidget(QString type, QWidget *parent, QVariantMap param)
{
    return HWidgetFactory::createWidget<ITestSetWidget>(type, param, parent);
}

ITestDataEditDialog *HGuiFactory::createTestDataEditDialog(QString type, QWidget *parent, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HTestDataEditDialog(parent);
    p->initialize(param);
    return p;
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
    auto p = new HAction(this);
    p->setText(text);
    p->setHandler(createHandler(type, param));
    return p;
}

void HGuiFactory::registerClass()
{
    HWidgetFactory::registerClass<HSimpleTestSetWidget>("HSimpleTestSetWidget");
    HWidgetFactory::registerClass<HSpecCalibrateSetWidget>("HSpecCalibrateSetWidget");
    HWidgetFactory::registerClass<HSpecCalibrateSetWidget2>("HSpecCalibrateSetWidget2");
    HWidgetFactory::registerClass<HAdjustSetWidget>("HAdjustSetWidget");
    HWidgetFactory::registerClass<HAdjustSetWidget2>("HAdjustSetWidget2");

    HObjectFactory::registerClass<HTestHandler>("HTestHandler");
    HObjectFactory::registerClass<HSpecCalibrateHandler>("HSpecCalibrateHandler");
    HObjectFactory::registerClass<HSpecLuminousHandler>("HSpecLuminousHandler");
    HObjectFactory::registerClass<HSpecTcHandler>("HSpecTcHandler");
    HObjectFactory::registerClass<HElecCalibrateHandler>("HElecCalibrateHandler");
    HObjectFactory::registerClass<HLuminousCalibrateHandler>("HLuminousCalibrateHandler");
    HObjectFactory::registerClass<HChromatismEditHandler>("HChromatismEditHandler");
    HObjectFactory::registerClass<HChromatismSelectHandler>("HChromatismSelectHandler");
    HObjectFactory::registerClass<HGradeEditHandler>("HGradeEditHandler");
    HObjectFactory::registerClass<HGradeSelectHandler>("HGradeSelectHandler");
    HObjectFactory::registerClass<HAdjustEditHandler>("HAdjustEditHandler");
    HObjectFactory::registerClass<HAdjustSelectHandler>("HAdjustSelectHandler");
    HObjectFactory::registerClass<HQualityEditHandler>("HQualityEditHandler");
    HObjectFactory::registerClass<HQualitySelectHandler>("HQualitySelectHandler");
    HObjectFactory::registerClass<HProductInfoEditHandler>("HProductInfoEditHandler");
    HObjectFactory::registerClass<HSqlBrowserHandler>("HSqlBrowserHandler");
    HObjectFactory::registerClass<HIVTestHandler>("HIVTestHandler");
}

HE_GUI_END_NAMESPACE
