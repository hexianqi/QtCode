/***************************************************************************************************
**      2019-06-26  HAntLine 蚂蚁线控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85810-ds-1.html#tpc
**                  1:可设置蚂蚁线的长度
**                  2:可设置蚂蚁线的宽度=粗细
**                  3:可设置蚂蚁线的步长
**                  4:可设置蚂蚁线的流动速度
**                  5:可设置蚂蚁线的颜色
**                  6:可设置蚂蚁线的形状
***************************************************************************************************/

#ifndef HANTLINE_H
#define HANTLINE_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HAntLinePrivate;

class HAntLine : public QWidget
{
    Q_OBJECT
    Q_ENUMS(LineStyle)
    Q_PROPERTY(int lineLength READ lineLength WRITE setLength)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(int lineStep READ lineStep WRITE setLineStep)
    Q_PROPERTY(int lineSpeed READ lineSpeed WRITE setLineSpeed)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(LineStyle lineStyle READ lineStyle WRITE setLineStyle)

public:
    enum LineStyle
    {
        Rect = 0,         // 矩形
        RoundedRect = 1,  // 圆角矩形
        Ellipse = 2,      // 椭圆
        Circle = 3        // 圆形
    };

public:
    explicit HAntLine(QWidget *parent = nullptr);
    ~HAntLine() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int lineLength() const;
    int lineWidth() const;
    int lineStep() const;
    int lineSpeed() const;
    QColor lineColor() const;
    LineStyle lineStyle() const;

public slots:
    void setLength(int value);
    void setLineWidth(int value);
    void setLineStep(int value);
    void setLineSpeed(int value);
    void setLineColor(const QColor &value);
    void setLineStyle(LineStyle value);

protected:
    HAntLine(HAntLinePrivate &p, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

protected:
    QScopedPointer<HAntLinePrivate> d_ptr;

private:
    void init();
    void updateValue();
};

HE_CONTROL_END_NAMESPACE

#endif // HANTLINE_H
