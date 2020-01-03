#ifndef HSCREENOBJECT_P_H
#define HSCREENOBJECT_P_H

#include "HScreenObject.h"
#include <QtGui/QPixmap>

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HSCREENOBJECT_P_H
