#pragma once

#include "HOpenGLCamera.h"
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLCameraPrivate
{
public:
    // camera Attributes
    QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D front = QVector3D(0.0f, 0.0f, -1.0f);
    QVector3D up;
    QVector3D right;
    QVector3D worldUp = QVector3D(0.0f, 1.0f,  0.0f);
    // euler Angles
    float yaw = -90.0f;
    float pitch = 0.0f;
    // camera options
    float movementSpeed = 25.f;
    float mouseSensitivity = 0.1f;
    float zoom = 15.0f;
};

HE_REFERENCE_END_NAMESPACE

