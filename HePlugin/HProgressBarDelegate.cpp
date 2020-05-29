#include "HProgressBarDelegate.h"
#include <QtWidgets/QApplication>

void HProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().type() != QVariant::Int)
        return QStyledItemDelegate::paint(painter, option, index);

    auto progress = index.data().toInt();
    QStyleOptionProgressBar progressBarOption;
    progressBarOption.rect = option.rect.adjusted(4, 4, -4, -4);
    progressBarOption.minimum = 0;
    progressBarOption.maximum = 100;
    progressBarOption.progress = progress;
    progressBarOption.textVisible = true;
    progressBarOption.text = QString("%1%").arg(progress);
    progressBarOption.textAlignment = Qt::AlignCenter;
    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
}

bool HProgressBarDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() != QEvent::MouseButtonDblClick)
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    return true;
}
