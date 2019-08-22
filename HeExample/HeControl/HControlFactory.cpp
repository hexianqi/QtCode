#include "HControlFactory_p.h"
#include "HCircularProgress.h"
#include "HColorPicker.h"
#include "HDemoWidget.h"
#include "HFlatStyleWidget.h"
#include "HGifWidget.h"
#include "HIconFontWidget.h"
#include "HImageEffectWidget.h"
#include "HImageBrowser.h"
#include "HNetworkWidget.h"
#include "HQssCreator.h"
#include "HSerialPortWidget.h"
#include "HSpliteWidget.h"
#include "HStyleWidget.h"
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
    HWidgetFactory::registerClass<HCircularProgress>("HCircularProgress");
    HWidgetFactory::registerClass<HColorPicker>("HColorPickerWidget");
    HWidgetFactory::registerClass<HDemoWidget>("HDemoWidget");    
    HWidgetFactory::registerClass<HFlatStyleWidget>("HFlatStyleWidget");
    HWidgetFactory::registerClass<HGifWidget>("HGifWidget");
    HWidgetFactory::registerClass<HIconFontWidget>("HIconFontWidget");
    HWidgetFactory::registerClass<HImageEffectWidget>("HImageEffectWidget");
    HWidgetFactory::registerClass<HImageBrowser>("HImageBrowser");
    HWidgetFactory::registerClass<HNetworkWidget>("HNetworkWidget");
    HWidgetFactory::registerClass<HQssCreator>("HQssCreator");
    HWidgetFactory::registerClass<HSerialPortWidget>("HSerialPortWidget");
    HWidgetFactory::registerClass<HSpliteWidget>("HSpliteWidget");
    HWidgetFactory::registerClass<HStyleWidget>("HStyleWidget");
    auto e = HWidgetFactory::keys().toSet();
    d_ptr->keys = e.subtract(b).toList();
}

HE_CONTROL_END_NAMESPACE
