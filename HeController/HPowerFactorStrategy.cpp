#include "HPowerFactorStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QDebug>

HE_CONTROLLER_BEGIN_NAMESPACE

HPowerFactorStrategyPrivate::HPowerFactorStrategyPrivate()
{
    actionSupport << ACT_GET_ELEC_DATA;
}

HPowerFactorStrategy::HPowerFactorStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HPowerFactorStrategyPrivate, parent)
{
}

HPowerFactorStrategy::HPowerFactorStrategy(HPowerFactorStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HPowerFactorStrategy::~HPowerFactorStrategy()
{
    qDebug() << __func__;
}

QString HPowerFactorStrategy::typeName()
{
    return "HPowerFactorStrategy";
}

bool HPowerFactorStrategy::handle(HActionType action)
{
    Q_D(HPowerFactorStrategy);
    if (action == ACT_GET_ELEC_DATA)
    {
        QVector<double> data;
        if (d->protocol->getData(action, data) && data.size() >= 4)
        {
            d->testData->setData("[交流电压]", data[0]);
            d->testData->setData("[交流电流]", data[1]);
            d->testData->setData("[交流电功率]", data[2]);
            d->testData->setData("[功率因数]", data[3]);
            return true;
        }
    }
    return false;
}

HE_CONTROLLER_END_NAMESPACE
