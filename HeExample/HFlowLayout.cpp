#include "HFlowLayout_p.h"
#include <QWidget>

HE_EXAMPLE_BEGIN_NAMESPACE

HFlowLayoutPrivate::HFlowLayoutPrivate(int hSpace, int vSpacing)
{
    this->hSpacing = hSpace;
    this->vSpacing = vSpacing;
}

HFlowLayout::HFlowLayout(QWidget *parent, int margin, int hSpacing, int vSpacing)
    : QLayout(parent), d_ptr(new HFlowLayoutPrivate(hSpacing, vSpacing))
{
    setContentsMargins(margin, margin, margin, margin);
}

HFlowLayout::HFlowLayout()
    : d_ptr(new HFlowLayoutPrivate)
{
}

HFlowLayout::HFlowLayout(HFlowLayoutPrivate &p, QWidget *parent)
    : QLayout(parent), d_ptr(&p)
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
    return 0;
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
    if (d_ptr->hSpacing >= 0)
        return d_ptr->hSpacing;
    return smartSpacing(QStyle::PM_LayoutHorizontalSpacing);
}

int HFlowLayout::verticalSpacing() const
{
    if (d_ptr->vSpacing >= 0)
        return d_ptr->vSpacing;
    return smartSpacing(QStyle::PM_LayoutVerticalSpacing);
}

int HFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;
    for (auto item : d_ptr->items)
    {
        QWidget *widget = item->widget();
        int spaceX = horizontalSpacing();
        if (spaceX == -1)
            spaceX = widget->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Horizontal);
        int spaceY = verticalSpacing();
        if (spaceY == -1)
            spaceY = widget->style()->layoutSpacing(QSizePolicy::PushButton, QSizePolicy::PushButton, Qt::Vertical);
        int nextX = x + item->sizeHint().width() + spaceX;
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
    QObject *parent = this->parent();
    if (!parent)
        return -1;
    if (!parent->isWidgetType())
        return static_cast<QLayout *>(parent)->spacing();
    QWidget *widget = static_cast<QWidget *>(parent);
    return widget->style()->pixelMetric(pm, 0, widget);
}

HE_EXAMPLE_END_NAMESPACE
