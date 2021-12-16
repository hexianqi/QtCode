/***************************************************************************************************
**      2019-07-11  HDrawHelper 绘制帮助类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <qnamespace.h>

class QChar;
class QSize;
class QPointF;
class QColor;
class QPen;
class QPainter;
class QImage;
class QPixmap;
class QFont;

HE_BEGIN_NAMESPACE

class HDrawHelper
{
public:
    // 绘制遮罩层
    static void drawOverlay(QPainter *, double radius, QColor color);
    // 绘制十字瞄准线
    static void drawCrosshair(QPainter *, QPointF point, int width, const QColor &color);
    // 绘制十字光标
    static void drawCrossCursor(QPainter *, QPointF point, int size, const QColor &color);
    // 创建平铺图像
    static QImage createTiledImage(int size, const QColor &color1, const QColor &color2);
    // 创建十字图像
    static QImage createCrossImage(QSize size, const QPen &pen);
    // 创建字体图像
    static QImage createFontImage(const QFont &font, const QChar &c, QSize size, const QPen &pen, int flags = Qt::AlignCenter);
    // 自动调节文字大小
    static QFont adjustFontSize(QPainter *, const QString &text, double width);
    // 加载svg图片
    static QPixmap loadSvgToPixmap(const QString& path, QSize size);
};

HE_END_NAMESPACE
