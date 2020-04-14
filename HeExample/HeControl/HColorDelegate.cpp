#include "HColorDelegate.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HColorDelegate::HColorDelegate(QObject *parent) :
    QAbstractItemDelegate(parent)
{
}

void HColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    painter->save();
    painter->setBrush(index.data(Qt::DecorationRole).value<QColor>());
    painter->drawRect(option.rect);
    if (option.state & QStyle::State_Selected)
    {
        auto pen = painter->pen();
        pen.setWidth(2);
        painter->setPen(pen);
        painter->drawRect(option.rect.adjusted(1, 1, 0, 0));
    }
    painter->restore();
}

QSize HColorDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return {16, 16};
}

HE_CONTROL_END_NAMESPACE
