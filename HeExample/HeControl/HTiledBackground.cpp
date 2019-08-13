#include "HTiledBackground_p.h"
#include "HDrawHelper.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HTiledBackground::HTiledBackground(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTiledBackgroundPrivate)
{
}

HTiledBackground::HTiledBackground(HTiledBackgroundPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HTiledBackground::~HTiledBackground()
{
}

QSize HTiledBackground::sizeHint() const
{
    return QSize(100, 100);
}

QSize HTiledBackground::minimumSizeHint() const
{
    return QSize(20, 20);
}

QColor HTiledBackground::color1() const
{
    return d_ptr->color1;
}

QColor HTiledBackground::color2() const
{
    return d_ptr->color2;
}

int HTiledBackground::size() const
{
    return d_ptr->size;
}


QPixmap HTiledBackground::pixmap() const
{
    return d_ptr->pixmap;
}

void HTiledBackground::setColor1(const QColor &value)
{
    if (d_ptr->color1 == value)
        return;
    d_ptr->color1 = value;
    update();
}

void HTiledBackground::setColor2(const QColor &value)
{
    if (d_ptr->color2 == value)
        return;
    d_ptr->color2 = value;
    update();
}

void HTiledBackground::setSize(int value)
{
    if (d_ptr->size == value)
        return;
    d_ptr->size = value;
    update();
}

void HTiledBackground::setPixmap(const QPixmap &value)
{
    if (d_ptr->pixmap == value)
        return;
    d_ptr->pixmap = value;
    update();
}

void HTiledBackground::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto pixmap = d_ptr->pixmap.isNull() ? QPixmap::fromImage(HDrawHelper::createTiledImage(d_ptr->color1, d_ptr->color2, d_ptr->size)) : d_ptr->pixmap;
    painter.drawTiledPixmap(rect(), pixmap);
}

HE_CONTROL_END_NAMESPACE
