#include "HKeyenceStrategy_p.h"

HKeyenceStrategyPrivate::HKeyenceStrategyPrivate()
{
    actionSupport << ACT_SET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_LOCATION
                  << ACT_RESET_MOTOR_STATE
                  << ACT_QUERY_MOTOR_STATE;
}

HKeyenceStrategy::HKeyenceStrategy(QObject *parent) :
    HAbstractActionStrategy(*new HKeyenceStrategyPrivate, parent)
{
}

HKeyenceStrategy::HKeyenceStrategy(HKeyenceStrategyPrivate &p, QObject *parent) :
    HAbstractActionStrategy(p, parent)
{
}

HKeyenceStrategy::~HKeyenceStrategy() = default;

QString HKeyenceStrategy::typeName()
{
    return "HKeyenceStrategy";
}

bool HKeyenceStrategy::handle(HActionType action)
{
//    Q_D(HKeyenceStrategy);
//    QVector<uchar> buff;
//    uchar c;

//    switch(action)
//    {
//    case ACT_SET_OUTPUT_VOLTAGE:
//        return d->protocol->setData(action, int(d->testData->data("[输出电压]").toDouble() * 100));
//    case ACT_SET_OUTPUT_CURRENT:
//        return d->protocol->setData(action, d->testData->data("[输出电流]").toInt());
//    case ACT_SET_OVER_VOLTAGE:
//        return d->protocol->setData(action, int(d->testData->data("[过电压]").toDouble() * 100));
//    case ACT_SET_OVER_CURRENT:
//        return d->protocol->setData(action, d->testData->data("[过电流]").toInt());
//    case ACT_SET_SOURCE_MODE:
//        c = d->testData->data("[电源模式]").toInt();
//        d->protocol->setData(ACT_SET_OUTPUT_VOLTAGE, c == 1 ? int(d->testData->data("[输出电压]").toDouble() * 100) : 1);
//        return d->protocol->setData(action, c);
//    case ACT_SET_SOURCE_FORWARD:
//    case ACT_SET_SOURCE_REVERSE:
//    case ACT_SET_SOURCE_IO:
//        return d->protocol->setData(action, QVector<uchar>());
//    case ACT_GET_ELEC_DATA:
//        d->protocol->getData(action, buff);
//        if (buff.length() >= 5)
//        {
//            d->testData->setData("[实测电压]", (buff[1] * 256.0 + buff[2]) / 100.0);
//            d->testData->setData("[实测电流]", buff[3] * 256.0 + buff[4]);
//            d->testData->setData("[电功率]", (buff[1] * 256.0 + buff[2]) * (buff[3] * 256.0 + buff[4]) / 100000.0);
//        }
//        return true;
//    }
    return true;
    return false;
}


