#include "HDataFormatInfo_p.h"
#include <QDoubleValidator>

HE_CORE_USE_NAMESPACE

void HDataFormatInfoPrivate::init(QString typeName, QString unit, double min, double max, int decimals, double singleStep, QColor color)
{
    this->typeName = typeName;
    this->unit = unit;
    this->color = color;
    this->decimals = decimals;
    this->min = min;
    this->max = max;
    this->singleStep = singleStep;
}

HDataFormatInfo::HDataFormatInfo()
    : d_ptr(new HDataFormatInfoPrivate)
{
}

HDataFormatInfo::HDataFormatInfo(QString typeName, double min, double max, int decimals, double singleStep)
    : HDataFormatInfo()
{
    d_ptr->init(typeName, "", min, max, decimals, singleStep);
}

HDataFormatInfo::HDataFormatInfo(QString typeName, QString unit, double min, double max, int decimals, double singleStep, QColor color)
    : HDataFormatInfo()
{
    d_ptr->init(typeName, unit, min, max, decimals, singleStep, color);
}

HDataFormatInfo::HDataFormatInfo(const HDataFormatInfo &rhs)
    : d_ptr(rhs.d_ptr)
{
}

HDataFormatInfo::HDataFormatInfo(HDataFormatInfoPrivate &p)
    : d_ptr(&p)
{
}

HDataFormatInfo &HDataFormatInfo::operator=(const HDataFormatInfo &rhs)
{
    if (this != &rhs)
        d_ptr.operator=(rhs.d_ptr);
    return *this;
}

HDataFormatInfo::~HDataFormatInfo()
{
}

void HDataFormatInfo::setTypeName(QString text)
{
    d_ptr->typeName = text;
}

void HDataFormatInfo::setUnit(QString text)
{
    d_ptr->unit = text;
}

void HDataFormatInfo::setColor(QColor value)
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
    return withColor ? QString("<font color=%1>%2</font>").arg(color().name()).arg(d_ptr->unit) : d_ptr->unit;
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
    QDoubleValidator *v = new QDoubleValidator(min(), max(), decimals(), parent);
    v->setNotation(QDoubleValidator::StandardNotation);
    return v;
}

QIntValidator *HDataFormatInfo::toIntValidator(QObject *parent)
{
    return new QIntValidator(static_cast<int>(min()), static_cast<int>(max()), parent);
}

//void HDataFormatInfo::toInitWidget(QSpinBox *widget)
//{
//    widget->setRange(int(_botton), int(_top));
//    widget->setSingleStep(_singleStep);
//    widget->setSuffix(QString(" %1 ").arg(unit(false)));
//    widget->setAlignment(Qt::AlignCenter);
//}

//void HDataFormatInfo::toInitWidget(QDoubleSpinBox *widget)
//{
//    widget->setDecimals(_decimals);
//    widget->setRange(_botton, _top);
//    widget->setSingleStep(_singleStep);
//    widget->setSuffix(QString(" %1 ").arg(unit(false)));
//    widget->setAlignment(Qt::AlignCenter);
//}
