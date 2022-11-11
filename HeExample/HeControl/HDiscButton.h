/***************************************************************************************************
**      2022-11-01  HDiscButton
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QWidget>

HE_BEGIN_NAMESPACE

class HDiscButtonPrivate;

class HDiscButton : public QWidget
{
    Q_OBJECT

public:
    enum ButtonType
    {
        Button_Up,
        Button_Left,
        Button_Down,
        Button_Right,
        Button_Center,
        Button_None
    };

public:
    explicit HDiscButton(QWidget *parent = nullptr);
    ~HDiscButton() override;

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    bool isInBoard(const QPointF &);
    bool isInCircular(const QPointF &);
    double radius(const QPointF &);
    QPainterPath gradientArc(double startAngle, double angleLength);

protected:
    QScopedPointer<HDiscButtonPrivate> d_ptr;
};

HE_END_NAMESPACE

