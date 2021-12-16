/***************************************************************************************************
**      2020-11-09  IShaderEngine   渲染引擎接口
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class HGeometryEngine;
class HGeometryEnginePrivate;

class IShaderEngine : public IInitializeable
{
public:
    virtual void setData(QVariantMap value) = 0;
    virtual void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE
