#include "HControlFactory_p.h"
#include "HControlDemoWidget.h"
#include "HCodeCountWidget.h"
#include "HColorPicker.h"
#include "HEmailWidget.h"
#include "HGifWidget.h"
#include "HNetworkWidget.h"
#include "HPngAmend.h"
#include "HScreenWidget.h"
#include "HSerialPortWidget.h"
#include "HMoveEventFilter.h"

#include "HCircularProgress.h"
#include "HDemoWidget.h"
#include "HImageEffectWidget.h"
#include "HImageBrowser.h"

#include "HeCore/HObjectFactory.h"
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

QStringList HControlFactory::supportedWidgets()
{
    return d_ptr->supportedWidgets;
}

QStringList HControlFactory::supportedEventFilters()
{
    return d_ptr->supportedEventFilters;
}

QWidget *HControlFactory::createWidget(const QString &type, QWidget *parent)
{
    return HWidgetFactory::createWidget<QWidget>(type, parent);
}

IEventFilter *HControlFactory::createEventFilter(const QString &type, QVariantMap param)
{
    return HObjectFactory::createObject<IEventFilter>(type, param, this);
}

void HControlFactory::registerClass()
{
    auto b = HWidgetFactory::keys().toSet();
    // 演示
    HWidgetFactory::registerClass<HControlDemoWidget>("HControlDemoWidget");
    // 工具
    HWidgetFactory::registerClass<HCodeCountWidget>("HCodeCountWidget");
    HWidgetFactory::registerClass<HColorPicker>("HColorPicker");
    HWidgetFactory::registerClass<HEmailWidget>("HEmailWidget");
    HWidgetFactory::registerClass<HGifWidget>("HGifWidget");
    HWidgetFactory::registerClass<HNetworkWidget>("HNetworkWidget");
    HWidgetFactory::registerClass<HPngAmend>("HPngAmend");
    HWidgetFactory::registerClass<HScreenWidget>("HScreenWidget");
    HWidgetFactory::registerClass<HSerialPortWidget>("HSerialPortWidget");

    // 未整理
    HWidgetFactory::registerClass<HCircularProgress>("HCircularProgress");
    HWidgetFactory::registerClass<HImageEffectWidget>("HImageEffectWidget");
    HWidgetFactory::registerClass<HImageBrowser>("HImageBrowser");
    HWidgetFactory::registerClass<HDemoWidget>("HDemoWidget");

    auto e = HWidgetFactory::keys().toSet();
    d_ptr->supportedWidgets = e.subtract(b).toList();
    b = HObjectFactory::keys().toSet();
    HObjectFactory::registerClass<HMoveEventFilter>("HMoveEventFilter");
    e = HObjectFactory::keys().toSet();
    d_ptr->supportedEventFilters = e.subtract(b).toList();
}

HE_CONTROL_END_NAMESPACE
