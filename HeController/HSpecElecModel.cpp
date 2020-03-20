#include "HSpecElecModel_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestElec.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecElecModelPrivate::HSpecElecModelPrivate()
{
    testElec = HAppContext::getContextPointer<ITestElec>("ITestElec");
}

HSpecElecModel::HSpecElecModel(QObject *parent) :
    HSpecModel(*new HSpecElecModelPrivate, parent)
{
}

HSpecElecModel::HSpecElecModel(HSpecElecModelPrivate &p, QObject *parent) :
    HSpecModel(p, parent)
{
}

HSpecElecModel::~HSpecElecModel()
{
    qDebug() << __func__;
}

QString HSpecElecModel::typeName()
{
    return "HSpecElecModel";
}

void HSpecElecModel::syncTestData(quint32 type)
{
    Q_D(HSpecElecModel);
    if (type & IConfigManage::ContainElec)
    {
        d->testElec->setCalibrate(d->configManage->elecCalibrateCollection());
        addAction(ACT_RESET_ELEC);
        type &= ~IConfigManage::ContainElec;
    }
    HSpecModel::syncTestData(type);
}

void HSpecElecModel::syncMachine(quint32 type)
{
    if (type & IConfigManage::ContainElec)
    {
        addAction(ACT_GET_REVERSE_CURRENT);
        addAction(ACT_SET_OUTPUT_VOLTAGE);
        addAction(ACT_SET_GEARS_MEASURED_CURRENT);
        addAction(ACT_SET_OUTPUT_CURRENT);
        addAction(ACT_SET_SOURCE_MODE);
        type &= ~IConfigManage::ContainElec;
    }
    HSpecModel::syncMachine(type);
}

HE_CONTROLLER_END_NAMESPACE
