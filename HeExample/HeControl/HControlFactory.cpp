#include "HControlFactory_p.h"
#include "HControlHelper.h"
#include "HControlDemoWidget.h"
#include "HColorPicker.h"
#include "HGifWidget.h"
#include "HScreenWidget.h"
//#include "HSerialPortWidget.h"
//#include "HCircularProgress.h"
//#include "HDemoWidget.h"
//#include "HImageEffectWidget.h"
#include "HImageBrowser.h"
#include "HBackgroundEventFilter.h"
#include "HMoveEventFilter.h"
#include "HResizeEventFilter.h"
#include "HeCore/HObjectFactory.h"
#include "HeCore/HWidgetFactory.h"
#include <QtCore/QSet>

HE_BEGIN_NAMESPACE

HControlFactory::HControlFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HControlFactoryPrivate)
{
    registerClass();
}

HControlFactory::~HControlFactory() = default;

void HControlFactory::initialize(QVariantMap /*param*/)
{

}

QString HControlFactory::typeName()
{
    return "HControlFactory";
}

QStringList HControlFactory::supportedWidget()
{
    return d_ptr->supportedWidget;
}

QWidget *HControlFactory::createWidget(const QString &type, QWidget *parent)
{
    if (type == "frameless")
    {
        auto w = new QWidget();
        w->resize(800, 600);
        HControlHelper::framelessWidget(w);
        return w;
    }
    if (type == "translucent")
    {
        auto w = new QWidget();
        w->resize(800, 600);
        HControlHelper::translucentWidget(w, QStringList());
        return w;
    }
    return HWidgetFactory::createWidget<QWidget>(type, parent);
}

QStringList HControlFactory::supportedEventFilter()
{
    return d_ptr->supportedEventFilter;
}

IEventFilter *HControlFactory::createEventFilter(const QString &type, QVariantMap param)
{
    return HObjectFactory::createObject<IEventFilter>(type, param, this);
}

void HControlFactory::registerClass()
{
    // 支持的窗体
    auto b = HWidgetFactory::keys().toSet();
    // 演示
    HWidgetFactory::registerClass<HControlDemoWidget>("HControlDemoWidget");
    // 工具
    HWidgetFactory::registerClass<HColorPicker>("HColorPicker");
    HWidgetFactory::registerClass<HGifWidget>("HGifWidget");
    HWidgetFactory::registerClass<HScreenWidget>("HScreenWidget");
    HWidgetFactory::registerClass<HImageBrowser>("HImageBrowser");
//    HWidgetFactory::registerClass<HSerialPortWidget>("HSerialPortWidget");
//    // 未整理
//    HWidgetFactory::registerClass<HCircularProgress>("HCircularProgress");
//    HWidgetFactory::registerClass<HImageEffectWidget>("HImageEffectWidget");
//
//    HWidgetFactory::registerClass<HDemoWidget>("HDemoWidget");

    auto e = HWidgetFactory::keys().toSet();
    d_ptr->supportedWidget = e.subtract(b).toList();
    d_ptr->supportedWidget.prepend("frameless");
    d_ptr->supportedWidget.prepend("translucent");

    // 支持的事件
    b = HObjectFactory::keys().toSet();
    HObjectFactory::registerClass<HBackgroundEventFilter>("HBackgroundEventFilter");
    HObjectFactory::registerClass<HMoveEventFilter>("HMoveEventFilter");
    HObjectFactory::registerClass<HResizeEventFilter>("HResizeEventFilter");
    e = HObjectFactory::keys().toSet();
    d_ptr->supportedEventFilter = e.subtract(b).toList();
}

HE_END_NAMESPACE
