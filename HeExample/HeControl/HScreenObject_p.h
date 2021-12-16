#pragma once

#include "HScreenObject.h"
#include <QtGui/QPixmap>

HE_BEGIN_NAMESPACE

class HScreenObjectPrivate
{
public:
    HScreenObject::Status status;   // 状态
    QRect area;                     // 截图区域
    QSize size;                     // 屏幕大小
    QPoint startPos;                // 鼠标开始位置
    QPoint endPos;                  // 鼠标结束位置
    QPixmap fullScreen;             // 全屏图像
    QPixmap blurScreen;             // 模糊背景图
};

HE_END_NAMESPACE
