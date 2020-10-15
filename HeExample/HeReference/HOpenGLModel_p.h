#pragma once

#include "HOpenGLModel.h"
#include <QtCore/QVector>
#include <QtCore/QHash>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLModelPrivate
{
public:
    QString directory;
    QVector<HOpenGLMesh *> meshes;
    QHash<QString, Texture> textureCache;
};

HE_REFERENCE_END_NAMESPACE

