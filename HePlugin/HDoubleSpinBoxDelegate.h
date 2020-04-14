/***************************************************************************************************
**      2019-03-22  HDoubleSpinBoxDelegate 编辑功能(双精度数字调节框)条目代理类。
***************************************************************************************************/

#ifndef HDOUBLESPINBOXDELEGATE_H
#define HDOUBLESPINBOXDELEGATE_H

#include "HItemDelegate.h"

class HDoubleSpinBoxDelegatePrivate;

class QDESIGNER_WIDGET_EXPORT HDoubleSpinBoxDelegate : public HItemDelegate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDoubleSpinBoxDelegate)

public:
    explicit HDoubleSpinBoxDelegate(QObject *parent = nullptr);

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;

protected:
    HDoubleSpinBoxDelegate(HDoubleSpinBoxDelegatePrivate &p, QObject *parent = nullptr);
};

#endif // HDOUBLESPINBOXDELEGATE_H
