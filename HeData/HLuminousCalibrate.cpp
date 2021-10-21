#include "HLuminousCalibrate_p.h"
#include "IDataFactory.h"
#include "ILuminousCalibrateItem.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HLuminousCalibratePrivate::HLuminousCalibratePrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HLuminousCalibrate::HLuminousCalibrate() :
    ILuminousCalibrate(*new HLuminousCalibratePrivate)
{
}

HLuminousCalibrate::HLuminousCalibrate(HLuminousCalibratePrivate &p) :
    ILuminousCalibrate(p)
{
}

HLuminousCalibrate::~HLuminousCalibrate()
{
}

QString HLuminousCalibrate::typeName()
{
    return "HLuminousCalibrate";
}

void HLuminousCalibrate::readContent(QDataStream &s)
{
    Q_D(HLuminousCalibrate);
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, HeData::ILuminousCalibrateItem>(s, d->items, [=](QString type) { return d->factory->createLuminousCalibrateItem(type); });
}

void HLuminousCalibrate::writeContent(QDataStream &s)
{
    Q_D(HLuminousCalibrate);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::ILuminousCalibrateItem>(s, d->items);
}

void HLuminousCalibrate::setTotalGears(int value)
{
    for (auto i : values())
        i->setTotalGears(value);
}

int HLuminousCalibrate::totalGears()
{
    return size() > 0 ? first()->totalGears() : 0;
}

double HLuminousCalibrate::toReal(double value, QString type, int index)
{
    if (!contains(type))
        return 0.0;
    return item(type)->toReal(value, index);
}

HE_DATA_END_NAMESPACE
