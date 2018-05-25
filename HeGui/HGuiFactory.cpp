#include "HGuiFactory_p.h"
#include "HeCore/IHandler.h"
#include "HeCore/HFactory.h"

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
}

void HGuiFactory::initialize(QVariantMap /*param*/)
{
}

QString HGuiFactory::typeName()
{
    return "HGuiFactory";
}

IHandler *HGuiFactory::createHandler(QString type, QVariantMap param)
{
    param.insert("parent", QVariant::fromValue(this));
    return HFactory::createObject<IHandler>(type, param);
}

void HGuiFactory::registerClass()
{
//    HFactory::registerClass<HSerialPort>("HSerialPort");
//    HFactory::registerClass<HUsbPortCy>("HUsbPortCy");
//    HFactory::registerClass<HDeviceSL>("HDeviceSL");
}

HE_GUI_END_NAMESPACE
