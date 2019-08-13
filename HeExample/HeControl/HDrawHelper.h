/***************************************************************************************************
**      2019-07-11  HDrawHelper 绘制帮助类。
***************************************************************************************************/

#ifndef HDRAWHELPER_H
#define HDRAWHELPER_H

#include "HControlGlobal.h"

class QPainter;
class QColor;
class QPixmap;
class QImage;
class QSize;
class QPen;

HE_CONTROL_BEGIN_NAMESPACE

class HDrawHelper
{
public:
    // 绘制遮罩层
    static void drawOverlay(QPainter *, double radius, QColor color);
    // 创建平铺图像
    static QImage createTiledImage(QColor color1, QColor color2, int size);
    // 创建十字图片
    static QImage createCrossImage(QSize size, QPen pen);
};

HE_CONTROL_END_NAMESPACE

#endif // HDRAWHELPER_H
