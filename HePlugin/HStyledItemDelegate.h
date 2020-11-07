/***************************************************************************************************
**      2019-03-22  HItemDelegate 编辑功能条目代理类。
***************************************************************************************************/

#ifndef HSTYLEDITEMDELEGATE_H
#define HSTYLEDITEMDELEGATE_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QStyledItemDelegate>

class HStyledItemDelegatePrivate;

class QDESIGNER_WIDGET_EXPORT HStyledItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit HStyledItemDelegate(QObject *parent = nullptr);
    ~HStyledItemDelegate() override;

public:
    void setOrientation(Qt::Orientation value);
    void setOrigin(QPoint value);
    void setType(const QString &);
    void setType(const QStringList &);

protected:
    HStyledItemDelegate(HStyledItemDelegatePrivate &p, QObject *parent = nullptr);

protected:
    QString toType(QModelIndex index) const;
    bool isRedefine(QModelIndex index) const;

protected:
    QScopedPointer<HStyledItemDelegatePrivate> d_ptr;
};

#endif // HSTYLEDITEMDELEGATE_H
