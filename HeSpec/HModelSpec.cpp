#include "HModelSpec_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/ITestSpec.h"
#include "HeData/IConfigManage.h"
#include "HeGui/HSpecCalibrateWidget.h"
#include <QtCore/QDebug>

HModelSpecPrivate::HModelSpecPrivate(IModel *q) :
    HAbstractModelPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecCalibrateWidget *HModelSpecPrivate::widget()
{
    if (testWidget == nullptr)
        testWidget = HAppContext::getContextPointer<HSpecCalibrateWidget>("ITestWidget");
    return testWidget;
}

HModelSpec::HModelSpec(QObject *parent) :
    HAbstractModel(*new HModelSpecPrivate(this), parent)
{
}

HModelSpec::~HModelSpec()
{
    qDebug() << __func__;
}

void HModelSpec::initialize(QVariantMap /*param*/)
{

}

QString HModelSpec::typeName()
{
    return "HModelSpec";
}

void HModelSpec::syncTestData(quint32 type)
{
    Q_D(HModelSpec);
    if (type & IConfigManage::ContainSpec)
    {
        auto c = d->configManage->specCalibrate("1");
        d->testSpec->setCalibrate(c);
        d->widget()->setCalibrate(c);
        addAction(ACT_RESET_SPECTRUM);
    }
}

void HModelSpec::syncMachine(quint32 type)
{
    if (type & IConfigManage::ContainSpec)
        addAction(ACT_SET_INTEGRAL_TIME);
}
