#pragma once

#include "HRoundShadowWidget.h"

HE_BEGIN_NAMESPACE

class HRoundShadowWidgetPrivate
{
public:
    int padding = 15;
    bool moveEnable = true;
    bool resizeEnable = true;
    QWidget *widget;

//    pressType mousePressType{pressType::NoPressed};


//    int rectX, rectY, rectW, rectH; //窗体坐标+宽高
//    QPoint lastPos;

//    QRect rectRight;
//    QRect rectBottom;
//    QRect rectRightBottom;

};

HE_END_NAMESPACE

