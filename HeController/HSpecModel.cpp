#include "HSpecModel_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeData/ITestSpec.h"

HE_BEGIN_NAMESPACE

HSpecModelPrivate::HSpecModelPrivate()
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HSpecModel::HSpecModel(QObject *parent) :
    HAbstractModel(*new HSpecModelPrivate, parent)
{
}

HSpecModel::HSpecModel(HSpecModelPrivate &p, QObject *parent) :
    HAbstractModel(p, parent)
{
}

HSpecModel::~HSpecModel() = default;

QString HSpecModel::typeName()
{
    return "HSpecModel";
}

void HSpecModel::syncTestData(quint32 type)
{
    Q_D(HSpecModel);
    if ((type & IConfigManage::ContainSpec) != 0u)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        addAction(ACT_RESET_SPECTRUM);
    }
    if ((type & IConfigManage::ContainGrade) != 0u)
        addAction(ACT_RESET_GRADE);
}

void HSpecModel::syncDevice(quint32 type)
{
    if ((type & IConfigManage::ContainSpec) != 0u)
        addAction(ACT_SET_INTEGRAL_TIME);
}

HE_END_NAMESPACE
