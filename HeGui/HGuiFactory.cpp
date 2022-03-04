#include "HGuiFactory_p.h"
#include "HSimpleTestSetWidget.h"
#include "HSpecCalibrateSetWidget.h"
#include "HSpecCalibrateSetWidget2.h"
#include "HAdjustSetWidget.h"
#include "HAdjustSetWidget2.h"
#include "HProductEditDialog.h"
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
#include "HQualityEditHandler.h"
#include "HQualitySelectHandler.h"
#include "HLocationEditHandler.h"
#include "HLocationSelectHandler.h"
#include "HAdjustEditHandler.h"
#include "HAdjustSelectHandler.h"
#include "HAdjust2EditHandler.h"
#include "HAdjust2SelectHandler.h"
#include "HSqlBrowserHandler.h"
#include "HProductEditHandler.h"
#include "HIVTestHandler.h"
#include "HImportCurveHandler.h"
#include "HExportCurveHandler.h"
#include "HImportDeviceHandler.h"
#include "HExportDeviceHandler.h"
#include "HLoginInHandler.h"
#include "HLoginOutHandler.h"
#include "HSpecPrintTemplate.h"
#include "HTagPrintTemplate.h"
#include "HSpecTextExportTemplate.h"
#include "HeCore/HObjectFactory.h"
#include "HeCore/HWidgetFactory.h"

HE_BEGIN_NAMESPACE

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

HGuiFactory::~HGuiFactory() = default;

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
    return HWidgetFactory::createWidget<ITestDataEditDialog>(type, param, parent);
}

IHandler *HGuiFactory::createHandler(QString type, QVariantMap param)
{
    auto p = HObjectFactory::createObject<IHandler>(type, param, this);
    if (p == nullptr)
    {
        p = new HTestHandler(this);
        p->initialize(param);
    }
    return p;
}

IPrintTemplate *HGuiFactory::createPrintTemplate(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IPrintTemplate>(type, param, this);
}

ITextExportTemplate *HGuiFactory::createTextExportTemplate(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HSpecTextExportTemplate(this);
    p->initialize(param);
    return p;
}

HAction *HGuiFactory::createAction(QString text, QString type, QVariantMap param)
{
    auto p = new HAction(this);
    p->initialize(param);
    p->setText(text);
    p->setHandler(createHandler(type, param));
    return p;
}

void HGuiFactory::registerClass()
{
    // 设置窗体
    HWidgetFactory::registerClass<HSimpleTestSetWidget>("HSimpleTestSetWidget");
    HWidgetFactory::registerClass<HSpecCalibrateSetWidget>("HSpecCalibrateSetWidget");
    HWidgetFactory::registerClass<HSpecCalibrateSetWidget2>("HSpecCalibrateSetWidget2");
    HWidgetFactory::registerClass<HAdjustSetWidget>("HAdjustSetWidget");
    HWidgetFactory::registerClass<HAdjustSetWidget2>("HAdjustSetWidget2");
    // 对话框
    HWidgetFactory::registerClass<HProductEditDialog>("HProductEditDialog");
    // 动作处理
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
    HObjectFactory::registerClass<HQualityEditHandler>("HQualityEditHandler");
    HObjectFactory::registerClass<HQualitySelectHandler>("HQualitySelectHandler");
    HObjectFactory::registerClass<HLocationEditHandler>("HLocationEditHandler");
    HObjectFactory::registerClass<HLocationSelectHandler>("HLocationSelectHandler");
    HObjectFactory::registerClass<HAdjustEditHandler>("HAdjustEditHandler");
    HObjectFactory::registerClass<HAdjustSelectHandler>("HAdjustSelectHandler");
    HObjectFactory::registerClass<HAdjust2EditHandler>("HAdjust2EditHandler");
    HObjectFactory::registerClass<HAdjust2SelectHandler>("HAdjust2SelectHandler");
    HObjectFactory::registerClass<HProductEditHandler>("HProductEditHandler");
    HObjectFactory::registerClass<HSqlBrowserHandler>("HSqlBrowserHandler");
    HObjectFactory::registerClass<HIVTestHandler>("HIVTestHandler");
    HObjectFactory::registerClass<HImportDeviceHandler>("HImportDeviceHandler");
    HObjectFactory::registerClass<HExportDeviceHandler>("HExportDeviceHandler");
    HObjectFactory::registerClass<HImportCurveHandler>("HImportCurveHandler");
    HObjectFactory::registerClass<HExportCurveHandler>("HExportCurveHandler");
    HObjectFactory::registerClass<HLoginInHandler>("HLoginInHandler");
    HObjectFactory::registerClass<HLoginOutHandler>("HLoginOutHandler");
    // 打印模板
    HObjectFactory::registerClass<HSpecPrintTemplate>("HSpecPrintTemplate");
    HObjectFactory::registerClass<HTagPrintTemplate>("HTagPrintTemplate");
}

HE_END_NAMESPACE
