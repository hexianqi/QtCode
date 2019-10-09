/***************************************************************************************************
**      2019-03-28  HCustomGraphics 自定义多边形控件
**                  http://www.qtcn.org/bbs/read-htm-tid-85583-ds-1.html#tpc
**                  1:自定义随意绘制多边形
**                  2:产生闭合形状后可单击选中移动整个多边形
**                  3:可拉动某个点
**                  4:支持多个多边形
**                  5:鼠标右键退出绘制
**                  6:可设置各种颜色
***************************************************************************************************/

#ifndef HCUSTOMGRAPHICS_H
#define HCUSTOMGRAPHICS_H

#include "HControlGlobal.h"
#include <QtWidgets/QWidget>

HE_CONTROL_BEGIN_NAMESPACE

class HCustomGraphicsPrivate;

class HCustomGraphics : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool selectDotVisible READ isSelectDotVisible WRITE setSelectDotVisible)
    Q_PROPERTY(int dotRadius READ dotRadius WRITE setDotRadius)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor dotColor READ dotColor WRITE setDotColor)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor polygonColor READ polygonColor WRITE setPolygonColor)
    Q_PROPERTY(QColor selectColor READ selectColor WRITE setSelectColor)

public:
    explicit HCustomGraphics(QWidget *parent = nullptr);
    ~HCustomGraphics() override;

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    bool isSelectDotVisible() const;
    int dotRadius() const;
    int lineWidth() const;
    QColor dotColor() const;
    QColor lineColor() const;
    QColor polygonColor() const;
    QColor selectColor() const;

public slots:
    void setSelectDotVisible(bool b);
    void setDotRadius(int value);
    void setLineWidth(int value);
    void setDotColor(const QColor &value);
    void setLineColor(const QColor &value);
    void setPolygonColor(const QColor &value);
    void setSelectColor(const QColor &value);

protected:
    HCustomGraphics(HCustomGraphicsPrivate &p, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void drawPolygon(QPainter *);
    void drawLines(QPainter *);

protected:
    QScopedPointer<HCustomGraphicsPrivate> d_ptr;

private:
    void init();
    // 计算两点间的距离
    double calcLength(const QPoint &p1, const QPoint &p2);
    // 检测是否选中多边形
    bool checkPoint(const QVector<QPoint> &points, QPoint p);
    // 清除临时绘制的
    void clearTemp();
    // 清除所有
    void clearAll();
};

HE_CONTROL_END_NAMESPACE

#endif // HCUSTOMGRAPHICS_H
