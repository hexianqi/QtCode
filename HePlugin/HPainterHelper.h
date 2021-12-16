/***************************************************************************************************
**      2021-10-22  HPainterHelper 绘图帮助类。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QVariant>

class QPainter;

class QDESIGNER_WIDGET_EXPORT HPainterHelper
{
public:
    // 绘制文本
    static QPointF drawText(QPainter *, double x, double y, const QString &text, int flags = Qt::AlignLeft);
    static QPointF drawText(QPainter *, QRectF rect, const QString &text, int flags = Qt::AlignLeft);
    // 绘制LOGO
    static QPointF drawLogo(QPainter *, QRectF rect, QString fileName = QString());
    // 绘制图表
    static QPointF drawChart(QPainter *, QRectF rect, QWidget *widget);
    // 绘制箭头
    static void drawQuiver(QPainter *, QPointF p1, QPointF p2, int size = 8);
    // 绘制十字瞄准线
    static void drawCrosshair(QPainter *, QPointF point, int size, const QColor &);
    // 绘制十字光标
    static void drawCrossCursor(QPainter *, QPointF point, int size, const QColor &);
    static void drawCrossCursor(QPainter *, QPointF point, int size = 3);
    // 打印页头
    static double paintHeader(QPainter *, const QVariantMap &param);
    // 打印页尾
    static double paintFooter(QPainter *, const QString &footer);

};
