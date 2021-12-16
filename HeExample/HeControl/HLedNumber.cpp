#include "HLedNumber_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HLedNumber::HLedNumber(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLedNumberPrivate)
{
    init();
}

HLedNumber::HLedNumber(HLedNumberPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLedNumber::~HLedNumber() = default;

QSize HLedNumber::sizeHint() const
{
    return {150, 160};
}

QSize HLedNumber::minimumSizeHint() const
{
    return {10, 10};
}

int HLedNumber::number() const
{
    return d_ptr->number;
}

int HLedNumber::space() const
{
    return d_ptr->space;
}

int HLedNumber::padding() const
{
    return d_ptr->padding;
}

int HLedNumber::radius() const
{
    return d_ptr->radius;
}

QColor HLedNumber::backgroundStart() const
{
    return d_ptr->backgroundStart;
}

QColor HLedNumber::backgroundEnd() const
{
    return d_ptr->backgroundEnd;
}

QColor HLedNumber::numberBackgroundStart() const
{
    return d_ptr->numberBackgroundStart;
}

QColor HLedNumber::numberBackgroundEnd() const
{
    return d_ptr->numberBackgroundEnd;
}

QColor HLedNumber::numberColorStart() const
{
    return d_ptr->numberColorStart;
}

QColor HLedNumber::numberColorEnd() const
{
    return d_ptr->numberColorEnd;
}

void HLedNumber::setNumber(int value)
{
    if (d_ptr->number == value || value < 0 || value > 9)
        return;
    d_ptr->number = value;
    update();
}

void HLedNumber::setSpace(int value)
{
    if (d_ptr->space == value)
        return;
    d_ptr->space = value;
    update();
}

void HLedNumber::setPadding(int value)
{
    if (d_ptr->padding == value)
        return;
    d_ptr->padding = value;
    update();
}

void HLedNumber::setRadius(int value)
{
    if (d_ptr->radius == value)
        return;
    d_ptr->radius = value;
    update();
}

void HLedNumber::setBackgroundStart(const QColor &value)
{
    if (d_ptr->backgroundStart == value)
        return;
    d_ptr->backgroundStart = value;
    update();
}

void HLedNumber::setBackgroundEnd(const QColor &value)
{
    if (d_ptr->backgroundEnd == value)
        return;
    d_ptr->backgroundEnd = value;
    update();
}

void HLedNumber::setNumberBackgroundStart(const QColor &value)
{
    if (d_ptr->numberBackgroundStart == value)
        return;
    d_ptr->numberBackgroundStart = value;
    update();
}

void HLedNumber::setNumberBackgroundEnd(const QColor &value)
{
    if (d_ptr->numberBackgroundEnd == value)
        return;
    d_ptr->numberBackgroundEnd = value;
    update();
}

void HLedNumber::setNumberColorStart(const QColor &value)
{
    if (d_ptr->numberColorStart == value)
        return;
    d_ptr->numberColorStart = value;
    update();
}

void HLedNumber::setNumberColorEnd(const QColor &value)
{
    if (d_ptr->numberColorEnd == value)
        return;
    d_ptr->numberColorEnd = value;
    update();
}

void HLedNumber::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawNumberBackground(&painter);
    drawNumber(&painter);
}

void HLedNumber::drawBackground(QPainter *painter)
{
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, backgroundStart());
    gradient.setColorAt(1.0, backgroundEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
    painter->restore();
}

void HLedNumber::drawNumberBackground(QPainter *painter)
{
    double x, y;
    double w = (width() - 2 * space() - 8 * padding()) / 9.0;
    double h = (height() - 2 * space() - 8 * padding()) / 9.0;
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, numberBackgroundStart());
    gradient.setColorAt(1.0, numberBackgroundEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    for (int i = 0; i < 9; i++)
    {
        x = space() + (w + padding()) * i;
        for (int j = 0; j < 9; j++)
        {
            y = space() + (h + padding()) * j;
            painter->drawRoundedRect(QRectF(x, y, w, h), radius(), radius());
        }
    }
    painter->restore();
}

void HLedNumber::drawNumber(QPainter *painter)
{
    double x, y;
    double w = (width() - 2 * space() - 8 * padding()) / 9.0;
    double h = (height() - 2 * space() - 8 * padding()) / 9.0;
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, numberColorStart());
    gradient.setColorAt(1.0, numberColorEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    for (auto p : d_ptr->position.value(number()))
    {
        x = space() + (w + padding()) * p.x();
        y = space() + (h + padding()) * p.y();
        painter->drawRoundedRect(QRectF(x, y, w, h), radius(), radius());
    }
    painter->restore();
}

void HLedNumber::init()
{
    d_ptr->position.insert(0, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(2, 2)                                                 << QPoint(6, 2)
                           << QPoint(2, 3)                                                 << QPoint(6, 3)
                           << QPoint(2, 4)                                                 << QPoint(6, 4)
                           << QPoint(2, 5)                                                 << QPoint(6, 5)
                           << QPoint(2, 6)                                                 << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(1, QPolygon()                                 << QPoint(4, 1)
                           << QPoint(3, 2) << QPoint(4, 2)
                           << QPoint(4, 3)
                           << QPoint(4, 4)
                           << QPoint(4, 5)
                           << QPoint(4, 6)
                           << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7));

    d_ptr->position.insert(2, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(6, 2)
                           << QPoint(6, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(2, 5)
                           << QPoint(2, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(3, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(6, 2)
                           << QPoint(6, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(6, 5)
                           << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(4, QPolygon()                                 << QPoint(4, 1)
                           << QPoint(3, 2) << QPoint(4, 2)
                           << QPoint(2, 3)                 << QPoint(4, 3)
                           << QPoint(1, 4) << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(4, 5)
                           << QPoint(4, 6)
                           << QPoint(4, 7));

    d_ptr->position.insert(5, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(2, 2)
                           << QPoint(2, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(6, 5)
                           << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(6, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(2, 2)
                           << QPoint(2, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(2, 5)                                                 << QPoint(6, 5)
                           << QPoint(2, 6)                                                 << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(7, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(6, 2)
                           << QPoint(5, 3)
                           << QPoint(4, 4)
                           << QPoint(3, 5)
                           << QPoint(2, 6)
                           << QPoint(2, 7));

    d_ptr->position.insert(8, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(2, 2)                                                 << QPoint(6, 2)
                           << QPoint(2, 3)                                                 << QPoint(6, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(2, 5)                                                 << QPoint(6, 5)
                           << QPoint(2, 6)                                                 << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));

    d_ptr->position.insert(9, QPolygon() << QPoint(2, 1) << QPoint(3, 1) << QPoint(4, 1) << QPoint(5, 1) << QPoint(6, 1)
                           << QPoint(2, 2)                                                 << QPoint(6, 2)
                           << QPoint(2, 3)                                                 << QPoint(6, 3)
                           << QPoint(2, 4) << QPoint(3, 4) << QPoint(4, 4) << QPoint(5, 4) << QPoint(6, 4)
                           << QPoint(6, 5)
                           << QPoint(6, 6)
                           << QPoint(2, 7) << QPoint(3, 7) << QPoint(4, 7) << QPoint(5, 7) << QPoint(6, 7));
}

HE_END_NAMESPACE
