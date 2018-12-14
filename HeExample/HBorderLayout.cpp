#include "HBorderLayout_p.h"

HE_EXAMPLE_BEGIN_NAMESPACE

HBorderLayout::HBorderLayout(QWidget *parent, int margin, int spacing)
    : QLayout(parent), d_ptr(new HBorderLayoutPrivate)
{
    setContentsMargins(margin, margin, margin, margin);
    setSpacing(spacing);
}

HBorderLayout::HBorderLayout()
    : d_ptr(new HBorderLayoutPrivate)
{
}

HBorderLayout::HBorderLayout(HBorderLayoutPrivate &p, QWidget *parent)
    : QLayout(parent), d_ptr(&p)
{
}

HBorderLayout::~HBorderLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

int HBorderLayout::count() const
{
    return d_ptr->items.size();
}

void HBorderLayout::addItem(QLayoutItem *item)
{
    add(item, West);
}

QLayoutItem *HBorderLayout::itemAt(int index) const
{
    return d_ptr->items.value(index).first;
}

QLayoutItem *HBorderLayout::takeAt(int index)
{
    return index >= 0 && index < d_ptr->items.size() ? d_ptr->items.takeAt(index).first : nullptr;
}

QSize HBorderLayout::sizeHint() const
{
    return calculateSize(SizeHint);
}

QSize HBorderLayout::minimumSize() const
{
    return calculateSize(MinimumSize);
}

Qt::Orientations HBorderLayout::expandingDirections() const
{
    return Qt::Horizontal | Qt::Vertical;
}

void HBorderLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    QLayoutItem *centerItem = nullptr;
    int eastWidth = 0;
    int westWidth = 0;
    int northHeight = 0;
    int southHeight = 0;
    int centerHeight = 0;

    for (auto p : d_ptr->items)
    {
        QLayoutItem *item = p.first;
        Position position = p.second;
        if (position == North)
        {
            item->setGeometry(QRect(rect.x(), northHeight, rect.width(), item->sizeHint().height()));
            northHeight += item->geometry().height() + spacing();
        }
        if (position == South)
        {
            item->setGeometry(QRect(item->geometry().x(), item->geometry().y(), rect.width(), item->sizeHint().height()));
            southHeight += item->geometry().height() + spacing();
            item->setGeometry(QRect(rect.x(), rect.y() + rect.height() - southHeight + spacing(), item->geometry().width(), item->geometry().height()));
        }
        if (position == Center)
        {
            centerItem = item;
        }
    }

    centerHeight = rect.height() - northHeight - southHeight;

    for (auto p : d_ptr->items)
    {
        QLayoutItem *item = p.first;
        Position position = p.second;
        if (position == West)
        {
            item->setGeometry(QRect(rect.x() + westWidth, northHeight, item->sizeHint().width(), centerHeight));
            westWidth += item->geometry().width() + spacing();
        }
        if (position == East)
        {
            item->setGeometry(QRect(item->geometry().x(), item->geometry().y(), item->sizeHint().width(), centerHeight));
            eastWidth += item->geometry().width() + spacing();
            item->setGeometry(QRect( rect.x() + rect.width() - eastWidth + spacing(), northHeight, item->geometry().width(), item->geometry().height()));
        }
    }

    if (centerItem)
        centerItem->setGeometry(QRect(westWidth, northHeight, rect.width() - eastWidth - westWidth, centerHeight));
}

void HBorderLayout::add(QLayoutItem *item, Position position)
{
    d_ptr->items.append(qMakePair(item, position));
}

void HBorderLayout::add(QWidget *widget, Position position)
{
    add(new QWidgetItem(widget), position);
}

QSize HBorderLayout::calculateSize(SizeType sizeType) const
{
    QSize totalSize;
    for (auto p : d_ptr->items)
    {
        QLayoutItem *item = p.first;
        Position position = p.second;
        QSize itemSize = sizeType == MinimumSize ? item->maximumSize() : item->sizeHint();
        if (position == North || position == South || position == Center)
            totalSize.rheight() += itemSize.height();
        if (position == West || position == East || position == Center)
            totalSize.rwidth() += itemSize.width();
    }
    return totalSize;
}

HE_EXAMPLE_END_NAMESPACE
