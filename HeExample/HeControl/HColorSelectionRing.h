/***************************************************************************************************
**      2022-11-21  HColorSelectionRingWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HColorSelectionRingPrivate;

class HColorSelectionRing : public QWidget
{
    Q_OBJECT

public:
    explicit HColorSelectionRing(QWidget *parent = nullptr);
    ~HColorSelectionRing() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent* )override;
    void mouseMoveEvent(QMouseEvent *)override;
    void showEvent(QShowEvent *) override;

protected:
    QColor getColorInWidget(const QPoint &);

protected:
    QScopedPointer<HColorSelectionRingPrivate> d_ptr;
};

HE_END_NAMESPACE

