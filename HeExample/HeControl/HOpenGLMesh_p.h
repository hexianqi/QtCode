#pragma once

#include "HOpenGLMesh.h"
#include <QtCore/QVector>
#include <QtCore/QHash>
#include <QtGui/QOpenGLVertexArrayObject>

class QOpenGLExtraFunctions;

HE_CONTROL_BEGIN_NAMESPACE

class HHOpenGLMeshPrivate
{
public:
    HHOpenGLMeshPrivate();

public:
    void setup();
    void buildTexture(QOpenGLShaderProgram *);

public:
    QOpenGLExtraFunctions *funcs;
    QVector<Vertex>                     vertices;
    QVector<unsigned int>               indices;
    QHash<QString, QOpenGLTexture *>    textures;
    QOpenGLVertexArrayObject vao;
};

HE_CONTROL_END_NAMESPACE

