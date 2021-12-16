/***************************************************************************************************
**      2019-08-01  HColorDelegate
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QAbstractItemDelegate>

HE_BEGIN_NAMESPACE

class HColorDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit HColorDelegate(QObject *parent = nullptr);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

HE_END_NAMESPACE
