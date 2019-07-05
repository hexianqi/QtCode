#include "HAbstractProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractProgress::HAbstractProgress(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAbstractProgressPrivate)
{
}

HAbstractProgress::HAbstractProgress(HAbstractProgressPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HAbstractProgress::~HAbstractProgress()
{
}

double HAbstractProgress::minimum() const
{
    return d_ptr->minimum;
}

double HAbstractProgress::maximum() const
{
    return d_ptr->maximum;
}

double HAbstractProgress::value() const
{
    return d_ptr->value;
}

int HAbstractProgress::decimal() const
{
    return d_ptr->decimal;
}

void HAbstractProgress::setRange(double minimum, double maximum)
{
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d_ptr->minimum = minimum;
    d_ptr->maximum = maximum;
    if (d_ptr->value < minimum || d_ptr->value > maximum)
        setValue(qBound(minimum, d_ptr->value, maximum));
    else
        update();
}

void HAbstractProgress::setMinimum(double value)
{
    setRange(value, d_ptr->maximum);
}

void HAbstractProgress::setMaximum(double value)
{
    setRange(d_ptr->minimum, value);
}

void HAbstractProgress::setValue(double value)
{
    if (value < d_ptr->minimum || value > d_ptr-> maximum || qFuzzyCompare(value, d_ptr->value))
        return;
    d_ptr->value = value;
    emit valueChanged(value);
    update();
}

void HAbstractProgress::setDecimal(int value)
{
    if (d_ptr->decimal == value)
        return;
    d_ptr->decimal = value;
    update();
}

double HAbstractProgress::range()
{
    return d_ptr->maximum - d_ptr->minimum;
}

double HAbstractProgress::toRatio(double value)
{
    return (value- d_ptr->minimum) / range();
}

double HAbstractProgress::fromRatio(double value)
{
    return value * range() + d_ptr->minimum;
}

HE_CONTROL_END_NAMESPACE
