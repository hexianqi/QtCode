/***************************************************************************************************
**      2019-07-26  HLightPoint 呼吸点控件
**                  http://www.qtcn.org/bbs/read-htm-tid-86005-ds-1.html#tpc
**                  1:可设置呼吸间隔
**                  2:可设置颜色透明渐变步长
**                  3:可设置背景颜色
***************************************************************************************************/

#ifndef HLIGHTPOINT_H
#define HLIGHTPOINT_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HLightPointPrivate;

class HLightPoint : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(int interval READ interval WRITE setInterval)
    Q_PROPERTY(QColor background READ background WRITE setBackground)

public:
    explicit HLightPoint(QWidget *parent = nullptr);
    ~HLightPoint() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int step() const;
    int interval() const;
    QColor background() const;

public slots:
    void setStep(int value);
    void setInterval(int value);
    void setBackground(const QColor &value);

protected:
    HLightPoint(HLightPointPrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void drawBackground(QPainter *);

protected:
    QScopedPointer<HLightPointPrivate> d_ptr;

private:
    void init();
    void updateValue();
};

HE_CONTROL_END_NAMESPACE

#endif // HLIGHTPOINT_H
