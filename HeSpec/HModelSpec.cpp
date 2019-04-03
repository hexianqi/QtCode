#include "HModelSpec_p.h"
#include "HeCore/HAppContext.h"
#include "HeData/IConfigManage.h"
#include "HeController/ITestSpec.h"
#include <QDebug>

HModelSpecPrivate::HModelSpecPrivate(HModelSpec *q) :
    HAbstractModelPrivate(q)
{
    testSpec = HAppContext::getContextPointer<ITestSpec>("ITestSpec");
}

HModelSpec::HModelSpec(QObject *parent) :
    HAbstractModel(*new HModelSpecPrivate(this), parent)
{
}

HModelSpec::~HModelSpec()
{
    qDebug() << __func__;
}

QString HModelSpec::typeName()
{
    return "HModelSpec";
}

void HModelSpec::syncTestData(quint32 type)
{
    Q_D(HModelSpec);
    if (type & ConfigContainType::CCT_Spec)
    {
        d->testSpec->setCalibrate(d->configManage->specCalibrate("1"));
        addAction(ACT_RESET_SPECTRUM);
    }
}


