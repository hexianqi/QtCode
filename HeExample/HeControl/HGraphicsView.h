/***************************************************************************************************
**      2022-09-02  HGraphicsView
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsView>

HE_BEGIN_NAMESPACE

class HGraphicsViewPrivate;

class HGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit HGraphicsView(QWidget *parent = nullptr);
    ~HGraphicsView() override;

signals:
    void mouseMovePos(QPointF);

protected:
    HGraphicsView(HGraphicsViewPrivate &p, QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *) override;

protected:
    QScopedPointer<HGraphicsViewPrivate> d_ptr;
};

HE_END_NAMESPACE

