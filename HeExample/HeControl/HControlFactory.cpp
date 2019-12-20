#include "HControlFactory_p.h"
#include "HControlDemoWidget.h"
#include "HFlatStyleWidget.h"
#include "HStyleWidget.h"
#include "HQssCreator.h"
#include "HIconFontWidget.h"
#include "HCodeCountWidget.h"
#include "HGifWidget.h"
#include "HNetworkWidget.h"
#include "HPngAmend.h"
#include "HColorPicker.h"

#include "HMoveEventFilter.h"

#include "HCircularProgress.h"

#include "HDemoWidget.h"
#include "HImageEffectWidget.h"
#include "HImageBrowser.h"
#include "HSerialPortWidget.h"

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

QWidget *HControlFactory::createWidget(QString type, QWidget *parent)
{
    return HWidgetFactory::createWidget<QWidget>(type, parent);
}

IEventFilter *HControlFactory::createEventFilter(QString type, QVariantMap param)
{
    return HObjectFactory::createObject<IEventFilter>(type, param, this);
}

void HControlFactory::registerClass()
{
    auto b = HWidgetFactory::keys().toSet();
    // 演示
    HWidgetFactory::registerClass<HControlDemoWidget>("HControlDemoWidget");
    HWidgetFactory::registerClass<HFlatStyleWidget>("HFlatStyleWidget");
    HWidgetFactory::registerClass<HStyleWidget>("HStyleWidget");
    HWidgetFactory::registerClass<HQssCreator>("HQssCreator");
    HWidgetFactory::registerClass<HIconFontWidget>("HIconFontWidget");
    // 工具
    HWidgetFactory::registerClass<HCodeCountWidget>("HCodeCountWidget");
    HWidgetFactory::registerClass<HGifWidget>("HGifWidget");
    HWidgetFactory::registerClass<HNetworkWidget>("HNetworkWidget");
    HWidgetFactory::registerClass<HPngAmend>("HPngAmend");
    HWidgetFactory::registerClass<HColorPicker>("HColorPicker");

    // 未整理
    HWidgetFactory::registerClass<HCircularProgress>("HCircularProgress");
    HWidgetFactory::registerClass<HImageEffectWidget>("HImageEffectWidget");

    HWidgetFactory::registerClass<HImageBrowser>("HImageBrowser");
    HWidgetFactory::registerClass<HSerialPortWidget>("HSerialPortWidget");
    HWidgetFactory::registerClass<HDemoWidget>("HDemoWidget");

    auto e = HWidgetFactory::keys().toSet();
    d_ptr->supportedWidgets = e.subtract(b).toList();


    b = HObjectFactory::keys().toSet();
    HObjectFactory::registerClass<HMoveEventFilter>("HMoveEventFilter");
    e = HObjectFactory::keys().toSet();
    d_ptr->supportedEventFilters = e.subtract(b).toList();
}

HE_CONTROL_END_NAMESPACE
