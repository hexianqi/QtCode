/***************************************************************************************************
**      2019-05-01  HRingProgressBar 环形进度条控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85617-ds-1.html#tpc
**                  1:可设置范围值,支持负数值
**                  2:可设置精确度,最大支持小数点后3位
**                  3:可设置起始角度
**                  4:可设置三种值+三种颜色,启用自动检测值后绘制不同的颜色
**                  5:可设置背景颜色/文字颜色/进度颜色/中间圆颜色
**                  6:可设置值警戒报警比较模式 0-不比较 1-最大值报警 2-最小值报警
**                  7:可设置显示的值是百分比
**                  8:可设置圆环与背景之间的距离即间距
**                  9:可设置圆环的宽度
**                  10:可设置圆环背景颜色,形成两种颜色差
**                  11:可设置顺时针逆时针转
**                  12:自适应窗体拉伸,刻度尺和文字自动缩放
***************************************************************************************************/

#ifndef HRINGPROGRESSBAR_H
#define HRINGPROGRESSBAR_H

#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRingProgressBarPrivate;

class HRingProgressBar : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRingProgressBar)
    Q_PROPERTY(bool reverse READ isReverse WRITE setReverse)
    Q_PROPERTY(bool showPercent READ isShowPercent WRITE setShowPercent)
    Q_PROPERTY(int alarmMode READ alarmMode WRITE setAlarmMode)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int ringPadding READ ringPadding WRITE setRingPadding)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
    Q_PROPERTY(int ringValue1 READ ringValue1 WRITE setRingValue1)
    Q_PROPERTY(int ringValue2 READ ringValue2 WRITE setRingValue2)
    Q_PROPERTY(int ringValue3 READ ringValue3 WRITE setRingValue3)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor circleColor READ circleColor WRITE setCircleColor)
    Q_PROPERTY(QColor ringBackground READ ringBackground WRITE setRingBackground)
    Q_PROPERTY(QColor ringColor READ ringColor WRITE setRingColor)
    Q_PROPERTY(QColor ringColor1 READ ringColor1 WRITE setRingColor1)
    Q_PROPERTY(QColor ringColor2 READ ringColor2 WRITE setRingColor2)
    Q_PROPERTY(QColor ringColor3 READ ringColor3 WRITE setRingColor3)

public:
    explicit HRingProgressBar(QWidget *parent = nullptr);
    ~HRingProgressBar() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isReverse() const;
    bool isShowPercent() const;
    int alarmMode() const;
    int angleStart() const;
    int ringPadding() const;
    int ringWidth() const;
    int ringValue1() const;
    int ringValue2() const;
    int ringValue3() const;
    QColor background() const;
    QColor textColor() const;
    QColor circleColor() const;
    QColor ringBackground() const;
    QColor ringColor() const;
    QColor ringColor1() const;
    QColor ringColor2() const;
    QColor ringColor3() const;

public slots:
    void setDecimal(int value) override;
    void setReverse(bool b);
    void setShowPercent(bool b);
    void setAlarmMode(int value);
    void setAngleStart(int value);
    void setRingPadding(int value);
    void setRingWidth(int value);
    void setRingValue1(int value);
    void setRingValue2(int value);
    void setRingValue3(int value);
    void setBackground(const QColor &value);
    void setTextColor(const QColor &value);
    void setCircleColor(const QColor &value);
    void setRingBackground(const QColor &value);
    void setRingColor(const QColor &value);
    void setRingColor1(const QColor &value);
    void setRingColor2(const QColor &value);
    void setRingColor3(const QColor &value);

protected:
    HRingProgressBar(HRingProgressBarPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawRing(QPainter *);
    void drawPadding(QPainter *);
    void drawCircle(QPainter *);
    void drawValue(QPainter *);
};

HE_CONTROL_END_NAMESPACE

#endif // HRINGPROGRESSBAR_H
