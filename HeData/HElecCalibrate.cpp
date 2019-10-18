#include "HElecCalibrate_p.h"
#include "IDataFactory.h"
#include "IElecCalibrateItem.h"
#include "IElecCalibrateItemCollection.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

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
    HDataHelper::read<QString, HeData::IElecCalibrateItemCollection>(s, d_ptr->datas, [=](QString type) { return d_ptr->factory->createElecCalibrateItemCollection(type); });
}

void HElecCalibrate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HDataHelper::write<QString, HeData::IElecCalibrateItemCollection>(s, d_ptr->datas);
}

void HElecCalibrate::setItemCollection(ElecType type, IElecCalibrateItemCollection *p)
{
    auto key = toString(type);
    if (!key.isEmpty())
        d_ptr->datas[key] = p;
}

IElecCalibrateItemCollection *HElecCalibrate::itemCollection(IElecCalibrate::ElecType type)
{
    auto key = toString(type);
    if (key.isEmpty() || !d_ptr->datas.contains(key))
        return nullptr;
    return d_ptr->datas.value(key);
}

IElecCalibrateItem *HElecCalibrate::item(ElecType type, int index)
{
    auto i = itemCollection(type);
    return i == nullptr ? nullptr : i->itemAt(index);
}

double HElecCalibrate::toFiction(double value, ElecType type, int index)
{
    auto i = item(type, index);
    return i == nullptr ? 0.0 : i->toFiction(value);
}

double HElecCalibrate::toReal(double value, ElecType type, int index)
{
    auto i = item(type, index);
    return i == nullptr ? 0.0 : i->toReal(value);
}

QString HElecCalibrate::toString(ElecType type)
{
    switch (type)
    {
    case SourceVoltage:
        return "[电源电压]";
    case ReverseVoltage:
        return "[反向电压]";
    case ForwardCurrent:
        return "[正向电流]";
    case ForwardVoltage:
        return "[正向电压]";
    case ReverseCurrent:
        return "[反向漏流]";
    case FeedbackCurrent:
        return "[回溯电流]";
    }
    return QString();
}

HE_DATA_END_NAMESPACE
