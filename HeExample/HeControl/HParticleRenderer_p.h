#pragma once

#include "HParticleRenderer.h"
#include "HAbstractRenderer_p.h"
#include <QtCore/QVector>
#include <QtGui/QVector2D>
#include <QtGui/QVector4D>

HE_BEGIN_NAMESPACE

// Represents a single particle and its state
struct HParticle
{
public:
    void update(float dt);
    void respawn(QVector2D position, QVector2D velocity, QVector2D offset = QVector2D());

public:
    QVector2D Position;
    QVector2D Velocity;
    QVector4D Color;
    float     Life = 0.0f;
};

class HParticleRendererPrivate : public HAbstractRendererPrivate
{
public:
    HParticle *unusedParticle();

public:
    int lastUsed = 0;
    QOpenGLTexture *texture = nullptr;
    QVector<HParticle *> particles;
};

HE_END_NAMESPACE

