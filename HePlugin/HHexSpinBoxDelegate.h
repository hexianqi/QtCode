/***************************************************************************************************
**      2019-03-22  HHexSpinBoxDelegate 编辑功能(16进制调节框)条目代理基类。
***************************************************************************************************/

#ifndef HHEXSPINBOXDELEGATE_H
#define HHEXSPINBOXDELEGATE_H

#include "HItemDelegate.h"

class HHexSpinBoxDelegatePrivate;

class QDESIGNER_WIDGET_EXPORT HHexSpinBoxDelegate : public HItemDelegate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HHexSpinBoxDelegate)

public:
    explicit HHexSpinBoxDelegate(QObject *parent = nullptr);
    ~HHexSpinBoxDelegate() override;

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;

protected:
    HHexSpinBoxDelegate(HHexSpinBoxDelegatePrivate &p, QObject *parent = nullptr);
};


#endif // HHEXSPINBOXDELEGATE_H
