/***************************************************************************************************
**      2019-03-22  HItemDelegate 编辑功能条目代理类。
***************************************************************************************************/

#ifndef HITEMDELEGATE_H
#define HITEMDELEGATE_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtWidgets/QItemDelegate>

class HItemDelegatePrivate;

class QDESIGNER_WIDGET_EXPORT HItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit HItemDelegate(QObject *parent = nullptr);
    ~HItemDelegate() override;

signals:
    void editingFinished();

public:
    void setOrientation(Qt::Orientation value);
    void setOrigin(QPoint value);
    void setType(const QString &);
    void setType(const QStringList &);

protected:
    HItemDelegate(HItemDelegatePrivate &p, QObject *parent = nullptr);

protected:
    QString toType(QModelIndex index) const;
    bool isRedefine(QModelIndex index) const;

protected:
    QScopedPointer<HItemDelegatePrivate> d_ptr;
};

#endif // HITEMDELEGATE_H
