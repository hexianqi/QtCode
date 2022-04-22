#include "HAbstractBuilder_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCoreHelper.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/HControllerFactory.h"
#include "HeData/HDataFactory.h"
#include "HeGui/HGuiFactory.h"
#include "HeSql/HSqlFactory.h"
#include "HeSql/ISqlBrowser.h"
#include "HeSql/ISqlHandle.h"
#include "HeSql/ISqlOutput.h"
#include "HeSql/ISqlTableModel.h"

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

ISqlTableModel *HAbstractBuilder::createSqlTableModel(QString name, QStringList field)
{
    auto model = d_ptr->sqlFactory->createTableModel("HSqlTableModel");
    auto handle = d_ptr->sqlFactory->createHandle("HSqlHandle");
    auto output = d_ptr->sqlFactory->createOutput("HSqlOutput");
    auto browser = d_ptr->sqlFactory->createBrowser("HSqlBrowser", d_ptr->mainWindow);
    auto text = HAppContext::getContextPointer<ITextExportTemplate>(QString("I%1TextExportTemplate").arg(name));
    auto print = HAppContext::getContextPointer<IPrintTemplate>(QString("I%1PrintTemplate").arg(name));
    model->setTableField(name, field);
    handle->setModel(model);
    output->setModel(model);
    output->setTextTemplate(text);
    output->setPrintTemplate(print);
    browser->setModel(model);
    browser->setRecordHandle(handle);
    browser->setRecordOutput(output);
    HAppContext::setContextPointer(QString("I%1SqlHandle").arg(name), handle);
    HAppContext::setContextPointer(QString("I%1SqlBrowser").arg(name), browser);
    return model;
}

QString HAbstractBuilder::deployItem(const QString &key)
{
    return d_ptr->deploy.value(key).toString();
}

HE_END_NAMESPACE
