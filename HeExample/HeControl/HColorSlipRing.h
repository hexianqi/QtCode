/***************************************************************************************************
**      2022-11-04  HColorSlipRing
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HColorSlipRingPrivate;

class HColorSlipRing : public QWidget
{
    Q_OBJECT

public:
    explicit HColorSlipRing(QWidget *parent = nullptr);
    ~HColorSlipRing() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    QPointF calcPos(double angle, int radius);

protected:
    QScopedPointer<HColorSlipRingPrivate> d_ptr;
};

HE_END_NAMESPACE

