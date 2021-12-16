/***************************************************************************************************
**      2019-08-27  HNavTreeView
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QTreeView>

class QStandardItem;

HE_BEGIN_NAMESPACE

class HNavTreeViewPrivate;

class HNavTreeView : public QTreeView
{
    Q_OBJECT
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor normalBackground READ normalBackground WRITE setNormalBackground)
    Q_PROPERTY(QColor hoverBackground READ hoverBackground WRITE setHoverBackground)
    Q_PROPERTY(QColor selectedBackground READ selectedBackground WRITE setSelectedBackground)
    Q_PROPERTY(QColor normalTextColor READ normalTextColor WRITE setNormalTextColor)
    Q_PROPERTY(QColor hoverTextColor READ hoverTextColor WRITE setHoverTextColor)
    Q_PROPERTY(QColor selectedTextColor READ selectedTextColor WRITE setSelectedTextColor)

public:
    explicit HNavTreeView(QWidget *parent = nullptr);
    ~HNavTreeView() override;

public:
    QString info(const QModelIndex &index);
    QColor lineColor() const;
    QColor normalBackground() const;
    QColor hoverBackground() const;
    QColor selectedBackground() const;
    QColor normalTextColor() const;
    QColor hoverTextColor() const;
    QColor selectedTextColor() const;

public slots:
    void addItem(const QString &text, QStandardItem *parent = nullptr);
    void addItem(const QString &text, const QString &parentText);
    void setItemInfo(const QString &itemText, const QString &info);
    void setLineColor(const QColor &value);
    void setNormalBackground(const QColor &value);
    void setHoverBackground(const QColor &value);
    void setSelectedBackground(const QColor &value);
    void setNormalTextColor(const QColor &value);
    void setHoverTextColor(const QColor &value);
    void setSelectedTextColor(const QColor &value);

protected:
    HNavTreeView(HNavTreeViewPrivate &p, QWidget *parent = nullptr);

protected:
    QScopedPointer<HNavTreeViewPrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
