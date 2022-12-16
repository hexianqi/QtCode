#include "HColorGradientRoundedButton_p.h"
#include "HDrawHelper.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsDropShadowEffect>

HE_BEGIN_NAMESPACE

QVariant colorInterpolator(const HDoubleColor &start, const HDoubleColor &end, qreal progress)
{
    auto fr = start.frist.red() + ((end.frist.red() - start.frist.red()) * progress);
    auto fg = start.frist.green() + ((end.frist.green() - start.frist.green()) * progress);
    auto fb = start.frist.blue() + ((end.frist.blue() - start.frist.blue()) * progress);
    auto sr = start.second.red() + ((end.second.red() - start.second.red()) * progress);
    auto sg = start.second.green() + ((end.second.green() - start.second.green()) * progress);
    auto sb = start.second.blue() + ((end.second.blue() - start.second.blue()) * progress);

    return QVariant::fromValue(HDoubleColor(QColor(fr, fg, fb), QColor(sr, sg, sb)));
}

HDoubleColor::HDoubleColor(QColor frist, QColor second)
{
    this->frist = frist;
    this->second = second;
}

bool HDoubleColor::operator!=(const HDoubleColor &other)
{
    return (this->frist != other.frist) || (this->second != other.second);
}

bool HDoubleColor::operator==(const HDoubleColor &other)
{
    return (this->frist == other.frist) && (this->second == other.second);
}

HColorGradientRoundedButton::HColorGradientRoundedButton(QWidget *parent) :
    QAbstractButton(parent),
    d_ptr(new HColorGradientRoundedButtonPrivate)
{
    init();
}

HColorGradientRoundedButton::HColorGradientRoundedButton(HColorGradientRoundedButtonPrivate &p, QWidget *parent) :
    QAbstractButton(parent),
    d_ptr(&p)
{
    init();
}

HColorGradientRoundedButton::~HColorGradientRoundedButton()
{
}

HDoubleColor HColorGradientRoundedButton::currentColor() const
{
    return d_ptr->currentColor;
}

void HColorGradientRoundedButton::setCurrentColor(const HDoubleColor &value)
{
    if (d_ptr->currentColor == value)
        return;
    d_ptr->currentColor = value;
    update();
}

void HColorGradientRoundedButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainterPath path;
    path.addRoundedRect(rect(), 25, 25);
    QLinearGradient linearGradient(rect().topLeft(), rect().topRight());
    linearGradient.setColorAt(0, d_ptr->currentColor.frist);
    linearGradient.setColorAt(1, d_ptr->currentColor.second);
    auto font = painter.font();
    font.setBold(true);
    font.setPixelSize(20);

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setClipPath(path);
    painter.drawRect(rect());
    painter.fillRect(rect(), linearGradient);
    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, text());
}

void HColorGradientRoundedButton::enterEvent(QEvent *event)
{
    if (d_ptr->animation->state() == QAbstractAnimation::Running)
        d_ptr->animation->stop();
    d_ptr->animation->setStartValue(QVariant::fromValue(d_ptr->currentColor));
    d_ptr->animation->setEndValue(QVariant::fromValue(d_ptr->endColor));
    d_ptr->animation->start();
    QAbstractButton::enterEvent(event);
}

void HColorGradientRoundedButton::leaveEvent(QEvent *event)
{
    if (d_ptr->animation->state() == QAbstractAnimation::Running)
        d_ptr->animation->stop();
    d_ptr->animation->setStartValue(QVariant::fromValue(d_ptr->currentColor));
    d_ptr->animation->setEndValue(QVariant::fromValue(d_ptr->startColor));
    d_ptr->animation->start();
    QAbstractButton::leaveEvent(event);
}

void HColorGradientRoundedButton::init()
{
    qRegisterMetaType<HDoubleColor>("HDoubleColor");
    qRegisterAnimationInterpolator<HDoubleColor>(colorInterpolator);
    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0,0);
    effect->setBlurRadius(25);
    effect->setColor(Qt::black);

    d_ptr->startColor = HDoubleColor(HDrawHelper::randomColor(), HDrawHelper::randomColor());
    d_ptr->endColor = HDoubleColor(HDrawHelper::randomColor(), HDrawHelper::randomColor());
    d_ptr->currentColor = d_ptr->startColor;
    d_ptr->animation = new QPropertyAnimation(this, "currentColor");
    d_ptr->animation->setDuration(400);
    connect(d_ptr->animation, &QPropertyAnimation::valueChanged, this, [=] { update(); });

    setGraphicsEffect(effect);
    setMinimumSize(180,50);
    setMouseTracking(true);
}

HE_END_NAMESPACE
