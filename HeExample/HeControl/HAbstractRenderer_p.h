#pragma once

#include "HAbstractRenderer.h"
#include <QtGui/QOpenGLVertexArrayObject>

class QOpenGLFunctions;

HE_BEGIN_NAMESPACE

class HAbstractRendererPrivate
{
public:
    HAbstractRendererPrivate();

public:
    QOpenGLFunctions *funcs;
    QOpenGLShaderProgram *shader = nullptr;
    QOpenGLVertexArrayObject vao;
};

HE_END_NAMESPACE

