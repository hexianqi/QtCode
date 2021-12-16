/***************************************************************************************************
**      2019-07-24  IShaderEffect 特效
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

class QPainter;

HE_BEGIN_NAMESPACE

class IShaderEffect : public IInitializeable
{
public:
    // 绘制
    virtual void draw(QPainter *, double factor, const QRect &rect, const QPixmap &pixmap) = 0;
};

HE_END_NAMESPACE
