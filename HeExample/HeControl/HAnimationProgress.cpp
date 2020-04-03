#include "HAnimationProgress_p.h"
#include <QtCore/QPropertyAnimation>

HE_CONTROL_BEGIN_NAMESPACE

HAnimationProgress::HAnimationProgress(QWidget *parent) :
    HAbstractProgress(*new HAnimationProgressPrivate, parent)
{
    init();
}

HAnimationProgress::HAnimationProgress(HAnimationProgressPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
    init();
}

HAnimationProgress::~HAnimationProgress()
{
}

bool HAnimationProgress::isAnimationEnable() const
{
    Q_D(const HAnimationProgress);
    return d->animationEnable;
}

int HAnimationProgress::duration() const
{
    Q_D(const HAnimationProgress);
    return d->animation->duration();
}

double HAnimationProgress::currentValue() const
{
    Q_D(const HAnimationProgress);
    return d->currentValue;
}

void HAnimationProgress::setValue(double value)
{
    Q_D(HAnimationProgress);
    if (value < d_ptr->minimum || value > d_ptr->maximum || qFuzzyCompare(value, d_ptr->value))
        return;
    d_ptr->value = value;
    emit valueChanged(value);
    if (d->animationEnable)
    {
        d->animation->setStartValue(d->currentValue);
        d->animation->setEndValue(value);
        d->animation->start();
    }
    else
    {
        d->currentValue = value;
        update();
    }
}

void HAnimationProgress::setAnimationEnable(bool b)
{
    Q_D(HAnimationProgress);
    if (d->animationEnable == b)
        return;
    d->animationEnable = b;
}

void HAnimationProgress::setDuration(int value)
{
    Q_D(HAnimationProgress);
    if (d->animation->duration() == value)
        return;
    d->animation->setDuration(value);
}

void HAnimationProgress::setCurrentValue(double value)
{
    Q_D(HAnimationProgress);
    if (qFuzzyCompare(d->currentValue, value))
        return;
    d->currentValue = value;
    update();
}

void HAnimationProgress::init()
{
    Q_D(HAnimationProgress);
//    d->animation = new QPropertyAnimation(this, "currentValue", this);
    d->animation = new QPropertyAnimation(this);
    d->animation->setTargetObject(this);
    d->animation->setEasingCurve(QEasingCurve::Linear);
    connect(d->animation, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setCurrentValue(value.toDouble()); });
}

HE_CONTROL_END_NAMESPACE
