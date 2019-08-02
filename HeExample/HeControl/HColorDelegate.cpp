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
    auto c = qvariant_cast<QColor>(index.data(Qt::DecorationRole));
    painter->save();
    painter->setBrush(c);
    painter->drawRect(option.rect);
    if (option.state & QStyle::State_Selected)
    {
        auto p = painter->pen();
        p.setWidth(2);
        painter->setPen(p);
        painter->drawRect(option.rect.adjusted(1, 1, 0, 0));
    }
    painter->restore();
}

QSize HColorDelegate::sizeHint(const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    return QSize(16, 16);
}

HE_CONTROL_END_NAMESPACE
