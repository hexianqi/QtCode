/***************************************************************************************************
**      2019-05-15  HSqlPainterHelper SQL绘图帮助类。
***************************************************************************************************/

#ifndef HSQLPAINTERHELPER_H
#define HSQLPAINTERHELPER_H

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
    static QPointF drawText(QPainter *painter, double x, double y, QString text, int flags = Qt::AlignLeft);
    static QPointF drawText(QPainter *painter, QRectF rect, QString text, int flags = Qt::AlignLeft);
    static QPointF drawChart(QPainter *painter, QRectF rect, QString title, QWidget *widget);
};

HE_SQL_END_NAMESPACE

#endif // HSQLPAINTERHELPER_H
