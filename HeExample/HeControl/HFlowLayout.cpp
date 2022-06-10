#include "HFlowLayout_p.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

HFlowLayoutPrivate::HFlowLayoutPrivate(int horizontalSpacing, int verticalSpacing)
{
    this->horizontalSpacing = horizontalSpacing;
    this->verticalSpacing = verticalSpacing;
}

HFlowLayout::HFlowLayout(QWidget *parent, int margin, int horizontalSpacing, int verticalSpacing) :
    QLayout(parent),
    d_ptr(new HFlowLayoutPrivate(horizontalSpacing, verticalSpacing))
{
    setContentsMargins(margin, margin, margin, margin);
}

HFlowLayout::HFlowLayout() :
    d_ptr(new HFlowLayoutPrivate)
{
}

HFlowLayout::HFlowLayout(HFlowLayoutPrivate &p, QWidget *parent) :
    QLayout(parent),
    d_ptr(&p)
{
}

HFlowLayout::~HFlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

int HFlowLayout::count() const
{
    return d_ptr->items.size();
}

void HFlowLayout::addItem(QLayoutItem *item)
{
    d_ptr->items.append(item);
}

QLayoutItem *HFlowLayout::itemAt(int index) const
{
    return d_ptr->items.value(index);
}

QLayoutItem *HFlowLayout::takeAt(int index)
{
    return index >= 0 && index < d_ptr->items.size() ? d_ptr->items.takeAt(index) : nullptr;
}

QSize HFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize HFlowLayout::minimumSize() const
{
    QSize size;
    for (auto item : d_ptr->items)
        size = size.expandedTo(item->minimumSize());
    return size + QSize(2 * margin(), 2 * margin());
}

Qt::Orientations HFlowLayout::expandingDirections() const
{
    return Qt::Horizontal;
}

void HFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

bool HFlowLayout::hasHeightForWidth() const
{
    return true;
}

int HFlowLayout::heightForWidth(int width) const
{
    return doLayout(QRect(0, 0, width, 0), true);
}

int HFlowLayout::horizontalSpacing() const
{
    if (d_ptr->horizontalSpacing >= 0)
        return d_ptr->horizontalSpacing;
    return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int HFlowLayout::verticalSpacing() const
{
    if (d_ptr->horizontalSpacing >= 0)
        return d_ptr->verticalSpacing;
    return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

void HFlowLayout::setHorizontalSpacing(int value)
{
    if (d_ptr->horizontalSpacing == value)
        return;
    d_ptr->verticalSpacing = value;
    doLayout(this->geometry(), false);
}

void HFlowLayout::setVerticalSpacing(int value)
{
    if (d_ptr->verticalSpacing == value)
        return;
    d_ptr->verticalSpacing = value;
    doLayout(this->geometry(), false);
}

void HFlowLayout::addWidget(QWidget *widget)
{
    addItem(new QWidgetItem(widget));
}

int HFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    auto effectiveRect = rect.adjusted(left, top, -right, -bottom);
    auto x = effectiveRect.x();
    auto y = effectiveRect.y();
    auto lineHeight = 0;
    for (auto item : d_ptr->items)
    {
        auto widget = item->widget();
        auto spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = widget->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        auto spaceY = verticalSpacing();
        if (spaceY == -1)
            spaceY = widget->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        auto nextX = x + item->sizeHint().width() + spaceX;
        if (nextX - spaceX > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + spaceY;
            nextX = x + item->sizeHint().width() + spaceX;
            lineHeight = 0;
        }
        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));
        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}

int HFlowLayout::smartSpacing(QStyle::PixelMetric pm) const
{
    auto parent = this->parent();
    if (!parent)
        return -1;
    if (!parent->isWidgetType())
        return qobject_cast<QLayout *>(parent)->spacing();
    auto widget = qobject_cast<QWidget *>(parent);
    return widget->style()->pixelMetric(pm, nullptr, widget);
}

HE_END_NAMESPACE
