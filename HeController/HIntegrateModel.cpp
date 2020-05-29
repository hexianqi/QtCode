#include "HIntegrateModel_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include "HeData/ITestLuminous.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HIntegrateModelPrivate::HIntegrateModelPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
    testLuminous = HAppContext::getContextPointer<ITestLuminous>("ITestLuminous");
}

HIntegrateModel::HIntegrateModel(QObject *parent) :
    HAbstractModel(*new HIntegrateModelPrivate, parent)
{
}

HIntegrateModel::HIntegrateModel(HIntegrateModelPrivate &p, QObject *parent) :
    HAbstractModel(p, parent)
{
}

HIntegrateModel::~HIntegrateModel()
{
    qDebug() << __func__;
}

void HIntegrateModel::initialize(QVariantMap /*param*/)
{

}

QString HIntegrateModel::typeName()
{
    return "HIntegrateModel";
}

void HIntegrateModel::syncTestData(quint32 type)
{
    Q_D(HIntegrateModel);
    if ((type & IConfigManage::ContainSpec) != 0u)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        addAction(ACT_RESET_SPECTRUM);
//        type &= ~IConfigManage::ContainSpec;
    }
    if ((type & IConfigManage::ContainElec) != 0u)
    {
        d->testElec->setCalibrate(d->configManage->elecCalibrateCollection());
        addAction(ACT_RESET_ELEC);
    }
    if ((type & IConfigManage::ContainLuminous) != 0u)
    {
        d->testLuminous->setCalibrate(d->configManage->luminousCalibrateCollection());
        addAction(ACT_RESET_LUMINOUS);
    }
    if ((type & IConfigManage::ContainGrade) != 0u)
    {
        addAction(ACT_RESET_GRADE);
    }
}

void HIntegrateModel::syncMachine(quint32 type)
{
    if ((type & IConfigManage::ContainSpec) != 0u)
        addAction(ACT_SET_INTEGRAL_TIME);
    if ((type & IConfigManage::ContainElec) != 0u)
    {
        addAction(ACT_GET_REVERSE_CURRENT);
        addAction(ACT_SET_OUTPUT_VOLTAGE);
        addAction(ACT_SET_GEARS_MEASURED_CURRENT);
        addAction(ACT_SET_OUTPUT_CURRENT);
        addAction(ACT_SET_SOURCE_MODE);
    }
    if ((type & IConfigManage::ContainLuminous) != 0u)
    {
        addAction(ACT_SET_LUMINOUS_TYPE);
        addAction(ACT_SET_LUMINOUS_GEARS);
    }
}

HE_CONTROLLER_END_NAMESPACE
