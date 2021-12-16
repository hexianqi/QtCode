#include "HInfiniteCircular_p.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HInfiniteCircular::HInfiniteCircular(QObject *parent) :
    HAbstractCircular(*new HInfiniteCircularPrivate, parent)
{
}

HInfiniteCircular::HInfiniteCircular(HInfiniteCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HInfiniteCircular::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HInfiniteCircular::typeName()
{
    return "HInfiniteCircular";
}

void HInfiniteCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HInfiniteCircular);
    HAbstractCircular::draw(painter, factor, param);

    // x * |cos(a)| = 50
    // side = x / sqrt(2) = 50 / sqrt(2) / |cos(a)|
    auto mapAngle = static_cast<int>(factor * 360) % 45; // a mapTo [0, 45]
    auto cosA = qAbs(cos(qDegreesToRadians(mapAngle * 1.0)));
    auto side = 50 / M_SQRT2;
    if (!qFuzzyCompare(cosA, 0))
        side /= cosA;
    auto gradient1 = QLinearGradient(QPointF(0, -side / 2), QPointF(0, side / 2));
    auto gradient2 = QLinearGradient(QPointF(-side / 2, 0), QPointF(side / 2, 0));
    gradient1.setColorAt(0, d->foreground);
    gradient1.setColorAt(1, d->background);
    gradient2.setColorAt(0, d->background);
    gradient2.setColorAt(1, d->foreground);

    painter->rotate(factor * 360);
    painter->save();
    painter->rotate(45);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(gradient1, 5));
    painter->drawLine(QPointF(0, -side / 2), QPointF(0, side / 2));
    painter->setPen(QPen(gradient2, 5));
    painter->drawLine(QPointF(-side / 2, 0), QPointF(side / 2, 0));
    painter->setPen(QPen(d->foreground, 5));
    painter->setBrush(d->foreground);
    painter->drawPie(QRectF(0, -side, side, side), 270*16, 270*16);
    painter->setPen(QPen(d->background, 5));
    painter->setBrush(d->background);
    painter->drawPie(QRectF(-side, 0, side, side), 90*16, 270*16);
    painter->restore();
}

QColor HInfiniteCircular::background() const
{
    Q_D(const HInfiniteCircular);
    return d->background;
}

QColor HInfiniteCircular::foreground() const
{
    Q_D(const HInfiniteCircular);
    return d->foreground;
}

void HInfiniteCircular::setBackground(const QColor &value)
{
    Q_D(HInfiniteCircular);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HInfiniteCircular::setForeground(const QColor &value)
{
    Q_D(HInfiniteCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_END_NAMESPACE
