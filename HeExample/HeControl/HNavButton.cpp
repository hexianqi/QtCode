#include "HNavButton_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HNavButton::HNavButton(QWidget *parent) :
    QPushButton(parent),
    d_ptr(new HNavButtonPrivate)
{
}

HNavButton::HNavButton(HNavButtonPrivate &p, QWidget *parent) :
    QPushButton(parent),
    d_ptr(&p)
{
}

HNavButton::~HNavButton()
{
}

int HNavButton::paddingLeft() const
{
    return d_ptr->paddingLeft;
}

int HNavButton::paddingRight() const
{
    return d_ptr->paddingRight;
}

int HNavButton::paddingTop() const
{
    return d_ptr->paddingTop;
}

int HNavButton::paddingBottom() const
{
    return d_ptr->paddingBottom;
}

Qt::Alignment HNavButton::textAlign() const
{
    return d_ptr->textAlign;
}

bool HNavButton::isShowTriangle() const
{
    return d_ptr->showTriangle;
}

int HNavButton::triangleLen() const
{
    return d_ptr->triangleLen;
}

HNavButton::Position HNavButton::trianglePosition() const
{
    return d_ptr->trianglePosition;
}

QColor HNavButton::triangleColor() const
{
    return d_ptr->triangleColor;
}

bool HNavButton::isShowIcon() const
{
    return d_ptr->showIcon;
}

int HNavButton::iconSpace() const
{
    return d_ptr->iconSpace;
}

QSize HNavButton::iconSize() const
{
    return d_ptr->iconSize;
}

QPixmap HNavButton::iconNormal() const
{
    return d_ptr->iconNormal;
}

QPixmap HNavButton::iconHover() const
{
    return d_ptr->iconHover;
}

QPixmap HNavButton::iconCheck() const
{
    return d_ptr->iconCheck;
}

bool HNavButton::isShowLine() const
{
    return d_ptr->showLine;
}

int HNavButton::lineSpace() const
{
    return d_ptr->lineSpace;
}

int HNavButton::lineWidth() const
{
    return d_ptr->lineWidth;
}

HNavButton::Position HNavButton::linePosition() const
{
    return d_ptr->linePosition;
}

QColor HNavButton::lineColor() const
{
    return d_ptr->lineColor;
}

QColor HNavButton::bormalBackground() const
{
    return d_ptr->normalBackground;
}

QColor HNavButton::hoverBackground() const
{
    return d_ptr->hoverBackground;
}

QColor HNavButton::checkBackground() const
{
    return d_ptr->checkBackground;
}

QColor HNavButton::normalTextColor() const
{
    return d_ptr->normalTextColor;
}

QColor HNavButton::hoverTextColor() const
{
    return d_ptr->hoverTextColor;
}

QColor HNavButton::checkTextColor() const
{
    return d_ptr->checkTextColor;
}

void HNavButton::setPadding(int value)
{
    d_ptr->paddingLeft = value;
    d_ptr->paddingRight = value;
    d_ptr->paddingTop = value;
    d_ptr->paddingBottom = value;
    update();
}

void HNavButton::setPadding(int left, int right, int top, int bottom)
{
    d_ptr->paddingLeft = left;
    d_ptr->paddingRight = right;
    d_ptr->paddingTop = top;
    d_ptr->paddingBottom = bottom;
    update();
}

void HNavButton::setPaddingLeft(int value)
{
    if (d_ptr->paddingLeft == value)
        return;
    d_ptr->paddingLeft = value;
    update();
}

void HNavButton::setPaddingRight(int value)
{
    if (d_ptr->paddingRight == value)
        return;
    d_ptr->paddingRight = value;
    update();
}

void HNavButton::setPaddingTop(int value)
{
    if (d_ptr->paddingTop == value)
        return;
    d_ptr->paddingTop = value;
    update();
}

void HNavButton::setPaddingBottom(int value)
{
    if (d_ptr->paddingBottom == value)
        return;
    d_ptr->paddingBottom = value;
    update();
}

void HNavButton::setTextAlign(Qt::Alignment value)
{
    if (d_ptr->textAlign == value)
        return;
    d_ptr->textAlign = value;
    update();
}

void HNavButton::setShowTriangle(bool b)
{
    if (d_ptr->showTriangle == b)
        return;
    d_ptr->showTriangle = b;
    update();
}

void HNavButton::setTriangleLen(int value)
{
    if (d_ptr->triangleLen == value)
        return;
    d_ptr->triangleLen = value;
    update();
}

