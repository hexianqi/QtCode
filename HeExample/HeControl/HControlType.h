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
        PointerStyle_Circle = 0,        // 圆形指示器
        PointerStyle_Indicator = 1,     // 指针指示器
        PointerStyle_IndicatorR = 2,    // 圆角指针指示器
        PointerStyle_Triangle = 3       // 三角形指示器
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
