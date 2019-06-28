#include "HSlideNavigation_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HSlideNavigation::HSlideNavigation(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HSlideNavigationPrivate)
{
    init();
}

HSlideNavigation::HSlideNavigation(HSlideNavigationPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HSlideNavigation::~HSlideNavigation()
{
}

QStringList HSlideNavigation::items() const
{
    QStringList list;
    for (auto v : d_ptr->items)
        list << v.first;
    return list;
}

int HSlideNavigation::currentIndex() const
{
    return d_ptr->currentIndex;
}

bool HSlideNavigation::isKeyMoveEnable() const
{
    return  d_ptr->keyMoveEnable;
}

Qt::Orientation HSlideNavigation::orientation() const
{
    return d_ptr->orientation;
}

bool HSlideNavigation::isFixed() const
{
    return d_ptr->fixed;
}

int HSlideNavigation::space() const
{
    return d_ptr->space;
}

int HSlideNavigation::barRadious() const
{
    return d_ptr->barRadious;
}

QColor HSlideNavigation::barBackgroundStart() const
{
    return d_ptr->barBackgroundStart;
}

QColor HSlideNavigation::barBackgroundEnd() const
{
    return d_ptr->barBackgroundEnd;
}

int HSlideNavigation::itemRadious() const
{
    return d_ptr->itemRadious;
}

QColor HSlideNavigation::itemBackgroundStart() const
{
    return d_ptr->itemBackgroundStart;
}

QColor HSlideNavigation::itemBackgroundEnd() const
{
    return d_ptr->itemBackgroundEnd;
}

QColor HSlideNavigation::itemTextColor() const
{
    return d_ptr->itemTextColor;
}

HSlideNavigation::ItemLineStyle HSlideNavigation::itemLineStyle() const
{
    return d_ptr->itemLineStyle;
}

int HSlideNavigation::itemLineWidth() const
{
    return d_ptr->itemLineWidth;
}

QColor HSlideNavigation::itemLineColor() const
{
    return d_ptr->itemLineColor;
}

void HSlideNavigation::addItem(QString value)
{
    if(value.isEmpty())
        return;

    for (auto it : d_ptr->items)
    {
        if (it.first == value)
            return;
    }

    auto fm = QFontMetrics(font());
    auto width = fm.width(value);
    auto height = fm.height();
    auto count = d_ptr->items.size();
    auto p = QPointF(0, 0);

    if (d_ptr->orientation == Qt::Horizontal)
    {
        if (count > 0)
            p.setX(d_ptr->totalTextWidth);
        else
            d_ptr->totalTextHeight = height + d_ptr->space;
        d_ptr->totalTextWidth += width + d_ptr->space;
    }
    else
    {
        if (count > 0)
            p.setY(d_ptr->totalTextHeight);
        else
            d_ptr->totalTextWidth += width + d_ptr->space * 2;
        d_ptr->totalTextHeight += height + d_ptr->space;
    }
    d_ptr->items.insert(count, qMakePair(value, QRectF(p, QPointF(d_ptr->totalTextWidth, d_ptr->totalTextHeight))));

    if (d_ptr->fixed)
    {
        if (d_ptr->orientation == Qt::Horizontal)
            setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        else
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    }
    setMinimumSize(d_ptr->totalTextWidth, d_ptr->totalTextHeight);
    update();
}

void HSlideNavigation::addItem(QStringList value)
{
    for (auto v : value)
        addItem(v);
}

void HSlideNavigation::setCurrentIndex(int value)
{
    moveTo(value);
}

void HSlideNavigation::setKeyMoveEnable(bool b)
{
    if (d_ptr->keyMoveEnable == b)
        return;
    d_ptr->keyMoveEnable = b;
}

void HSlideNavigation::setOrientation(Qt::Orientation value)
{
    if (d_ptr->orientation == value)
        return;
    d_ptr->orientation = value;
    update();
}

void HSlideNavigation::setFixed(bool b)
{
    if (d_ptr->fixed == b)
        return;
    d_ptr->fixed = b;
    update();
}

void HSlideNavigation::setSpace(int value)
{
    if (d_ptr->space == value)
        return;
    d_ptr->space = value;
    update();
}

void HSlideNavigation::setBarRadious(int value)
{
    if (d_ptr->barRadious == value)
        return;
    d_ptr->barRadious = value;
    update();
}

void HSlideNavigation::setBarBackgroundStart(const QColor &value)
{
    if (d_ptr->barBackgroundStart == value)
        return;
    d_ptr->barBackgroundStart = value;
    update();
}

void HSlideNavigation::setBarBackgroundEnd(const QColor &value)
{
    if (d_ptr->barBackgroundEnd == value)
        return;
    d_ptr->barBackgroundEnd = value;
    update();
}

void HSlideNavigation::setItemRadious(int value)
{
    if (d_ptr->itemRadious == value)
        return;
    d_ptr->itemRadious = value;
    update();
}

void HSlideNavigation::setItemBackgroundStart(const QColor &value)
{
    if (d_ptr->itemBackgroundStart == value)
        return;
    d_ptr->itemBackgroundStart = value;
    update();
}

void HSlideNavigation::setItemBackgroundEnd(const QColor &value)
{
    if (d_ptr->itemBackgroundEnd == value)
        return;
    d_ptr->itemBackgroundEnd = value;
    update();
}

void HSlideNavigation::setItemTextColor(const QColor &value)
{
    if (d_ptr->itemTextColor == value)
        return;
    d_ptr->itemTextColor = value;
    update();
}

void HSlideNavigation::setItemLineStyle(ItemLineStyle value)
{
    if (d_ptr->itemLineStyle == value)
        return;
    d_ptr->itemLineStyle = value;
    update();
}

void HSlideNavigation::setItemLineWidth(int value)
{
    if (d_ptr->itemLineWidth == value)
        return;
    d_ptr->itemLineWidth = value;
    update();
}

void HSlideNavigation::setItemLineColor(const QColor &value)
{
    if (d_ptr->itemLineColor == value)
        return;
    d_ptr->itemLineColor = value;
    update();
}

void HSlideNavigation::moveToFirst()
{
    moveTo(0);
}

void HSlideNavigation::moveToLast()
{
    moveTo(d_ptr->items.size() - 1);
}

void HSlideNavigation::moveToPrevious()
{
    moveTo(d_ptr->currentIndex - 1);
}

void HSlideNavigation::moveToNext()
{
    moveTo(d_ptr->currentIndex + 1);
}

void HSlideNavigation::moveTo(int value)
{
    if (value < 0 || value >= d_ptr->items.size())
        return;

    emit itemClicked(value, d_ptr->items[value].first);
    if (value == d_ptr->currentIndex)
        return;

    if(d_ptr->currentIndex == -1)
        d_ptr->rectStart = d_ptr->items[value].second;
    d_ptr->forward = value > d_ptr->currentIndex;
    d_ptr->currentIndex = value;
    d_ptr->rectEnd = d_ptr->items[value].second;
    d_ptr->slide->start();

}

void HSlideNavigation::moveTo(QString value)
{
    for (auto it = d_ptr->items.begin(); it != d_ptr->items.end(); it++)
    {
        if (it.value().first == value)
        {
            moveTo(it.key());
            break;
        }
    }
}

void HSlideNavigation::moveTo(QPointF value)
{
    for (auto it = d_ptr->items.begin(); it != d_ptr->items.end(); it++)
    {
        if (it.value().second.contains(value))
        {
            moveTo(it.key());
            break;
        }
    }
}

void HSlideNavigation::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    drawBarBackground(&painter);
    drawItemBackground(&painter);
    drawItemLine(&painter);
    drawText(&painter);
}

