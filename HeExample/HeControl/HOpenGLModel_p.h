#pragma once

#include "HOpenGLModel.h"
#include <QtCore/QVector>
#include <QtCore/QHash>

class QOpenGLFunctions;

HE_BEGIN_NAMESPACE

class HOpenGLModelPrivate
{
public:
    HOpenGLModelPrivate();

public:
    QString directory;
    QVector<HOpenGLMesh *> meshes;
    QHash<QString, QOpenGLTexture *> textures;
};

HE_END_NAMESPACE

