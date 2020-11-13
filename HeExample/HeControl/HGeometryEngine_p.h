#pragma once

#include "HGeometryEngine.h"
#include <QtCore/QHash>
#include <QtGui/QOpenGLVertexArrayObject>

class QOpenGLFunctions;

HE_CONTROL_BEGIN_NAMESPACE

class HOpenGLModel;

class HGeometryEnginePrivate
{
public:
    HGeometryEnginePrivate();

public:
    QOpenGLFunctions *funcs;
    QOpenGLVertexArrayObject triangleVao;
    QOpenGLVertexArrayObject rectVao;
    QOpenGLVertexArrayObject screenVao;
    QOpenGLVertexArrayObject planeVao;
    QOpenGLVertexArrayObject quadVao;
    QOpenGLVertexArrayObject cubeVao;
    QOpenGLVertexArrayObject sphereVao;
    QOpenGLVertexArrayObject skyboxVao;
    QHash<QString, HOpenGLModel *> models;
};

HE_CONTROL_END_NAMESPACE