void HSlideNavigation::resizeEvent(QResizeEvent *)
{
    adjuseItemSize();
}

void HSlideNavigation::mousePressEvent(QMouseEvent *event)
{
    moveTo(event->pos());
}

void HSlideNavigation::keyPressEvent(QKeyEvent *event)
{
    if (!d_ptr->keyMoveEnable)
    {
        QWidget::keyPressEvent(event);
        return;
    }
    switch (event->key())
    {
    case Qt::Key_Home:
        moveToFirst();
        break;
    case Qt::Key_End:
        moveToLast();
        break;
    case Qt::Key_Up:
    case Qt::Key_Left:
        moveToPrevious();
        break;
    case Qt::Key_Down:
    case Qt::Key_Right:
        moveToNext();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void HSlideNavigation::drawBarBackground(QPainter *painter)
{
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, d_ptr->barBackgroundStart);
    gradient.setColorAt(1.0, d_ptr->barBackgroundEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRoundedRect(rect(), d_ptr->barRadious, d_ptr->barRadious);
    painter->restore();
}

void HSlideNavigation::drawItemBackground(QPainter *painter)
{
    if (d_ptr->rectStart.isNull())
        return;

    auto gradient = QLinearGradient(d_ptr->rectStart.topLeft(), d_ptr->rectStart.bottomRight());
    gradient.setColorAt(0.0, d_ptr->itemBackgroundStart);
    gradient.setColorAt(1.0, d_ptr->itemBackgroundEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRoundedRect(d_ptr->rectStart, d_ptr->itemRadious, d_ptr->itemRadious);
    painter->restore();
}

void HSlideNavigation::drawItemLine(QPainter *painter)
{
    if (d_ptr->rectStart.isNull() || d_ptr->itemLineStyle == None)
        return;

    QPointF p1,p2;
    switch(d_ptr->itemLineStyle)
    {
    case ItemTop:
        p1 = d_ptr->rectStart.topLeft();
        p2 = d_ptr->rectStart.topRight();
        break;
    case ItemRight:
        p1 = d_ptr->rectStart.topRight();
        p2 = d_ptr->rectStart.bottomRight();
        break;
    case ItemBottom:
        p1 = d_ptr->rectStart.bottomLeft();
        p2 = d_ptr->rectStart.bottomRight();
        break;
    case ItemLeft:
        p1 = d_ptr->rectStart.topLeft();
        p2 = d_ptr->rectStart.bottomLeft();
        break;
    case ItemRect:
        break;
    default:
        return;
    }
    QPen pen;
    pen.setColor(d_ptr->itemLineColor);
    pen.setWidth(d_ptr->itemLineWidth);
    painter->save();
    painter->setPen(pen);
    if(d_ptr->itemLineStyle == ItemRect)
        painter->drawRoundedRect(d_ptr->rectStart, d_ptr->itemRadious, d_ptr->itemRadious);
    else
        painter->drawLine(p1, p2);
    painter->restore();
}

void HSlideNavigation::drawText(QPainter *painter)
{
    painter->save();
    painter->setPen(d_ptr->itemTextColor);
    for (auto v : d_ptr->items)
        painter->drawText(v.second, Qt::AlignCenter, v.first);
    painter->restore();
}

void HSlideNavigation::adjuseItemSize()
{
    if (d_ptr->fixed)
        return;
    auto fm = QFontMetrics(font());
    auto addWidth = (width() - d_ptr->totalTextWidth) / (d_ptr->orientation == Qt::Horizontal ? d_ptr->items.size() : 1.0);
    auto addHeight = (height() - d_ptr->totalTextHeight) / (d_ptr->orientation != Qt::Horizontal ? d_ptr->items.size() : 1.0);

    auto dx = 0.0;
    auto dy = 0.0;
    for (auto it = d_ptr->items.begin(); it != d_ptr->items.end(); it++)
    {
        auto p = QPointF(0, 0);
        auto textWidth = fm.width(it.value().first);
        auto textHeight = fm.height();
        if (d_ptr->orientation == Qt::Horizontal)
        {
            p.setX(dx);
            dx += textWidth + d_ptr->space + addWidth;
            dy = d_ptr->totalTextHeight + addHeight;
        }
        else
        {
            p.setY(dy);
            dx = d_ptr->totalTextWidth + addWidth;
            dy += textHeight + d_ptr->space + addHeight;
        }
        auto rect = QRectF(p, QPointF(dx, dy));
        it.value().second = rect;
        if (it.key() == d_ptr->currentIndex)
        {
            d_ptr->rectStart = rect;
            d_ptr->rectEnd = rect;
        }
    }
    update();
}

void HSlideNavigation::doSlide()
{
    if (d_ptr->space <= 0 ||  d_ptr->rectStart == d_ptr->rectEnd)
        return;

    auto dx = d_ptr->orientation == Qt::Horizontal ? d_ptr->space / 2.0 : 0;
    auto dy = d_ptr->orientation != Qt::Horizontal ? d_ptr->space / 2.0 : 0;
    if (d_ptr->forward)
    {
        d_ptr->rectStart.adjust(dx, dy, dx, dy);
        if ((d_ptr->orientation == Qt::Horizontal && d_ptr->rectStart.left() >= d_ptr->rectEnd.left()) ||
            (d_ptr->orientation == Qt::Vertical && d_ptr->rectStart.top() >= d_ptr->rectEnd.top()))
        {
            d_ptr->slide->stop();
            if(d_ptr->rectStart != d_ptr->rectEnd)
                d_ptr->shake->start();
        }
    }
    else
    {
        d_ptr->rectStart.adjust(-dx, -dy, -dx, -dy);
        if ((d_ptr->orientation == Qt::Horizontal && d_ptr->rectStart.left() <= d_ptr->rectEnd.left()) ||
            (d_ptr->orientation == Qt::Vertical && d_ptr->rectStart.top() <= d_ptr->rectEnd.top()))
        {
            d_ptr->slide->stop();
            if(d_ptr->rectStart != d_ptr->rectEnd)
                d_ptr->shake->start();
        }
    }
    update();
}

void HSlideNavigation::doShake()
{
    auto delta = 2.0;
    auto dx1 = 0.0;
    auto dy1 = 0.0;
    auto dx2 = 0.0;
    auto dy2 = 0.0;

    if (d_ptr->rectStart.left() > d_ptr->rectEnd.left())
        dx1 = -delta;
    else if (d_ptr->rectStart.left() < d_ptr->rectEnd.left())
        dx1 = delta;
    if (d_ptr->rectStart.top() > d_ptr->rectEnd.top())
        dy1 = -delta;
    else if (d_ptr->rectStart.top() < d_ptr->rectEnd.top())
        dy1 = delta;
    if (d_ptr->rectStart.right() > d_ptr->rectEnd.right())
        dx2 = -delta;
    else if (d_ptr->rectStart.right() < d_ptr->rectEnd.right())
        dx2 = delta;
    if (d_ptr->rectStart.bottom() > d_ptr->rectEnd.bottom())
        dy2 = -delta;
    else if (d_ptr->rectStart.bottom() < d_ptr->rectEnd.bottom())
        dy2 = delta;
    d_ptr->rectStart.adjust(dx1, dy1, dx2, dy2);

    if (qAbs(d_ptr->rectStart.left() - d_ptr->rectEnd.left()) <= delta)
        d_ptr->rectStart.setLeft(d_ptr->rectEnd.left());
    if (qAbs(d_ptr->rectStart.top() - d_ptr->rectEnd.top()) <= delta)
        d_ptr->rectStart.setTop(d_ptr->rectEnd.top());
    if (qAbs(d_ptr->rectStart.right() - d_ptr->rectEnd.right()) <= delta)
        d_ptr->rectStart.setRight(d_ptr->rectEnd.right());
    if (qAbs(d_ptr->rectStart.bottom() - d_ptr->rectEnd.bottom()) <= delta)
        d_ptr->rectStart.setBottom(d_ptr->rectEnd.bottom());
    if (d_ptr->rectStart == d_ptr->rectEnd)
        d_ptr->shake->stop();
    update();
}

void HSlideNavigation::init()
{
    d_ptr->slide = new QTimer(this);
    d_ptr->slide->setInterval(10);
    d_ptr->shake = new QTimer(this);
    d_ptr->shake->setInterval(10);
    connect(d_ptr->slide, &QTimer::timeout, this, &HSlideNavigation::doSlide);
    connect(d_ptr->shake, &QTimer::timeout, this, &HSlideNavigation::doShake);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::ClickFocus);
}

HE_CONTROL_END_NAMESPACE
