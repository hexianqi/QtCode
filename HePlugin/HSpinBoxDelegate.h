/***************************************************************************************************
**      2022-01-28  HSpinBoxDelegate
***************************************************************************************************/

#pragma once

#include "HStyledItemDelegate.h"

class HSpinBoxDelegatePrivate;

class QDESIGNER_WIDGET_EXPORT HSpinBoxDelegate : public HStyledItemDelegate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpinBoxDelegate)

public:
    explicit HSpinBoxDelegate(QObject *parent = nullptr);

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;

protected:
    HSpinBoxDelegate(HSpinBoxDelegatePrivate &p, QObject *parent = nullptr);
};



