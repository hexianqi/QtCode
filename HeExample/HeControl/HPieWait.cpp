#include "HPieWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HPieWait::HPieWait(QObject *parent) :
    HAbstractWait(*new HPieWaitPrivate, parent)
{
}

HPieWait::HPieWait(HPieWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HPieWait::~HPieWait()
{
}

void HPieWait::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
    if (param.contains("spanAngle"))
        setSpanAngle(param.value("spanAngle").toInt());
}

QString HPieWait::typeName()
{
    return "HPieWait";
}

void HPieWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HPieWait);
    HAbstractWait::draw(painter, param);
    auto value = param.value("value", 0).toInt();
    auto rect = QRectF(-50, -50, 100, 100);

    painter->rotate(value);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(rect);
    painter->setBrush(d->foreground);
    painter->drawPie(rect, 0, d->spanAngle * 16);
    painter->restore();
}

QColor HPieWait::background() const
{
    Q_D(const HPieWait);
    return d->background;
}

QColor HPieWait::foreground() const
{
    Q_D(const HPieWait);
    return d->foreground;
}

int HPieWait::spanAngle() const
{
    Q_D(const HPieWait);
    return d->spanAngle;
}

void HPieWait::setBackground(const QColor &value)
{
    Q_D(HPieWait);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HPieWait::setForeground(const QColor &value)
{
    Q_D(HPieWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

void HPieWait::setSpanAngle(int value)
{
    Q_D(HPieWait);
    if (d->spanAngle == value)
        return;
    d->spanAngle = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
