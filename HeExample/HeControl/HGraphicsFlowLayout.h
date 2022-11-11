/***************************************************************************************************
**      2022-10-24  HGraphicsFlowLayout
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsLayout>

HE_BEGIN_NAMESPACE

class HGraphicsFlowLayoutPrivate;

class HGraphicsFlowLayout : public QGraphicsLayout
{

public:
    explicit HGraphicsFlowLayout(QGraphicsLayoutItem *parent = nullptr);
    ~HGraphicsFlowLayout() override;

public:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;
    int count() const override;
    void setGeometry(const QRectF &) override;
    void removeAt(int) override;
    QGraphicsLayoutItem *itemAt(int) const override;
    void addItem(QGraphicsLayoutItem *);

protected:
    HGraphicsFlowLayout(HGraphicsFlowLayoutPrivate &p, QGraphicsLayoutItem *parent = nullptr);

protected:
    QScopedPointer<HGraphicsFlowLayoutPrivate> d_ptr;
};

HE_END_NAMESPACE
