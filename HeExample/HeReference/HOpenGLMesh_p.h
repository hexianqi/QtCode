#pragma once

#include "HOpenGLMesh.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HOpenGLMeshPrivate
{
public:
    void setup();

public:
    QVector<Vertex>       vertices;
    QVector<unsigned int> indices;
    QVector<Texture>      textures;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};

HE_END_NAMESPACE

