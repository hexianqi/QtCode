#include "HElecCalibrate_p.h"
#include "IDataFactory.h"
#include "IElecCalibrateItem.h"
#include "IElecCalibrateItemCollection.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HElecCalibratePrivate::HElecCalibratePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HElecCalibrate::HElecCalibrate() :
    d_ptr(new HElecCalibratePrivate)
{
}

HElecCalibrate::HElecCalibrate(HElecCalibratePrivate &p) :
    d_ptr(&p)
{
}

HElecCalibrate::~HElecCalibrate()
{
}

void HElecCalibrate::initialize(QVariantMap /*param*/)
{

}

QString HElecCalibrate::typeName()
{
    return "HElecCalibrate";
}

void HElecCalibrate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, IElecCalibrateItemCollection>(s, d_ptr->datas, [=](QString type) { return d_ptr->factory->createElecCalibrateItemCollection(type); });
}

void HElecCalibrate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IElecCalibrateItemCollection>(s, d_ptr->datas);
}

void HElecCalibrate::setItemCollection(HElecType type, IElecCalibrateItemCollection *p)
{
    auto key = toString(type);
    if (!key.isEmpty())
        d_ptr->datas[key] = p;
}

IElecCalibrateItemCollection *HElecCalibrate::itemCollection(HElecType type)
{
    auto key = toString(type);
    if (key.isEmpty() || !d_ptr->datas.contains(key))
        return nullptr;
    return d_ptr->datas.value(key);
}

IElecCalibrateItem *HElecCalibrate::item(HElecType type, int index)
{
    auto i = itemCollection(type);
    return i == nullptr ? nullptr : i->itemAt(index);
}

double HElecCalibrate::toFiction(double value, HElecType type, int index)
{
    auto i = item(type, index);
    return i == nullptr ? 0.0 : i->toFiction(value);
}

double HElecCalibrate::toReal(double value, HElecType type, int index)
{
    auto i = item(type, index);
    return i == nullptr ? 0.0 : i->toReal(value);
}

QString HElecCalibrate::toString(HElecType type)
{
    switch (type)
    {
    case OutputVoltage:
        return "[输出电压]";
    case OutputCurrent:
        return "[输出电流]";
    case MeasuredVoltage:
        return "[实测电压]";
    case MeasuredCurrent:
        return "[实测电流]";
    case ReverseVoltage:
        return "[反向电压]";
    case ReverseCurrent:
        return "[反向漏流]";
    }
    return QString();
}

HE_END_NAMESPACE
