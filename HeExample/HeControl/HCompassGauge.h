/***************************************************************************************************
**      2016-11-12  HCompassGauge 指南针仪表盘控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85579-ds-1.html#tpc
**                  1:可设置当前度数
**                  2:可设置精确度
**                  3:可设置边框渐变颜色
**                  4:可设置背景渐变颜色
**                  5:可设置加深和明亮颜色
**                  6:可设置指南指北指针颜色
**                  7:可设置中心点渐变颜色
***************************************************************************************************/

#ifndef HCOMPASSGAUGE_H
#define HCOMPASSGAUGE_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HCompassGaugePrivate;

class HCompassGauge : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int decimal READ decimal WRITE setDecimal)
    Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
    Q_PROPERTY(QColor backgroundStart READ backgroundStart WRITE setBackgroundStart)
    Q_PROPERTY(QColor backgroundEnd READ backgroundEnd WRITE setBackgroundEnd)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor)
    Q_PROPERTY(QColor northPointerColor READ northPointerColor WRITE setNorthPointerColor)
    Q_PROPERTY(QColor southPointerColor READ southPointerColor WRITE setSouthPointerColor)
    Q_PROPERTY(QColor crownColorStart READ crownColorStart WRITE setCrownColorStart)
    Q_PROPERTY(QColor crownColorEnd READ crownColorEnd WRITE setCrownColorEnd)
    Q_PROPERTY(QColor centerColorStart READ centerColorStart WRITE setCenterColorStart)
    Q_PROPERTY(QColor centerColorEnd READ centerColorEnd WRITE setCenterColorEnd)

public:
    explicit HCompassGauge(QWidget *parent = nullptr);
    ~HCompassGauge() override;

signals:
    void valueChanged(double value);

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    double value() const;
    int decimal() const;
    QColor foreground() const;
    QColor backgroundStart() const;
    QColor backgroundEnd() const;
    QColor textColor() const;
    QColor darkColor() const;
    QColor lightColor() const;
    QColor northPointerColor() const;
    QColor southPointerColor() const;
    QColor crownColorStart() const;
    QColor crownColorEnd() const;
    QColor centerColorStart() const;
    QColor centerColorEnd() const;

public slots:
    void setValue(double value);
    void setDecimal(int value);
    void setForeground(const QColor &value);
    void setBackgroundStart(const QColor &value);
    void setBackgroundEnd(const QColor &value);
    void setTextColor(const QColor &value);
    void setDarkColor(const QColor &value);
    void setLightColor(const QColor &value);
    void setNorthPointerColor(const QColor &value);
    void setSouthPointerColor(const QColor &value);
    void setCrownColorStart(const QColor &value);
    void setCrownColorEnd(const QColor &value);
    void setCenterColorStart(const QColor &value);
    void setCenterColorEnd(const QColor &value);
    void setCurrentValue(double value);

protected:
    HCompassGauge(HCompassGaugePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawCrownCircle(QPainter *);
    void drawBackground(QPainter *);
    void drawScale(QPainter *);
    void drawScaleLabel(QPainter *);
    void drawCoverOuterCircle(QPainter *);
    void drawCoverInnerCircle(QPainter *);
    void drawCoverCenterCircle(QPainter *);
    void drawPointer(QPainter *);
    void drawCenterCircle(QPainter *);
    void drawValue(QPainter *);

protected:
    QScopedPointer<HCompassGaugePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HCOMPASSGAUGE_H
