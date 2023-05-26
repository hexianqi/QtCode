#include "HStrategy1000RGB_p.h"
#include "HeCommunicate/IProtocol.h"
#include "HeData/ITestData.h"
#include <QtCore/QVector>

HStrategy1000RGBPrivate::HStrategy1000RGBPrivate()
{
    actionSupport << ACT_SET_SOURCE_MODE
                  << ACT_SET_OUTPUT_VOLTAGE
                  << ACT_SET_OUTPUT_CURRENT
                  << ACT_SET_GEARS_OUTPUT_CURRENT
                  << ACT_SET_GEARS_MEASURED_CURRENT
                  << ACT_SET_REVERSE_VOLTAGE
                  << ACT_SET_SOURCE_IO
                  << ACT_GET_ELEC_DATA
                  << ACT_GET_MEASURED_VOLTAGE
                  << ACT_GET_MEASURED_CURRENT
                  << ACT_GET_REVERSE_CURRENT;
}

HStrategy1000RGB::HStrategy1000RGB(QObject *parent) :
    HAbstractActionStrategy(*new HStrategy1000RGBPrivate, parent)
{
}

HStrategy1000RGB::~HStrategy1000RGB() = default;

QString HStrategy1000RGB::typeName()
{
    return "HStrategy1000RGB";
}

bool HStrategy1000RGB::handle(HActionType action)
{
    Q_D(HStrategy1000RGB);
    QVariantList samlpes;

    switch(action)
    {
    case ACT_SET_SOURCE_MODE:
        return d->protocol->setData(action, d->testData->data("[电源模式]").toInt());
    case ACT_SET_SOURCE_IO:
        return d->protocol->setData(ACT_SET_SOURCE_IO, d->testData->data("[电源开关]").toList());
    case ACT_SET_OUTPUT_VOLTAGE:
        return d->protocol->setData(action, d->testData->data("[输出电压_F]").toInt());
    case ACT_SET_REVERSE_VOLTAGE:
        return d->protocol->setData(action, d->testData->data("[反向电压_F]").toInt());
    case ACT_SET_OUTPUT_CURRENT:
        return d->protocol->setData(ACT_SET_OUTPUT_CURRENT, d->testData->data("[输出电流-RGBW_F]").toList());
    case ACT_SET_GEARS_OUTPUT_CURRENT:
    case ACT_SET_GEARS_MEASURED_CURRENT:
        if (!d->protocol->setData(ACT_SET_SOURCE_IO, d->testData->data("[电源开关]").toList()))
            return false;
        if (!d->protocol->setData(ACT_SET_GEARS_OUTPUT_CURRENT, d->testData->data("[电流_档位]").toInt()))
            return false;
        return d->protocol->setData(ACT_SET_OUTPUT_CURRENT, d->testData->data("[输出电流-RGBW_F]").toList());
    case ACT_GET_ELEC_DATA:
        d->protocol->getData(action, samlpes, QVariant::Int);
        d->testData->setData("[实测电压-RGBW_F]", QVariantList() << samlpes[0] << samlpes[3] << samlpes[6] << samlpes[9]);
        d->testData->setData("[实测电流-RGBW_F]", QVariantList() << samlpes[1] << samlpes[4] << samlpes[7] << samlpes[10]);
        d->testData->setData("[反向漏流-RGBW_F]", QVariantList() << samlpes[2] << samlpes[5] << samlpes[8] << samlpes[11]);
        return true;
    case ACT_GET_MEASURED_VOLTAGE:
        d->protocol->getData(action, samlpes, QVariant::Int);
        d->testData->setData("[实测电压-RGBW_F]", samlpes);
        return true;
    case ACT_GET_MEASURED_CURRENT:
        d->protocol->getData(action, samlpes, QVariant::Int);
        d->testData->setData("[实测电流-RGBW_F]", samlpes);
        return true;
    case ACT_GET_REVERSE_CURRENT:
        d->protocol->getData(action, samlpes, QVariant::Int);
        d->testData->setData("[反向漏流-RGBW_F]", samlpes);
        return true;
    }
    return false;
}
