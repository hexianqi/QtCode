#pragma once

#include "HMultColorBars.h"

class HMultColorBarsPrivate
{
public:
    HMultColorBarsPrivate();

public:
    bool labelVisible = true;                           // 标签可视
    Qt::Alignment labelAlignment = Qt::AlignCenter;     // 标签对齐方式
    double labelSpace = 5.0;                            // 标签与柱状图的间距，这里按像素大小
    QFont labelFont;                                    // 标签字体
};



