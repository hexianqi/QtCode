/***************************************************************************************************
**      2020-12-16  HParticleRenderer
***************************************************************************************************/

#pragma once

#include "HAbstractRenderer.h"

class QOpenGLTexture;

HE_CONTROL_BEGIN_NAMESPACE

class HGameObject;
class HParticleRendererPrivate;

class HParticleRenderer : public HAbstractRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HParticleRenderer)

public:
    explicit HParticleRenderer(int amount, QOpenGLShaderProgram *, QObject *parent = nullptr);
    ~HParticleRenderer() override;

public:
    void setTexture(QOpenGLTexture *);

public:
    void update(float dt);
    void respawn(HGameObject *, int amount = 1);
    void draw();

protected:
    void init(int amount);
};

HE_CONTROL_END_NAMESPACE

