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
    float moveSpeed = 25.f;
    float sensitivity = 0.1f;
    float zoom = 45.0f;
    bool firstMouse = true;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
};

HE_REFERENCE_END_NAMESPACE

