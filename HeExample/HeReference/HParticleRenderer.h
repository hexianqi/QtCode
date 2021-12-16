/***************************************************************************************************
**      2020-12-10  HParticleRenderer
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HOpenGLShaderProgram;
class HOpenGLTexture2D;
class HGameObject;
class HParticleRendererPrivate;

class HParticleRenderer : public QObject
{
    Q_OBJECT

public:
    explicit HParticleRenderer(HOpenGLShaderProgram *shader, int amount, QObject *parent = nullptr);
    ~HParticleRenderer() override;

public:
    void setTexture(HOpenGLTexture2D *);

public:
    void update(float dt);
    void respawn(HGameObject *, int amount = 1);
    void draw();

protected:
    void init(int amount);

protected:
    QScopedPointer<HParticleRendererPrivate> d_ptr;
};

HE_END_NAMESPACE

