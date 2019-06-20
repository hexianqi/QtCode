#include "HDonutWait_p.h"
#include <QtGui/QPalette>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HDonutWait::HDonutWait(QObject *parent) :
    HAbstractWait(*new HDonutWaitPrivate, parent)
{
}

HDonutWait::HDonutWait(HDonutWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HDonutWait::~HDonutWait()
{
}

void HDonutWait::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
    if (param.contains("spanAngle"))
        setSpanAngle(param.value("spanAngle").toInt());
}

QString HDonutWait::typeName()
{
    return "HDonutWait";
}

void HDonutWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HDonutWait);
    HAbstractWait::draw(painter, param);
    auto value = param.value("value", 0).toInt();
    auto palette = param.value("palette").value<QPalette>();
    auto rectOut = QRectF(-50, -50, 100, 100);
    auto rectIn = QRectF(-30, -30, 60, 60);
    auto text = QString("%1%").arg(qAbs(value / 3.6), 0, 'f', 0);
    auto font = painter->font();
    font.setBold(true);

    painter->rotate(value);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(rectOut);
    painter->setBrush(d->foreground);
    painter->drawPie(rectOut, 0, d->spanAngle * 16);
    painter->setBrush(palette.window().color());
    painter->drawEllipse(rectIn);
    painter->rotate(-value);
    painter->setFont(font);
    painter->setPen(d->foreground);
    painter->drawText(rectIn, Qt::AlignCenter, text);
    painter->restore();
}

QColor HDonutWait::background() const
{
    Q_D(const HDonutWait);
    return d->background;
}

QColor HDonutWait::foreground() const
{
    Q_D(const HDonutWait);
    return d->foreground;
}

int HDonutWait::spanAngle() const
{
    Q_D(const HDonutWait);
    return d->spanAngle;
}

void HDonutWait::setBackground(const QColor &value)
{
    Q_D(HDonutWait);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HDonutWait::setForeground(const QColor &value)
{
    Q_D(HDonutWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

void HDonutWait::setSpanAngle(int value)
{
    Q_D(HDonutWait);
    if (d->spanAngle == value)
        return;
    d->spanAngle = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
