#include "HMainWindow2000_p.h"
#include "HModel2000.h"
#include "HeCore/HAppContext.h"
#include "HeCore/HCore.h"
#include "HeCommunicate/HCommunicateFactory.h"
#include "HeController/HTestDataFactory.h"
#include "HeController/HTestSpec.h"
#include <QMessageBox>
#include <QTimer>
#include <QSettings>

HE_CONTROLLER_USE_NAMESPACE

HMainWindow2000Private::HMainWindow2000Private(HMainWindow2000 *q)
    : HMainWindowPrivate(q)
{
}


HMainWindow2000::HMainWindow2000(QWidget *parent)
    : HMainWindow(*new HMainWindow2000Private(this), parent)
{

}

HMainWindow2000::HMainWindow2000(HMainWindow2000Private &p, QWidget *parent)
    : HMainWindow(p, parent)
{
}

HMainWindow2000::~HMainWindow2000()
{
}

void HMainWindow2000::init()
{
    HMainWindow::init();

    Q_D(HMainWindow2000);
    HAppContext::setContextValue("Settings", "Ini\\SL2000.ini");
    HAppContext::setContextPointer("MainWindow", this);
    HAppContext::setContextPointer("ICommunicateFactory", new HCommunicateFactory);
    ITestDataFactory *testFactroy = new HTestDataFactory;
    HAppContext::setContextPointer("ITestDataFactory", testFactroy);
    HAppContext::setContextPointer("ITestSpec", testFactroy->createTestSpec(""));




    d->model = new HModel2000(this);
//    connect(d->model, &IModel::deviceFailed, this, [=](QString text) { QMessageBox::critical(this, "", text); });
//    connect(d->model, &IModel::initThreadFinished, this, [=](QStringList list) { QMessageBox::information(this, "", list.join("-")); });
//    connect(d->model, &IModel::threadStateChanged, this, [=](QString name, int state) { QMessageBox::information(this, "", tr("%1:%2").arg(name).arg(state)); });
//    connect(d->model, &IModel::actionFailed, this, [=](HActionType action, QString text) { QMessageBox::warning(this, "", text); });
//    connect(d->model, &IModel::actionFinished, this, [=](HActionType action) { QMessageBox::information(this, "", toComment(action)); });
//
    HAppContext::setContextPointer("IModel", d->model);
    d->model->initConfig();
}

