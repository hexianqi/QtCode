#include "HSplitEffect_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HSplitEffect::HSplitEffect(QObject *parent) :
    HAbstractShaderEffect(*new HSplitEffectPrivate, parent)
{
}

HSplitEffect::HSplitEffect(HSplitEffectPrivate &p, QObject *parent) :
    HAbstractShaderEffect(p, parent)
{
}

void HSplitEffect::initialize(QVariantMap param)
{
    if (param.contains("orientation"))
        setOrientation(param.value("orientation").value<Qt::Orientation>());
    if (param.contains("splitStyle"))
        setSplitStyle(param.value("splitStyle").value<SplitStyle>());
}

QString HSplitEffect::typeName()
{
    return "HSplitEffect";
}

void HSplitEffect::draw(QPainter *painter, double factor, const QRect &rect, const QPixmap &pixmap)
{
    Q_D(HSplitEffect);

    auto w = rect.width();
    auto h = rect.height();
    auto s = ((d->orientation == Qt::Horizontal) ?  pixmap.height() : pixmap.width());
    auto wh = factor * s;
    if (wh < 1)
        return;
    if (d->splitStyle == SplitStyle_OutsideToInside)
    {
        QRectF rect1, rect2;
        double x2, y2;
        auto x1 = (w - pixmap.width()) / 2;
        auto y1 = (h - pixmap.height()) / 2;
        wh = wh / 2;
        if (d->orientation == Qt::Horizontal)
        {
            x2 = x1;
            y2 = (pixmap.height() + h) / 2.0 - wh;
            rect1.setRect(0, 0, pixmap.width(), wh);
            rect2.setRect(0, pixmap.height() - wh, pixmap.width(), wh);
        }
        else
        {
            x2 = (pixmap.width() + w) / 2.0 - wh;
            y2 = y1;
            rect1.setRect(0, 0, wh, pixmap.height());
            rect2.setRect(pixmap.width() - wh, 0, wh, pixmap.height());
        }
        painter->save();
        painter->drawPixmap(QPointF(x1, y1), pixmap, rect1);
        painter->drawPixmap(QPointF(x2, y2), pixmap, rect2);
        painter->restore();
    }
    if (d->splitStyle == SplitStyle_InsideToOutside)
    {
        QPointF point;
        QRectF rect;
        if (d->orientation == Qt::Horizontal)
        {
            point.setX((w - pixmap.width()) / 2.0);
            point.setY((h - wh) / 2);
            rect.setRect(0, (pixmap.height() - wh) / 2 , pixmap.width(), wh);
        }
        else
        {
            point.setX((w - wh) / 2);
            point.setY((h - pixmap.height()) / 2.0);
            rect.setRect((pixmap.width() - wh) / 2, 0, wh, pixmap.height());
        }
        painter->save();
        painter->drawPixmap(point, pixmap, rect);
        painter->restore();
    }
}

Qt::Orientation HSplitEffect::orientation() const
{
    Q_D(const HSplitEffect);
    return d->orientation;
}

HSplitEffect::SplitStyle HSplitEffect::splitStyle() const
{
    Q_D(const HSplitEffect);
    return d->splitStyle;
}

void HSplitEffect::setOrientation(Qt::Orientation value)
{
    Q_D(HSplitEffect);
    if (d->orientation == value)
        return;
    d->orientation = value;
}

void HSplitEffect::setSplitStyle(SplitStyle value)
{
    Q_D(HSplitEffect);
    if (d->splitStyle == value)
        return;
    d->splitStyle = value;
}

HE_END_NAMESPACE
