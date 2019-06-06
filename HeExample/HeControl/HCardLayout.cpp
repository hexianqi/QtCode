#include "HCardLayout_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HCardLayout::HCardLayout(QWidget *parent)
    : QLayout(parent), d_ptr(new HCardLayoutPrivate)
{
}

HCardLayout::HCardLayout()
    : d_ptr(new HCardLayoutPrivate)
{
}

HCardLayout::HCardLayout(HCardLayoutPrivate &p, QWidget *parent)
    : QLayout(parent), d_ptr(&p)
{
}

// 由于QLayoutItem不继承自QObject，必须手动删除。在析构函数中，使用takeAt()删除列表中的每个项目，然后将其删除。
HCardLayout::~HCardLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

// 获取列表中的项目数
int HCardLayout::count() const
{
    return d_ptr->items.size();
}

// 添加项目
void HCardLayout::addItem(QLayoutItem *item)
{
    d_ptr->items.append(item);
}

// 获取索引idx所对应的项目
QLayoutItem *HCardLayout::itemAt(int index) const
{
    return d_ptr->items.value(index);
}

// 移除索引idx所对应的项目，并返回
QLayoutItem *HCardLayout::takeAt(int index)
{
    return index >= 0 && index < d_ptr->items.size() ? d_ptr->items.takeAt(index) : nullptr;
}

// sizeHint()和minimumSize()通常非常相似。这两个函数返回的尺寸应包括spacing()，但不包括margin()。
QSize HCardLayout::sizeHint() const
{
    int n = count();
    QSize size = n > 0 ? QSize(100, 70) : QSize(0, 0);
    for (auto item : d_ptr->items)
        size = size.expandedTo(item->sizeHint());
    return size + n * QSize(spacing(), spacing());
}

QSize HCardLayout::minimumSize() const
{
    QSize size;
    for (auto item : d_ptr->items)
        size = size.expandedTo(item->minimumSize());
    return size + count() * QSize(spacing(), spacing());
}

// 实际控制着布局，作为参数提供的矩形不包括margin()。相关的，使用spacing()作为项目之间的距离。
void HCardLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    int n = count();
    if (n == 0)
        return;

    int w = rect.width() - (n - 1) * spacing();
    int h = rect.height() - (n - 1) * spacing();
    for (int i = 0; i < n; i++)
        itemAt(i)->setGeometry(QRect(rect.x() + i * spacing(), rect.y() + i * spacing(), w, h));
}

HE_CONTROL_END_NAMESPACE
