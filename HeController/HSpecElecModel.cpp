#include "HSpecElecModel_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include "HeData/ITestElec.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecElecModelPrivate::HSpecElecModelPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
}

HSpecElecModel::HSpecElecModel(QObject *parent) :
    HAbstractModel(*new HSpecElecModelPrivate, parent)
{
}

HSpecElecModel::HSpecElecModel(HSpecElecModelPrivate &p, QObject *parent) :
    HAbstractModel(p, parent)
{
}

HSpecElecModel::~HSpecElecModel()
{
    qDebug() << __func__;
}

void HSpecElecModel::initialize(QVariantMap /*param*/)
{
}

QString HSpecElecModel::typeName()
{
    return "HSpecElecModel";
}

void HSpecElecModel::syncTestData(quint32 type)
{
    Q_D(HSpecElecModel);
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
    if ((type & IConfigManage::ContainGrade) != 0u)
    {
        addAction(ACT_RESET_GRADE);
    }
}

void HSpecElecModel::syncDevice(quint32 type)
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
}

HE_CONTROLLER_END_NAMESPACE
