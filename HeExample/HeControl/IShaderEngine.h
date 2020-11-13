/***************************************************************************************************
**      2020-11-09  IShaderEngine   渲染引擎接口
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class HGeometryEngine;
class HGeometryEnginePrivate;

class IShaderEngine : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    virtual void setData(QVariantMap value) = 0;
    virtual void draw(HGeometryEngine *, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE
