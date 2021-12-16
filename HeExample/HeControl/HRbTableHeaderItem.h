/***************************************************************************************************
**      2019-05-31  HRbTableHeaderItem 多标题项
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVariant>

HE_BEGIN_NAMESPACE

class HRbTableHeaderItemPrivate;

enum RbHeaderRole
{
    ColumnSpanRole = Qt::UserRole + 1,
    RowSpanRole
};

class HRbTableHeaderItem
{
public:
    explicit HRbTableHeaderItem(HRbTableHeaderItem *parent = nullptr);
    explicit HRbTableHeaderItem(int row, int column, HRbTableHeaderItem *parent = nullptr);
    virtual ~HRbTableHeaderItem();

public:
    void setData(const QVariant &data, int role);
    QVariant data(int role = ColumnSpanRole) const;
    void setText(const QString& text);
    void clear();
    int row();
    int column();
    HRbTableHeaderItem *parent();
    const HRbTableHeaderItem *child(int row, int column) const;
    HRbTableHeaderItem *child(int row, int column);
    HRbTableHeaderItem *insertChild(int row, int column);

protected:
    HRbTableHeaderItem(HRbTableHeaderItemPrivate &p);

protected:
    QScopedPointer<HRbTableHeaderItemPrivate> d_ptr;
};

HE_END_NAMESPACE
