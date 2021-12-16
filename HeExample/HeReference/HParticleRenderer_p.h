#pragma once

#include "HParticleRenderer.h"
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

class HParticleRendererPrivate
{
public:
    HParticle *unusedParticle();

public:
    HOpenGLShaderProgram *shader = nullptr;
    HOpenGLTexture2D *texture = nullptr;
    unsigned int vao = 0;
    int lastUsed = 0;
    QVector<HParticle *> particles;
};

HE_END_NAMESPACE

