#pragma once

#include "HAbstractShaderEngine.h"
#include <QtCore/QVector>

class QOpenGLShaderProgram;
class QOpenGLExtraFunctions;

HE_BEGIN_NAMESPACE

class HAbstractShaderEnginePrivate
{
public:
    HAbstractShaderEnginePrivate();

public:
    QOpenGLExtraFunctions *funcs;
    bool initialized = false;
    QVector<QOpenGLShaderProgram *> shaders;
    QVector<QOpenGLTexture *> textures;
};

HE_END_NAMESPACE