void HNavButton::setTrianglePosition(Position value)
{
    if (d_ptr->trianglePosition == value)
        return;
    d_ptr->trianglePosition = value;
    update();
}

void HNavButton::setTriangleColor(const QColor &value)
{
    if (d_ptr->triangleColor == value)
        return;
    d_ptr->triangleColor = value;
    update();
}

void HNavButton::setShowIcon(bool b)
{
    if (d_ptr->showIcon == b)
        return;
    d_ptr->showIcon = b;
    update();
}

void HNavButton::setIconSpace(int value)
{
    if (d_ptr->iconSpace == value)
        return;
    d_ptr->iconSpace = value;
    update();
}

void HNavButton::setIconSize(QSize value)
{
    if (d_ptr->iconSize == value)
        return;
    d_ptr->iconSize = value;
    update();
}

void HNavButton::setIconNormal(QPixmap value)
{
    if (d_ptr->iconNormal == value)
        return;
    d_ptr->iconNormal = value;
    update();
}

void HNavButton::setIconHover(QPixmap value)
{
    if (d_ptr->iconHover == value)
        return;
    d_ptr->iconHover = value;
    update();
}

void HNavButton::setIconCheck(QPixmap value)
{
    if (d_ptr->iconCheck == value)
        return;
    d_ptr->iconCheck = value;
    update();
}

void HNavButton::setShowLine(bool b)
{
    if (d_ptr->showLine == b)
        return;
    d_ptr->showLine = b;
    update();
}

void HNavButton::setLineSpace(int value)
{
    if (d_ptr->lineSpace == value)
        return;
    d_ptr->lineSpace = value;
    update();
}

void HNavButton::setLineWidth(int value)
{
    if (d_ptr->lineWidth == value)
        return;
    d_ptr->lineWidth = value;
    update();
}

void HNavButton::setLinePosition(Position value)
{
    if (d_ptr->linePosition == value)
        return;
    d_ptr->linePosition = value;
    update();
}

void HNavButton::setLineColor(const QColor &value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
    update();
}

void HNavButton::setNormalBackground(const QColor &value)
{
    if (d_ptr->normalBackground == value)
        return;
    d_ptr->normalBackground = value;
    update();
}

void HNavButton::setHoverBackground(const QColor &value)
{
    if (d_ptr->hoverBackground == value)
        return;
    d_ptr->hoverBackground = value;
    update();
}

void HNavButton::setCheckBackground(const QColor &value)
{
    if (d_ptr->checkBackground == value)
        return;
    d_ptr->checkBackground = value;
    update();
}

void HNavButton::setNormalTextColor(const QColor &value)
{
    if (d_ptr->normalTextColor == value)
        return;
    d_ptr->normalTextColor = value;
    update();
}

void HNavButton::setHoverTextColor(const QColor &value)
{
    if (d_ptr->hoverTextColor == value)
        return;
    d_ptr->hoverTextColor = value;
    update();
}

void HNavButton::setCheckTextColor(const QColor &value)
{
    if (d_ptr->checkTextColor == value)
        return;
    d_ptr->checkTextColor = value;
    update();
}

void HNavButton::setNormalBackgroundBrush(const QBrush &value)
{
    if (d_ptr->normalBackgroundBrush == value)
        return;
    d_ptr->normalBackgroundBrush = value;
    update();
}

void HNavButton::setHoverBackgroundBrush(const QBrush &value)
{
    if (d_ptr->hoverBackgroundBrush == value)
        return;
    d_ptr->hoverBackgroundBrush = value;
    update();
}

void HNavButton::setCheckBackgroundBrush(const QBrush &value)
{
    if (d_ptr->checkBackgroundBrush == value)
        return;
    d_ptr->checkBackgroundBrush = value;
    update();
}

void HNavButton::enterEvent(QEvent *)
{
    if (d_ptr->hover)
        return;
    d_ptr->hover = true;
}

void HNavButton::leaveEvent(QEvent *)
{
    if (!d_ptr->hover)
        return;
    d_ptr->hover = false;
}

void HNavButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 绘制背景
    drawBackground(&painter);
    // 绘制文字
    drawText(&painter);
    // 绘制图标
    drawIcon(&painter);
    // 绘制边框线条
    drawLine(&painter);
    // 绘制倒三角
    drawTriangle(&painter);
}

