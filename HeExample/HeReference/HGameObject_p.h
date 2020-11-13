#pragma once

#include "HGameObject.h"
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HGameObjectPrivate
{
public:
    QVector2D position = QVector2D(0.0, 0.0);
    QVector2D size = QVector2D(10.0, 10.0);
    float rotate = 0.0f;
    QVector3D color = QVector3D(1.0, 1.0, 1.0);
    HOpenGLTexture2D *texture = nullptr;
    QVector2D velocity = QVector2D(0.0, 0.0);
};

HE_REFERENCE_END_NAMESPACE

