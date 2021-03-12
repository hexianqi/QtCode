/***************************************************************************************************
**      2016-11-28  HNavLabel 导航标签控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86008-ds-1.html#tpc
**                  1:可设置前景色和背景色
**                  2:可设置箭头位置方向 左右上下
**                  3:可设置箭头大小
**                  4:可设置显示倒三角
**                  5:可设置倒三角长度/位置/颜色
***************************************************************************************************/

#pragma once

#include "HControlType.h"
#include <QtWidgets/QLabel>

HE_CONTROL_BEGIN_NAMESPACE

class HNavLabelPrivate;

class HNavLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)

    Q_PROPERTY(bool showArrow READ isShowArrow WRITE setShowArrow)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(HControlType::Position arrowPosition READ arrowPosition WRITE setArrowPosition)

    Q_PROPERTY(bool showTriangle READ isShowTriangle WRITE setShowTriangle)
    Q_PROPERTY(int triangleSize READ triangleSize WRITE setTriangleSize)
    Q_PROPERTY(HControlType::Position trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

public:
    explicit HNavLabel(QWidget *parent = nullptr);
    ~HNavLabel() override;

signals:
    void clicked();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int borderRadius() const;
    QColor background() const;
    QColor foreground() const;
    bool isShowArrow() const;
    int arrowSize() const;
    HControlType::Position arrowPosition() const;
    bool isShowTriangle() const;
    int triangleSize() const;
    HControlType::Position trianglePosition() const;
    QColor triangleColor() const;

public slots:
    void setBorderRadius(int value);
    void setBackground(const QColor &value);
    void setForeground(const QColor &value);
    void setShowArrow(bool b);
    void setArrowSize(int value);
    void setArrowPosition(HControlType::Position value);
    void setShowTriangle(bool b);
    void setTriangleSize(int value);
    void setTrianglePosition(HControlType::Position value);
    void setTriangleColor(const QColor &value);

protected:
    HNavLabel(HNavLabelPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawText(QPainter *);
    void drawTriangle(QPainter *);

protected:
    QScopedPointer<HNavLabelPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
