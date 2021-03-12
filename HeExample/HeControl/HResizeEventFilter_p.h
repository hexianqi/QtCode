#pragma once

#include "HResizeEventFilter.h"
#include "HAbstractMouseEventFilter_p.h"
#include <QtCore/QRect>

HE_CONTROL_BEGIN_NAMESPACE

class HResizeEventFilterPrivate : public HAbstractMouseEventFilterPrivate
{
public:
    int padding = 8;                // 边距
    QRect rectLeft;                 // 左侧区域
    QRect rectRight;                // 右侧区域
    QRect rectTop;                  // 上侧区域
    QRect rectBottom;               // 下侧区域
    QRect rectTopLeft;              // 左上侧区域
    QRect rectTopRight;             // 右上侧区域
    QRect rectBottomLeft;           // 左下侧区域
    QRect rectBottomRight;          // 右下侧区域
    bool pressedLeft;               // 鼠标按下左侧
    bool pressedRight;              // 鼠标按下右侧
    bool pressedTop;                // 鼠标按下上侧
    bool pressedBottom;             // 鼠标按下下侧
    bool pressedTopLeft;            // 鼠标按下左上侧
    bool pressedTopRight;           // 鼠标按下右上侧
    bool pressedBottomLeft;         // 鼠标按下左下侧
    bool pressedBottomRight;        // 鼠标按下右下侧
    QRect lastGeometry;             // 修改前区域
};

HE_CONTROL_END_NAMESPACE