void HNavButton::drawBackground(QPainter *painter)
{
    QRect rect;
    QBrush brush;
    QColor color;
    if (d_ptr->linePosition == Position_Left)
        rect = this->rect().adjusted(d_ptr->lineSpace, 0, 0, 0);
    else if (d_ptr->linePosition == Position_Right)
        rect = this->rect().adjusted(0, 0, -d_ptr->lineSpace, 0);
    else if (d_ptr->linePosition == Position_Top)
        rect = this->rect().adjusted(0, d_ptr->lineSpace, 0, 0);
    else if (d_ptr->linePosition == Position_Bottom)
        rect = this->rect().adjusted(0, 0, 0, -d_ptr->lineSpace);
    if (isChecked())
    {
        brush = d_ptr->checkBackgroundBrush;
        color = d_ptr->checkBackground;
    }
    else if (d_ptr->hover)
    {
        brush = d_ptr->hoverBackgroundBrush;
        color = d_ptr->hoverBackground;
    }
    else
    {
        brush = d_ptr->normalBackgroundBrush;
        color = d_ptr->normalBackground;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush != Qt::NoBrush ? brush : color);
    painter->drawRect(rect);
    painter->restore();
}

void HNavButton::drawText(QPainter *painter)
{
    QColor color;
    if (isChecked())
        color = d_ptr->checkTextColor;
    else if (d_ptr->hover)
        color = d_ptr->hoverTextColor;
    else
        color = d_ptr->normalTextColor;

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(color);
    painter->drawText(d_ptr->paddingLeft, d_ptr->paddingTop, width() - d_ptr->paddingLeft - d_ptr->paddingRight, height() - d_ptr->paddingTop - d_ptr->paddingBottom, QFlag(d_ptr->textAlign), text());
    painter->restore();
}

void HNavButton::drawIcon(QPainter *painter)
{
    if (!d_ptr->showIcon)
        return;
    QPixmap pixmap;
    if (isChecked())
        pixmap = d_ptr->iconCheck;
    else if (d_ptr->hover)
        pixmap = d_ptr->iconHover;
    else
        pixmap = d_ptr->iconNormal;
    if (pixmap.isNull())
        return;
    pixmap = pixmap.scaled(d_ptr->iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->save();
    painter->drawPixmap(d_ptr->iconSpace, (height() - d_ptr->iconSize.height()) / 2, pixmap);
    painter->restore();
}

void HNavButton::drawLine(QPainter *painter)
{
    if (!d_ptr->showLine || !isChecked())
        return;

    QPoint start, end;
    if (d_ptr->linePosition == Position_Left)
    {
        start = QPoint(0, 0);
        end = QPoint(0, height());
    }
    else if (d_ptr->linePosition == Position_Right)
    {
        start = QPoint(width(), 0);
        end = QPoint(width(), height());
    }
    else if (d_ptr->linePosition == Position_Top)
    {
        start = QPoint(0, 0);
        end = QPoint(width(), 0);
    }
    else if (d_ptr->linePosition == Position_Bottom)
    {
        start = QPoint(0, height());
        end = QPoint(width(), height());
    }

    painter->save();
    painter->setPen(QPen(d_ptr->lineColor, d_ptr->lineWidth));
    painter->drawLine(start, end);
    painter->restore();
}

void HNavButton::drawTriangle(QPainter *painter)
{
    if (!d_ptr->showTriangle || (!d_ptr->hover && !isChecked()))
        return;

    int x = width() / 2;
    int y = height() / 2;
    QPolygon poly;
    if (d_ptr->trianglePosition == Position_Left)
        poly.setPoints(3, d_ptr->triangleLen, y, 0, y - d_ptr->triangleLen, 0, y + d_ptr->triangleLen);
    else if (d_ptr->trianglePosition == Position_Right)
        poly.setPoints(3, width() - d_ptr->triangleLen, y, width(), y - d_ptr->triangleLen, width(), y + d_ptr->triangleLen);
    else if (d_ptr->trianglePosition == Position_Top)
        poly.setPoints(3, x, d_ptr->triangleLen, x - d_ptr->triangleLen, 0, x + d_ptr->triangleLen, 0);
    else if (d_ptr->trianglePosition == Position_Bottom)
        poly.setPoints(3, x, height() - d_ptr->triangleLen, x - d_ptr->triangleLen, height(), x + d_ptr->triangleLen, height());

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->triangleColor);
    painter->drawPolygon(poly);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
