/***************************************************************************************************
**      2019-07-24  IShaderEffect 特效
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

class QPainter;

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IShaderEffect : public IInitializeable
{
public:
    // 绘制
    virtual void draw(QPainter *, double factor, const QRect &rect, const QPixmap &pixmap) = 0;
};

HE_CONTROL_END_NAMESPACE
