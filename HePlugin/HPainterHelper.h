/***************************************************************************************************
**      2021-10-22  HPainterHelper SQL绘图帮助类。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QString>

class QPainter;
class QPointF;
class QRectF;
class QWidget;

class QDESIGNER_WIDGET_EXPORT HPainterHelper
{
public:
    // 绘制文本
    static QPointF drawText(QPainter *painter, double x, double y, const QString &text, int flags = Qt::AlignLeft);
    static QPointF drawText(QPainter *painter, QRectF rect, const QString &text, int flags = Qt::AlignLeft);
    // 绘制LOGO
    static QPointF drawLogo(QPainter *painter, QRectF rect, QString fileName = QString());
    // 绘制图表
    static QPointF drawChart(QPainter *painter, QRectF rect, QWidget *widget);
};
