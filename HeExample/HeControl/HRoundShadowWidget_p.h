#pragma once

#include "HRoundShadowWidget.h"

HE_BEGIN_NAMESPACE

class HRoundShadowWidgetPrivate
{
public:
    HRoundShadowWidget::PressType mousePressType = HRoundShadowWidget::NoPressed;
    int padding = 15;
    bool moveEnable = true;
    bool resizeEnable = true;
    QWidget *widget;
    QPoint lastPos;
    QRect lastGeometry;
    QRect rectRight;
    QRect rectBottom;
    QRect rectRightBottom;


//


//    int rectX, rectY, rectW, rectH; //窗体坐标+宽高
//



};

HE_END_NAMESPACE

