/***************************************************************************************************
**      2019-05-15  HSqlPainterHelper SQL绘图帮助类。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include <qnamespace.h>

class QPainter;
class QPointF;
class QRectF;
class QWidget;

HE_SQL_BEGIN_NAMESPACE

class HSqlPainterHelper
{
public:
    static QPointF drawText(QPainter *painter, double x, double y, const QString &text, int flags = Qt::AlignLeft);
    static QPointF drawText(QPainter *painter, QRectF rect, const QString &text, int flags = Qt::AlignLeft);
    static QPointF drawLogo(QPainter *painter, QRectF rect);
    static QPointF drawChart(QPainter *painter, QRectF rect, const QString &title, QWidget *widget);
};

HE_SQL_END_NAMESPACE
