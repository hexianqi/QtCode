/***************************************************************************************************
**      2016-12-31  HSpeedGauge 速度仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85567-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置大刻度数量/小刻度数量
**                  4:可设置开始旋转角度/结束旋转角度
**                  5:可设置是否启用动画效果
**                  6:可设置三色圆环占比例
**                  7:自适应窗体拉伸,刻度尺和文字自动缩放
***************************************************************************************************/

#ifndef HSPEEDGAUGE_H
#define HSPEEDGAUGE_H

#include "HCircleGauge.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSpeedGaugePrivate;

class HSpeedGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpeedGauge)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
    Q_PROPERTY(int ringPercentStart READ ringPercentStart WRITE setRingPercentStart)
    Q_PROPERTY(int ringPercentMid READ ringPercentMid WRITE setRingPercentMid)
    Q_PROPERTY(int ringPercentEnd READ ringPercentEnd WRITE setRingPercentEnd)
    Q_PROPERTY(QColor ringColorStart READ ringColorStart WRITE setRingColorStart)
    Q_PROPERTY(QColor ringColorMid READ ringColorMid WRITE setRingColorMid)
    Q_PROPERTY(QColor ringColorEnd READ ringColorEnd WRITE setRingColorEnd)

public:
    explicit HSpeedGauge(QWidget *parent = nullptr);
    ~HSpeedGauge() override;

public:
    int ringWidth() const;
    int ringPercentStart() const;
    int ringPercentMid() const;
    int ringPercentEnd() const;
    QColor ringColorStart() const;
    QColor ringColorMid() const;
    QColor ringColorEnd() const;

public slots:
    void setRingWidth(int value);
    void setRingPercentStart(int value);
    void setRingPercentMid(int value);
    void setRingPercentEnd(int value);
    void setRingColorStart(const QColor &value);
    void setRingColorMid(const QColor &value);
    void setRingColorEnd(const QColor &value);

protected:
    HSpeedGauge(HSpeedGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawScale(QPainter *, int radius) override;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HSPEEDGAUGE_H
