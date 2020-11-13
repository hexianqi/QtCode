/***************************************************************************************************
**      2020-12-16  HEffectRenderer
***************************************************************************************************/

#pragma once

#include "HAbstractRenderer.h"

HE_CONTROL_BEGIN_NAMESPACE

class HEffectRendererPrivate;

class HEffectRenderer : public HAbstractRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HEffectRenderer)

public:
    explicit HEffectRenderer(int width, int height, QOpenGLShaderProgram *, QObject *parent = nullptr);
    ~HEffectRenderer() override;

public:
    void setConfuse(bool b);
    void setChaos(bool b);
    void setShakeTime(float);
    void updateShake(float);
    void reset();

public:
    void begin();
    void end();
    void draw();

private:
    void init(int width, int height);
};

HE_CONTROL_END_NAMESPACE

