/***************************************************************************************************
**      2019-07-11
***************************************************************************************************/

#ifndef HCONTROLTYPE_H
#define HCONTROLTYPE_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HControlType : public QObject
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    enum PointerStyle
    {
        PointerStyleCircle = 0,        // 圆形指示器
        PointerStyleIndicator = 1,     // 指针指示器
        PointerStyleIndicatorR = 2,    // 圆角指针指示器
        PointerStyleTriangle = 3       // 三角形指示器
    };
    Q_ENUM(PointerStyle)

    enum Direction4
    {
        Direction4_LeftToRight,
        Direction4_TopToBottom,
        Direction4_RightToLeft,
        Direction4_BottomToTop,
        Direction4_Right = Direction4_LeftToRight,
        Direction4_Down = Direction4_TopToBottom,
        Direction4_Left = Direction4_RightToLeft,
        Direction4_Up = Direction4_BottomToTop
    };
    Q_ENUM(Direction4)
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLTYPE_H
