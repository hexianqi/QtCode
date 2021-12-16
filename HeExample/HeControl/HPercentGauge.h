/***************************************************************************************************
**      2018-08-30  HPercentGauge 百分比仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85620-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置仪表盘的标题
**                  6:可设置外圆背景/内圆背景/饼圆三种颜色/刻度尺颜色/文字颜色
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
**                  8:可自由拓展各种渐变色,各圆的半径
***************************************************************************************************/

#pragma once

#include "HCircleGauge.h"

HE_BEGIN_NAMESPACE

class HPercentGaugePrivate;

class HPercentGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPercentGauge)
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)
    Q_PROPERTY(QColor arcColor READ arcColor WRITE setArcColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QString title READ title WRITE setTitle)

public:
    explicit HPercentGauge(QWidget *parent = nullptr);

public:
    QColor baseColor() const;
    QColor arcColor() const;
    QColor titleColor() const;
    QString title() const;

public slots:
    void setBaseColor(const QColor &value);
    void setArcColor(const QColor &value);
    void setTitleColor(const QColor &value);
    void setTitle(const QString &value);

protected:
    HPercentGauge(HPercentGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawPointer(QPainter *, int radius) override;
    void drawTitle(QPainter *);
};

HE_END_NAMESPACE
