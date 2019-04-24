#include "HAbstractBuilder_p.h"
#include "IMainWindow.h"
#include "HeCore/HAppContext.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/HControllerFactory.h"
#include "HeData/HDataFactory.h"
#include "HeGui/HGuiFactory.h"
#include "HeSql/HSqlFactory.h"
#include <QtCore/QDebug>

HE_GUI_BEGIN_NAMESPACE

HAbstractBuilder::HAbstractBuilder(IMainWindow *parent) :
    QObject(parent),
    d_ptr(new HAbstractBuilderPrivate)
{
    HAppContext::setContextPointer("IMainWindow", parent);
}

HAbstractBuilder::HAbstractBuilder(HAbstractBuilderPrivate &p, IMainWindow *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractBuilder::~HAbstractBuilder()
{
    qDebug() << __func__;
}

void HAbstractBuilder::buildAll()
{
    buildFactory();
    buildConfigManage();
    buildTestData();
    buildDevice();
    buildThread();
    buildModel();
    buildDatabase();
    buildTestWidget();
}

void HAbstractBuilder::buildFactory()
{
    d_ptr->communicateFactory = new HCommunicateFactory(this);
    d_ptr->controllerFactory = new HControllerFactory(this);
    d_ptr->dataFactory = new HDataFactory(this);
    d_ptr->guiFactory = new HGuiFactory(this);
    d_ptr->sqlFactory = new HSqlFactory(this);
    HAppContext::setContextPointer("ICommunicateFactory", d_ptr->communicateFactory);
    HAppContext::setContextPointer("IControllerFactory", d_ptr->controllerFactory);
    HAppContext::setContextPointer("IDataFactory", d_ptr->dataFactory);
    HAppContext::setContextPointer("IGuiFactory", d_ptr->guiFactory);
    HAppContext::setContextPointer("ISqlFactory", d_ptr->sqlFactory);
}

HE_GUI_END_NAMESPACE
