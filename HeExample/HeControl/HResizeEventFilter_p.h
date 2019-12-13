#ifndef HRESIZEEVENTFILTER_P_H
#define HRESIZEEVENTFILTER_P_H

#include "HResizeEventFilter.h"
#include "HAbstractEventFilter_p.h"
#include <QtCore/QRect>

HE_CONTROL_BEGIN_NAMESPACE

class HResizeEventFilterPrivate : public HAbstractEventFilterPrivate
{
public:
    int padding = 8;                // 边距
    QRect rectLeft;                 // 左侧区域
    QRect rectRight;                // 右侧区域
    QRect rectTop;                  // 上侧区域
    QRect rectBottom;               // 下侧区域
    QRect rectLeftTop;              // 左上侧区域
    QRect rectRightTop;             // 右上侧区域
    QRect rectLeftBottom;           // 左下侧区域
    QRect rectRightBottom;          // 右下侧区域
    QRect preRect;                  // 修改前区域
    bool pressedLeft;               // 鼠标按下左侧
    bool pressedRight;              // 鼠标按下右侧
    bool pressedTop;                // 鼠标按下上侧
    bool pressedBottom;             // 鼠标按下下侧
    bool pressedLeftTop;            // 鼠标按下左上侧
    bool pressedRightTop;           // 鼠标按下右上侧
    bool pressedLeftBottom;         // 鼠标按下左下侧
    bool pressedRightBottom;        // 鼠标按下右下侧
};

HE_CONTROL_END_NAMESPACE

#endif // HRESIZEEVENTFILTER_P_H
