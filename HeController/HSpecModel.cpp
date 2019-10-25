#include "HSpecModel_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecModelPrivate::HSpecModelPrivate(IModel *q) :
    HAbstractModelPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecModel::HSpecModel(QObject *parent) :
    HAbstractModel(*new HSpecModelPrivate(this), parent)
{
}

HSpecModel::HSpecModel(HSpecModelPrivate &p, QObject *parent) :
    HAbstractModel(p, parent)
{
}

HSpecModel::~HSpecModel()
{
    qDebug() << __func__;
}

void HSpecModel::initialize(QVariantMap /*param*/)
{

}

QString HSpecModel::typeName()
{
    return "HSpecModel";
}

void HSpecModel::syncTestData(quint32 type)
{
    Q_D(HSpecModel);
    if (type & IConfigManage::ContainSpec)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        addAction(ACT_RESET_SPECTRUM);
    }
    if (type & IConfigManage::ContainGrade)
        addAction(ACT_RESET_GRADE);
}

void HSpecModel::syncMachine(quint32 type)
{
    if (type & IConfigManage::ContainSpec)
    {
        addAction(ACT_SET_INTEGRAL_TIME);
    }
}

HE_CONTROLLER_END_NAMESPACE
