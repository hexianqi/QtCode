#include "HNavLabel_p.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HNavLabel::HNavLabel(QWidget *parent) :
    QLabel(parent),
    d_ptr(new HNavLabelPrivate)
{
}

HNavLabel::HNavLabel(HNavLabelPrivate &p, QWidget *parent) :
    QLabel(parent),
    d_ptr(&p)
{
}

HNavLabel::~HNavLabel() = default;

QSize HNavLabel::sizeHint() const
{
    return {100, 25};
}

QSize HNavLabel::minimumSizeHint() const
{
    return {20, 5};
}

int HNavLabel::borderRadius() const
{
    return d_ptr->borderRadius;
}

QColor HNavLabel::background() const
{
    return d_ptr->background;
}

QColor HNavLabel::foreground() const
{
    return d_ptr->foreground;
}

bool HNavLabel::isShowArrow() const
{
    return d_ptr->showArrow;
}

int HNavLabel::arrowSize() const
{
    return d_ptr->arrowSize;
}

HControlType::Position HNavLabel::arrowPosition() const
{
    return d_ptr->arrowPosition;
}

bool HNavLabel::isShowTriangle() const
{
    return d_ptr->showTriangle;
}

int HNavLabel::triangleSize() const
{
    return d_ptr->triangleSize;
}

HControlType::Position HNavLabel::trianglePosition() const
{
    return d_ptr->trianglePosition;
}

QColor HNavLabel::triangleColor() const
{
    return d_ptr->triangleColor;
}

void HNavLabel::setBorderRadius(int value)
{
    if (d_ptr->borderRadius == value)
        return;
    d_ptr->borderRadius = value;
    update();
}

void HNavLabel::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HNavLabel::setForeground(const QColor &value)
{
    if (d_ptr->foreground == value)
        return;
    d_ptr->foreground = value;
    update();
}

void HNavLabel::setShowArrow(bool b)
{
    if (d_ptr->showArrow == b)
        return;
    d_ptr->showArrow = b;
    update();
}

void HNavLabel::setArrowSize(int value)
{
    if (d_ptr->arrowSize == value)
        return;
    d_ptr->arrowSize = value;
    update();
}

void HNavLabel::setArrowPosition(HControlType::Position value)
{
    if (d_ptr->arrowPosition == value)
        return;
    d_ptr->arrowPosition = value;
    update();
}

void HNavLabel::setShowTriangle(bool b)
{
    if (d_ptr->showTriangle == b)
        return;
    d_ptr->showTriangle = b;
    update();
}

void HNavLabel::setTriangleSize(int value)
{
    if (d_ptr->triangleSize == value)
        return;
    d_ptr->triangleSize = value;
    update();
}

void HNavLabel::setTrianglePosition(HControlType::Position value)
{
    if (d_ptr->trianglePosition == value)
        return;
    d_ptr->trianglePosition = value;
    update();
}

void HNavLabel::setTriangleColor(const QColor &value)
{
    if (d_ptr->triangleColor == value)
        return;
    d_ptr->triangleColor = value;
    update();
}

void HNavLabel::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        emit clicked();
    return QLabel::mousePressEvent(e);
}

void HNavLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawText(&painter);
    drawTriangle(&painter);
}

void HNavLabel::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->background);
    if (d_ptr->showArrow)
    {
        int width = this->width();
        int height = this->height();
        int endX = width - d_ptr->arrowSize;
        int endY = height - d_ptr->arrowSize;
        QPolygon poly;
        if (d_ptr->arrowPosition == HControlType::Position_Right)
        {
            d_ptr->plotArea = QRect(0, 0, endX, height);
            poly.setPoints(3, endX, height / 2 - d_ptr->arrowSize, endX, height / 2 + d_ptr->arrowSize, width, height / 2);
        }
        else if (d_ptr->arrowPosition == HControlType::Position_Left)
        {
            d_ptr->plotArea = QRect(d_ptr->arrowSize, 0, endX, height);
            poly.setPoints(3, d_ptr->arrowSize, height / 2 - d_ptr->arrowSize, d_ptr->arrowSize, height / 2 + d_ptr->arrowSize, 0, height / 2);
        }
        else if (d_ptr->arrowPosition == HControlType::Position_Bottom)
        {
            d_ptr->plotArea = QRect(0, 0, width, endY);
            poly.setPoints(3, width / 2 - d_ptr->arrowSize, endY, width / 2 + d_ptr->arrowSize, endY, width / 2, height);
        }
        else if (d_ptr->arrowPosition == HControlType::Position_Top)
        {
            d_ptr->plotArea = QRect(0, d_ptr->arrowSize, width, endY);
            poly.setPoints(3, width / 2 - d_ptr->arrowSize, d_ptr->arrowSize, width / 2 + d_ptr->arrowSize, d_ptr->arrowSize, width / 2, 0);
        }
        painter->drawRoundedRect(d_ptr->plotArea, d_ptr->borderRadius, d_ptr->borderRadius);
        painter->drawPolygon(poly);
    }
    else
    {
        d_ptr->plotArea = rect();
        painter->drawRoundedRect(d_ptr->plotArea, d_ptr->borderRadius, d_ptr->borderRadius);
    }
    painter->restore();
}

void HNavLabel::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(d_ptr->foreground);
    painter->setBrush(Qt::NoBrush);
    painter->drawText(d_ptr->plotArea, Qt::AlignCenter, this->text());
    painter->restore();
}

void HNavLabel::drawTriangle(QPainter *painter)
{
    if (!d_ptr->showTriangle)
        return;

    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;
    QPolygon pts;
    if (d_ptr->trianglePosition == HControlType::Position_Left)
        pts.setPoints(3, d_ptr->triangleSize, midHeight, 0, midHeight - d_ptr->triangleSize, 0, midHeight + d_ptr->triangleSize);
    else if (d_ptr->trianglePosition == HControlType::Position_Right)
        pts.setPoints(3, width - d_ptr->triangleSize, midHeight, width, midHeight - d_ptr->triangleSize, width, midHeight + d_ptr->triangleSize);
    else if (d_ptr->trianglePosition == HControlType::Position_Top)
        pts.setPoints(3, midWidth, d_ptr->triangleSize, midWidth - d_ptr->triangleSize, 0, midWidth + d_ptr->triangleSize, 0);
    else if (d_ptr->trianglePosition == HControlType::Position_Bottom)
        pts.setPoints(3, midWidth, height - d_ptr->triangleSize, midWidth - d_ptr->triangleSize, height, midWidth + d_ptr->triangleSize, height);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->triangleColor);
    painter->drawPolygon(pts);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
