#include "HAbstractBuilder_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/HControllerFactory.h"
#include "HeData/HDataFactory.h"
#include "HeGui/HGuiFactory.h"
#include "HeSql/HSqlFactory.h"

HE_BEGIN_NAMESPACE

HAbstractBuilderPrivate::HAbstractBuilderPrivate()
{
    mainWindow = HAppContext::getContextPointer<IMainWindow>("IMainWindow");
    configFileName = HAppContext::getContextValue<QString>("ConfigFileName");
}

HAbstractBuilder::HAbstractBuilder(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractBuilderPrivate)
{
}

void HAbstractBuilder::initialize(QVariantMap /*param*/)
{

}

HAbstractBuilder::HAbstractBuilder(HAbstractBuilderPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

void HAbstractBuilder::buildAll()
{
    readSettings();
    buildFactory();
    buildConfigManage();
    buildTestData();
    buildTemplate();
    buildDevice();
    buildThread();
    buildModel();
    buildMemento();
    buildDatabase();
    buildMenu();
    buildTestWidget();
    writeSettings();
}

void HAbstractBuilder::readSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    HCoreHelper::readSettings(fileName, "Builder", d_ptr->deploy);
}

void HAbstractBuilder::writeSettings()
{
    auto fileName = HAppContext::getContextValue<QString>("Settings");
    HCoreHelper::writeSettings(fileName, "Builder", d_ptr->deploy);
}

void HAbstractBuilder::buildFactory()
{
    d_ptr->sqlFactory = new HSqlFactory(this);
    d_ptr->guiFactory = new HGuiFactory(this);
    d_ptr->dataFactory = new HDataFactory(this);
    d_ptr->controllerFactory = new HControllerFactory(this);
    d_ptr->communicateFactory = new HCommunicateFactory(this);
    HAppContext::setContextPointer("ICommunicateFactory", d_ptr->communicateFactory);
    HAppContext::setContextPointer("IControllerFactory", d_ptr->controllerFactory);
    HAppContext::setContextPointer("IDataFactory", d_ptr->dataFactory);
    HAppContext::setContextPointer("IGuiFactory", d_ptr->guiFactory);
    HAppContext::setContextPointer("ISqlFactory", d_ptr->sqlFactory);
}

QString HAbstractBuilder::deployItem(const QString &key)
{
    return d_ptr->deploy.value(key).toString();
}

HE_END_NAMESPACE
