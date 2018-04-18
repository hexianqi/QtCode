#include "HDataFormatInfo.h"
#include <QDoubleValidator>

using namespace He::Core;

HDataFormatInfo::HDataFormatInfo()
{
    initialize("");
}

HDataFormatInfo::HDataFormatInfo(QString type, double min, double max, int decimals, double singleStep)
{
    initialize(type, "", min, max, decimals, singleStep);
}

HDataFormatInfo::HDataFormatInfo(QString type, QString unit, double min, double max, int decimals, double singleStep, QColor color)
{
    initialize(type, unit, min, max, decimals, singleStep, color);
}

void HDataFormatInfo::initialize(QString type, QString unit, double min, double max, int decimals, double singleStep, QColor color)
{
    _type = type;
    _unit = unit;
    _color = color;
    _decimals = decimals;
    _botton = min;
    _top = max;
    _singleStep = singleStep;
}

void HDataFormatInfo::setType(QString text)
{
    _type = text;
}

void HDataFormatInfo::setUnit(QString text)
{
    _unit = text;
}

void HDataFormatInfo::setColor(QColor value)
{
    _color = value;
}

void HDataFormatInfo::setDecimals(int value)
{
    _decimals = value;
}

void HDataFormatInfo::setBotton(double value)
{
    _botton = value;
}

void HDataFormatInfo::setTop(double value)
{
    _top = value;
}

void HDataFormatInfo::setRange(double min, double max, int decimals)
{
    _botton = min;
    _top = max;
    _decimals = decimals;
}

void HDataFormatInfo::setSingleStep(double value)
{
    _singleStep = value;
}

QString HDataFormatInfo::unit(bool color) const
{
    return color ? QString("<font color=%1>%2</font>").arg(_color.name()).arg(_unit) : _unit;
}

QDoubleValidator *HDataFormatInfo::toDoubleValidator(QObject * parent)
{
    QDoubleValidator *v = new QDoubleValidator(_botton, _top, _decimals, parent);
    v->setNotation(QDoubleValidator::StandardNotation);
    return v;
}

QIntValidator *HDataFormatInfo::toIntValidator(QObject *parent)
{
    return new QIntValidator(static_cast<int>(_botton), static_cast<int>(_top), parent);
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
