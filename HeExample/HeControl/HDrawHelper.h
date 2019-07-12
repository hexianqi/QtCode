/***************************************************************************************************
**      2019-07-11  HDrawHelper 绘制帮助类。
***************************************************************************************************/

#ifndef HDRAWHELPER_H
#define HDRAWHELPER_H

#include "HControlGlobal.h"

class QPainter;
class QColor;

HE_CONTROL_BEGIN_NAMESPACE

class HDrawHelper
{
public:
    // 绘制遮罩层
    static void drawOverlay(QPainter *, double radius, QColor color);

};

HE_CONTROL_END_NAMESPACE

#endif // HDRAWHELPER_H
