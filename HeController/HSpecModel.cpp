#include "HSpecModel_p.h"
#include "ITestSpec.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HSpecModelPrivate::HSpecModelPrivate(HSpecModel *q) :
    HAbstractModelPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecModel::HSpecModel(QObject *parent) :
    HAbstractModel(*new HSpecModelPrivate(this), parent)
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
    if (type & ConfigContainType::CCT_Spec)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        addAction(ACT_RESET_SPECTRUM);
    }
}

HE_CONTROLLER_END_NAMESPACE
