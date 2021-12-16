/***************************************************************************************************
**      2019-07-03  HPanelGauge 面板仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85992-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度+刻度尺精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置是否启用动画效果
**                  6:可设置刻度颜色+文字颜色+圆环的宽度和颜色
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
**                  8:可设置单位以及仪表盘名称
***************************************************************************************************/

#pragma once

#include "HCircleGauge.h"

HE_BEGIN_NAMESPACE

class HPanelGaugePrivate;

class HPanelGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPanelGauge)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
    Q_PROPERTY(QColor ringColor READ ringColor WRITE setRingColor)
    Q_PROPERTY(QString unit READ unit WRITE setUnit)
    Q_PROPERTY(QString text READ text WRITE setText)

public:
    explicit HPanelGauge(QWidget *parent = nullptr);

public:
    int ringWidth() const;
    QColor ringColor() const;
    QString unit() const;
    QString text() const;

public slots:
    void setRingWidth(int value);
    void setRingColor(const QColor &value);
    void setUnit(const QString &value);
    void setText(const QString &value);

protected:
    HPanelGauge(HPanelGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawScale(QPainter *, int radius) override;
    void drawValue(QPainter *, int radius) override;
};

HE_END_NAMESPACE
