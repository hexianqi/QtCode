#include "HQuality_p.h"
#include "HQualityItemCollection.h"
#include <QtCore/QDataStream>
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

HQualityPrivate::HQualityPrivate()
{
    colors.insert(HQualityReport::InvalidData,  Qt::yellow);
    colors.insert(HQualityReport::Broken,       Qt::gray);
    colors.insert(HQualityReport::NoPass,       Qt::red);
    colors.insert(HQualityReport::Passing,      Qt::green);
    colors.insert(HQualityReport::Spacer,       Qt::transparent);
    damages = new HQualityItemCollection;
    criterions = new HQualityItemCollection;
}

HQuality::HQuality() :
    d_ptr(new HQualityPrivate)
{
}

HQuality::HQuality(HQualityPrivate &p) :
    d_ptr(&p)
{
}

HQuality::~HQuality()
{

}

void HQuality::initialize(QVariantMap /*param*/)
{
}

QString HQuality::typeName()
{
    return "HQuality";
}

void HQuality::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> d_ptr->colors;
    d_ptr->damages->readContent(s);
    d_ptr->criterions->readContent(s);
}

void HQuality::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << d_ptr->colors;
    d_ptr->damages->writeContent(s);
    d_ptr->criterions->writeContent(s);
}

IQualityItemCollection *HQuality::itemCollection(HQualityType type)
{
    if (type == Damage)
        return d_ptr->damages;
    if (type == Criterion)
        return d_ptr->criterions;
    return nullptr;
}

void HQuality::setColor(HQualityReport type, const QColor &value)
{
    d_ptr->colors.insert(type, value);
}

QColor HQuality::color(HQualityReport type)
{
    return d_ptr->colors.value(type, Qt::transparent);
}

HQualityReport HQuality::check(QVariantMap value, QVariantMap *color)
{
    if (value.isEmpty())
        return HQualityReport::InvalidData;
    if (!d_ptr->damages->isValid(value))
        return HQualityReport::InvalidData;
    if (!d_ptr->criterions->isValid(value))
        return HQualityReport::InvalidData;
    if (!d_ptr->damages->check(value, color))
        return HQualityReport::Broken;
    if (!d_ptr->criterions->check(value, color))
        return HQualityReport::NoPass;
    return HQualityReport::Passing;
}

double HQuality::drift(QString type, QVariant value)
{
    return d_ptr->criterions->drift(type, value);
}

HE_END_NAMESPACE

