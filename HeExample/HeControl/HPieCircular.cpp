#include "HPieCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HPieCircular::HPieCircular(QObject *parent) :
    HAbstractCircular(*new HPieCircularPrivate, parent)
{
}

HPieCircular::HPieCircular(HPieCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

HPieCircular::~HPieCircular()
{
}

void HPieCircular::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
    if (param.contains("spanAngle"))
        setSpanAngle(param.value("spanAngle").toInt());
}

QString HPieCircular::typeName()
{
    return "HPieCircular";
}

void HPieCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HPieCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto rect = QRectF(-50, -50, 100, 100);

    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(rect);
    painter->setBrush(d->foreground);
    painter->drawPie(rect, 0, d->spanAngle * 16);
    painter->restore();
}

QColor HPieCircular::background() const
{
    Q_D(const HPieCircular);
    return d->background;
}

QColor HPieCircular::foreground() const
{
    Q_D(const HPieCircular);
    return d->foreground;
}

int HPieCircular::spanAngle() const
{
    Q_D(const HPieCircular);
    return d->spanAngle;
}

void HPieCircular::setBackground(const QColor &value)
{
    Q_D(HPieCircular);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HPieCircular::setForeground(const QColor &value)
{
    Q_D(HPieCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

void HPieCircular::setSpanAngle(int value)
{
    Q_D(HPieCircular);
    if (d->spanAngle == value)
        return;
    d->spanAngle = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
