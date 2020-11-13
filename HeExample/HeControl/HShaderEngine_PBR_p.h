#pragma once

#include "HShaderEngine_PBR.h"
#include "HAbstractShaderEngine_p.h"
#include <QtGui/QVector3D>

HE_CONTROL_BEGIN_NAMESPACE

class HShaderEngine_PBRPrivate : public HAbstractShaderEnginePrivate
{
public:
    HShaderEngine_PBRPrivate();

public:
    QVector<QVector3D> lightPosition;
    QVector<QVector3D> lightColor;
};

class HShaderEngine_PBR2Private : public HAbstractShaderEnginePrivate
{
public:
    QVector3D lightPosition = QVector3D(0.0f, 0.0f, 10.0f);
    QVector3D lightColor = QVector3D(150.0f, 150.0f, 150.0f);
};

class HShaderEngine_PBR3Private : public HShaderEngine_PBRPrivate
{
public:
    QOpenGLTexture *envCubemap = nullptr;
};

class HShaderEngine_PBR4Private : public HShaderEngine_PBR3Private
{
public:
    QOpenGLTexture *irradianceCubemap = nullptr;
};

class HShaderEngine_PBR5Private : public HShaderEngine_PBR4Private
{
public:
    QOpenGLTexture *prefilterCubemap = nullptr;
    QOpenGLTexture *brdfTexture = nullptr;
};

class HShaderEngine_PBR6Private : public HShaderEngine_PBR5Private
{
public:
    HShaderEngine_PBR6Private();

public:
    QHash<QString, QList<QOpenGLTexture *>> sphereTexture;
    QHash<QString, QVector3D> spherePosition;
};

HE_CONTROL_END_NAMESPACE

