#include "HDataFormatInfo_p.h"
#include <QtGui/QDoubleValidator>

HE_CORE_BEGIN_NAMESPACE

HDataFormatInfo::HDataFormatInfo() :
    HDataFormatInfo("")
{
}

HDataFormatInfo::HDataFormatInfo(const QString &typeName, double min, double max, int decimals, double singleStep) :
    HDataFormatInfo(typeName, "", min, max, decimals, singleStep)
{
}

HDataFormatInfo::HDataFormatInfo(const QString &typeName, const QString &unit, double min, double max, int decimals, double singleStep, const QColor &color) :
    d_ptr(new HDataFormatInfoPrivate)
{
    d_ptr->typeName = typeName;
    d_ptr->unit = unit;
    d_ptr->color = color;
    d_ptr->decimals = decimals;
    d_ptr->min = min;
    d_ptr->max = max;
    d_ptr->singleStep = singleStep;
}

HDataFormatInfo::HDataFormatInfo(const HDataFormatInfo &rhs)
{
    d_ptr = rhs.d_ptr;
}

HDataFormatInfo::HDataFormatInfo(HDataFormatInfoPrivate &p) :
    d_ptr(&p)
{
}

HDataFormatInfo &HDataFormatInfo::operator=(const HDataFormatInfo &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

HDataFormatInfo::~HDataFormatInfo() = default;

void HDataFormatInfo::setTypeName(const QString &text)
{
    d_ptr->typeName = text;
}

void HDataFormatInfo::setUnit(const QString &text)
{
    d_ptr->unit = text;
}

void HDataFormatInfo::setColor(const QColor &value)
{
    d_ptr->color = value;
}

void HDataFormatInfo::setDecimals(int value)
{
    d_ptr->decimals = value;
}

void HDataFormatInfo::setMin(double value)
{
    d_ptr->min = value;
}

void HDataFormatInfo::setMax(double value)
{
    d_ptr->max = value;
}

void HDataFormatInfo::setRange(double min, double max, int decimals)
{
    d_ptr->min = min;
    d_ptr->max = max;
    d_ptr->decimals = decimals;
}

void HDataFormatInfo::setSingleStep(double value)
{
    d_ptr->singleStep = value;
}

QString HDataFormatInfo::typeName() const
{
    return d_ptr->typeName;
}

QString HDataFormatInfo::unit(bool withColor) const
{
    return withColor ? QString("<font color=%1>%2</font>").arg(color().name(), d_ptr->unit) : d_ptr->unit;
}

QColor HDataFormatInfo::color() const
{
    return d_ptr->color;
}

int HDataFormatInfo::decimals() const
{
    return d_ptr->decimals;
}

double HDataFormatInfo::min() const
{
    return d_ptr->min;
}

double HDataFormatInfo::max() const
{
    return d_ptr->max;
}

double HDataFormatInfo::singleStep() const
{
    return d_ptr->singleStep;
}

QDoubleValidator *HDataFormatInfo::toDoubleValidator(QObject * parent)
{
    auto v = new QDoubleValidator(min(), max(), decimals(), parent);
    v->setNotation(QDoubleValidator::StandardNotation);
    return v;
}

QIntValidator *HDataFormatInfo::toIntValidator(QObject *parent)
{
    return new QIntValidator(int(min()), int(max()), parent);
}

HE_CORE_END_NAMESPACE
