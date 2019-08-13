/***************************************************************************************************
**      2019-07-04  HKnobGauge 旋钮仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85608-ds-1.html#tpc
**                  1:支持指示器样式选择(圆形/指针/圆角指针/三角形)
**                  2:支持鼠标按下旋转改变值
**                  3:支持负数范围值
**                  4:支持设置当前值及范围值
**                  5:支持设置起始旋转角度和结束旋转角度
**                  6:支持设置背景色/进度颜色/中间圆渐变颜色
**                  7:随窗体拉伸自动变化
**                  8:支持鼠标进入和离开动画效果
**                  9:可设置是否显示当前值
**                  10:可设置是否显示指示器
***************************************************************************************************/

#ifndef HKNOBGAUGE_H
#define HKNOBGAUGE_H

#include "HControlType.h"
#include "HAnimationProgress.h"

HE_CONTROL_BEGIN_NAMESPACE

class HKnobGaugePrivate;

class HKnobGauge : public HAnimationProgress
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKnobGauge)
    Q_PROPERTY(int angleStart READ angleStart WRITE setAngleStart)
    Q_PROPERTY(int angleEnd READ angleEnd WRITE setAngleEnd)
    Q_PROPERTY(QColor background READ background WRITE setBackground)
    Q_PROPERTY(QColor progressBackground READ progressBackground WRITE setProgressBackground)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(QColor circleColorStart READ circleColorStart WRITE setCircleColorStart)
    Q_PROPERTY(QColor circleColorEnd READ circleColorEnd WRITE setCircleColorEnd)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(bool showPointer READ isShowPointer WRITE setShowPointer)
    Q_PROPERTY(bool showValue READ isShowValue WRITE setShowValue)
    Q_PROPERTY(HControlType::PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)

public:
    explicit HKnobGauge(QWidget *parent = nullptr);
    ~HKnobGauge() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int angleStart() const;
    int angleEnd() const;
    QColor background() const;
    QColor progressBackground() const;
    QColor progressColor() const;
    QColor circleColorStart() const;
    QColor circleColorEnd() const;
    QColor textColor() const;
    bool isShowPointer() const;
    bool isShowValue() const;
    HControlType::PointerStyle pointerStyle() const;

public slots:
    void setAngleStart(int value);
    void setAngleEnd(int value);
    void setBackground(const QColor &value);
    void setProgressBackground(const QColor &value);
    void setProgressColor(const QColor &value);
    void setCircleColorStart(const QColor &value);
    void setCircleColorEnd(const QColor &value);
    void setTextColor(const QColor &value);
    void setShowPointer(bool b);
    void setShowValue(bool b);
    void setPointerStyle(HControlType::PointerStyle pointerStyle);

protected:
    HKnobGauge(HKnobGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);
    void drawColorPie(QPainter *);
    void drawCoverCircle(QPainter *);
    void drawCircle(QPainter *);
    void drawPointer(QPainter *);
    void drawPointerCircle(QPainter *);
    void drawPointerIndicator(QPainter *);
    void drawPointerIndicatorR(QPainter *);
    void drawPointerTriangle(QPainter *);
    void drawPointerCenter(QPainter *);
    void drawValue(QPainter *painter);

protected:
    double angleSpan();
    double toAngle(double value);
    double fromAngle(double value);

private:
    void init();
    void updateRadius(QVariant value);
    void setPressedValue(QPointF value);
};

HE_CONTROL_END_NAMESPACE

#endif // HKNOBGAUGE_H
