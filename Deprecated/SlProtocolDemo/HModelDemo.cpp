#include "HModelDemo_p.h"
#include "HTestWidgetDemo.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include "HeController/IThread.h"
#include "HeController/IThreadCollection.h"
#include "HeController/HDelayThread.h"
#include <QtCore/QDebug>

HModelDemoPrivate::HModelDemoPrivate(IModel *q) :
    HAbstractModelPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HTestWidgetDemo *HModelDemoPrivate::widget()
{
    if (testWidget == nullptr)
        testWidget = HAppContext::getContextPointer<HTestWidgetDemo>("ITestWidget");
    return testWidget;
}

HModelDemo::HModelDemo(QObject *parent) :
    HAbstractModel(*new HModelDemoPrivate(this), parent)
{
}

HModelDemo::~HModelDemo()
{
    qDebug() << __func__;
}

void HModelDemo::initialize(QVariantMap /*param*/)
{

}

QString HModelDemo::typeName()
{
    return "HModelDemo";
}

void HModelDemo::syncTestData(quint32 type)
{
    Q_D(HModelDemo);
    if (type & IConfigManage::ContainSpec)
    {
        auto c = d->configManage->specCalibrate("1");
        d->testSpec->setCalibrate(c);
        d->widget()->setSpecCalibrate(c);
        addAction(ACT_RESET_SPECTRUM);
    }
}

void HModelDemo::syncMachine(quint32 type)
{
    if (type & IConfigManage::ContainSpec)
        addAction(ACT_SET_INTEGRAL_TIME);
}
