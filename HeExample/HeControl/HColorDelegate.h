/***************************************************************************************************
**      2019-08-01  HColorDelegate
***************************************************************************************************/

#ifndef HCOLORDELEGATE_H
#define HCOLORDELEGATE_H

#include "HControlGlobal.h"
#include <QtWidgets/QAbstractItemDelegate>

HE_CONTROL_BEGIN_NAMESPACE

class HColorDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit HColorDelegate(QObject *parent = nullptr);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORDELEGATE_H
