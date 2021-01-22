#include "HDaXinStrategy_p.h"
#include "HeData/ITestData.h"
#include "HeCommunicate/IProtocol.h"
#include <QtCore/QDebug>

HDaXinStrategyPrivate::HDaXinStrategyPrivate()
{
    actionSupport << ACT_SET_OUTPUT_VOLTAGE
                  << ACT_SET_OUTPUT_CURRENT
                  << ACT_SET_OVER_VOLTAGE
                  << ACT_SET_OVER_CURRENT
                  << ACT_SET_SOURCE_MODE
                  << ACT_SET_SOURCE_FORWARD
                  << ACT_SET_SOURCE_REVERSE
                  << ACT_SET_SOURCE_IO
                  << ACT_GET_ELEC_DATA;
}

HDaXinStrategy::HDaXinStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HDaXinStrategyPrivate, parent)
{
}

HDaXinStrategy::HDaXinStrategy(HDaXinStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HDaXinStrategy::~HDaXinStrategy()
{
    qDebug() << __func__;
}

QString HDaXinStrategy::typeName()
{
    return "HDaXinStrategy";
}

bool HDaXinStrategy::handle(HActionType action)
{
    Q_D(HDaXinStrategy);
    QVector<uchar> buff;
    uchar c;

    switch(action)
    {
    case ACT_SET_OUTPUT_VOLTAGE:
        return d->protocol->setData(action, int(d->testData->data("[输出电压]").toDouble() * 100));
    case ACT_SET_OUTPUT_CURRENT:
        return d->protocol->setData(action, d->testData->data("[输出电流]").toInt());
    case ACT_SET_OVER_VOLTAGE:
        return d->protocol->setData(action, int(d->testData->data("[过电压]").toDouble() * 100));
    case ACT_SET_OVER_CURRENT:
        return d->protocol->setData(action, d->testData->data("[过电流]").toInt());
    case ACT_SET_SOURCE_MODE:
        c = d->testData->data("[电源模式]").toInt();
        d->protocol->setData(ACT_SET_OUTPUT_VOLTAGE, c == 1 ? int(d->testData->data("[输出电压]").toDouble() * 100) : 1);
        return d->protocol->setData(action, c);
    case ACT_SET_SOURCE_FORWARD:
    case ACT_SET_SOURCE_REVERSE:
    case ACT_SET_SOURCE_IO:
        return d->protocol->setData(action, QVector<uchar>());
    case ACT_GET_ELEC_DATA:
        d->protocol->getData(action, buff);
        if (buff.length() >= 5)
        {
            d->testData->setData("[实测电压]", (buff[1] * 256.0 + buff[2]) / 100.0);
            d->testData->setData("[实测电流]", buff[3] * 256.0 + buff[4]);
            d->testData->setData("[电功率]", (buff[1] * 256.0 + buff[2]) * (buff[3] * 256.0 + buff[4]) / 100000.0);
        }
        return true;
    }
    return false;
}
