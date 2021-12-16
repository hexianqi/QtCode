/***************************************************************************************************
**      2017-11-26  HMiniGauge 迷你仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86061-ds-1.html#tpc
**                  1:支持指示器样式选择 线条指示器/指针指示器/圆角指针指示器/三角形指示器
**                  2:支持鼠标按下旋转改变值
**                  3:支持负数刻度值
**                  4:支持设置当前值及范围值
**                  5:支持左右旋转角度设置
**                  6:支持设置刻度数量
**                  7:支持设置边框颜色/背景颜色/文本颜色/进度颜色
**                  8:支持设置是否等分显示左右值
***************************************************************************************************/

#pragma once

#include "HControlType.h"
#include "HCircleGauge.h"

HE_BEGIN_NAMESPACE

class HMiniGaugePrivate;

class HMiniGauge : public HCircleGauge
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMiniGauge)
    Q_PROPERTY(HControlType::PointerStyle pointerStyle READ pointerStyle WRITE setPointerStyle)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(bool doubleProgress READ doubleProgress WRITE setDoubleProgress)
    Q_PROPERTY(bool showValue READ isShowValue WRITE setShowValue)

public:
    explicit HMiniGauge(QWidget *parent = nullptr);

public:
    HControlType::PointerStyle pointerStyle() const;
    QColor borderColor() const;
    QColor progressColor() const;
    bool doubleProgress() const;
    bool isShowValue() const;

public slots:
    void setPointerStyle(HControlType::PointerStyle value);
    void setBorderColor(const QColor &value);
    void setProgressColor(const QColor &value);
    void setDoubleProgress(bool b);
    void setShowValue(bool b);

protected:
    HMiniGauge(HMiniGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawProgress(QPainter *, int radius) override;
    void drawPointer(QPainter *, int radius) override;
    void drawValue(QPainter *, int radius) override;
    void drawPointerCircle(QPainter *);
    void drawPointerIndicator(QPainter *);
    void drawPointerIndicatorR(QPainter *);
    void drawPointerTriangle(QPainter *);
    void drawPointerCenter(QPainter *);
    void drawCircle(QPainter *);

private:
    void setPressedValue(QPointF value);

};

HE_END_NAMESPACE

//    Q_PROPERTY(int step READ getStep WRITE setStep)

//protected:
//    void mousePressEvent(QMouseEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);
//    void paintEvent(QPaintEvent *);
//    void drawScale(QPainter *painter);
//    void drawBgCircle(QPainter *painter);
//    void drawCenterCircle(QPainter *painter);
//    void drawPointerLine(QPainter *painter);
//    void drawPointerIndicator(QPainter *painter);
//    void drawPointerIndicatorR(QPainter *painter);
//    void drawPointerTriangle(QPainter *painter);
//    void drawValue(QPainter *painter);

//private:
//    double minValue;                //最小值
//    double maxValue;                //最大值
//    double value;                   //目标值
//    int precision;                  //精确度,小数点后几位

//    int step;                       //刻度数量
//    int startAngle;                 //开始旋转角度
//    int endAngle;                   //结束旋转角度

//    QColor borderColor;             //边框颜色
//    QColor bgColor;                 //背景颜色
//    QColor textColor;               //文字颜色
//    QColor percentColor;            //进度颜色

//    bool doublePercent;             //是否对半等分范围值
//    bool showValue;                 //是否显示当前值
//    PointerStyle pointerStyle;      //指针样式

//private:
//    //鼠标是否按下
//    bool pressed;
//    //根据鼠标按下的坐标设置当前按下坐标处的值
//    void setPressedValue(QPointF pressedPoint);

//public:
//    double getMinValue()            const;
//    double getMaxValue()            const;
//    double getValue()               const;
//    int getPrecision()              const;

//    int getStep()                   const;
//    int getStartAngle()             const;
//    int getEndAngle()               const;

//    QColor getBorderColor()         const;
//    QColor getBgColor()             const;
//    QColor getTextColor()           const;
//    QColor getPercentColor()        const;

//    bool getDoublePercent()         const;
//    bool getShowValue()             const;
//    PointerStyle getPointerStyle()  const;

//    QSize sizeHint()                const;
//    QSize minimumSizeHint()         const;

//public Q_SLOTS:
//    //设置范围值
//    void setRange(double minValue, double maxValue);
//    void setRange(int minValue, int maxValue);

//    //设置最大最小值
//    void setMinValue(double minValue);
//    void setMaxValue(double maxValue);

//    //设置目标值
//    void setValue(double value);
//    void setValue(int value);

//    //设置精确度
//    void setPrecision(int precision);

//    //设置刻度数量
//    void setStep(int step);
//    //设置开始旋转角度
//    void setStartAngle(int startAngle);
//    //设置结束旋转角度
//    void setEndAngle(int endAngle);

//    //设置边框颜色
//    void setBorderColor(const QColor &borderColor);
//    //设置背景颜色
//    void setBgColor(const QColor &bgColor);
//    //设置文本颜色
//    void setTextColor(const QColor &textColor);
//    //设置进度颜色
//    void setPercentColor(const QColor &percentColor);

//    //设置是否对半等分范围值
//    void setDoublePercent(bool doublePercent);
//    //设置是否显示当前值
//    void setShowValue(bool showValue);
//    //设置指针样式
//    void setPointerStyle(const PointerStyle &pointerStyle);

//Q_SIGNALS:
//    void valueChanged(double value);
//};
