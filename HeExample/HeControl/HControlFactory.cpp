#include "HControlFactory_p.h"
#include "HDemoWidget.h"
#include "HColorPickerWidget.h"
#include "HSerialPortWidget.h"
#include "HGifWidget.h"
#include "HStyleWidget.h"
#include "HFlatStyleWidget.h"
#include "HBarRuler.h"
#include "HBattery.h"
#include "HLightButton.h"
#include "HLedNumber.h"
#include "HColorProgressBar.h"
#include "HRoundProgressBar.h"
#include "HCircularProgress.h"
#include "HeCore/HWidgetFactory.h"
#include <QtCore/QDebug>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

HControlFactory::HControlFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HControlFactoryPrivate)
{
    registerClass();
}

HControlFactory::~HControlFactory()
{
    qDebug() << __func__;
}

void HControlFactory::initialize(QVariantMap /*param*/)
{

}

QString HControlFactory::typeName()
{
    return "HControlFactory";
}

QStringList HControlFactory::keys()
{
    return d_ptr->keys;
}

QWidget *HControlFactory::createWidget(QString type, QWidget *parent)
{
    return HWidgetFactory::createWidget<QWidget>(type, parent);
}

void HControlFactory::registerClass()
{
    auto b = HWidgetFactory::keys().toSet();
    HWidgetFactory::registerClass<HDemoWidget>("HDemoWidget");
    HWidgetFactory::registerClass<HRoundProgressBar>("HRoundProgressBar");
//    HWidgetFactory::registerClass<HStyleWidget>("HStyleWidget");
//    HWidgetFactory::registerClass<HFlatStyleWidget>("HFlatStyleWidget");
//    HWidgetFactory::registerClass<HColorPickerWidget>("HColorPickerWidget");
//    HWidgetFactory::registerClass<HSerialPortWidget>("HSerialPortWidget");
//    HWidgetFactory::registerClass<HGifWidget>("HGifWidget");
//    HWidgetFactory::registerClass<HBarRuler>("HBarRuler");
//    HWidgetFactory::registerClass<HBattery>("HBattery");
//    HWidgetFactory::registerClass<HLightButton>("HLightButton");
//    HWidgetFactory::registerClass<HLedNumber>("HLedNumber");
//    HWidgetFactory::registerClass<HColorProgressBar>("HColorProgressBar");
//    HWidgetFactory::registerClass<HCircularProgress>("HCircularProgress");
    auto e = HWidgetFactory::keys().toSet();
    d_ptr->keys = e.subtract(b).toList();
}

HE_CONTROL_END_NAMESPACE
