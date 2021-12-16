#pragma once

#include "HOpenGLModel.h"
#include <QtCore/QVector>
#include <QtCore/QHash>

HE_BEGIN_NAMESPACE

class HOpenGLModelPrivate
{
public:
    QString directory;
    QVector<HOpenGLMesh *> meshes;
    QHash<QString, Texture> textures;
};

HE_END_NAMESPACE

