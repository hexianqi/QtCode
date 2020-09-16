#pragma once

#include "HLearnGLFW.h"
#include "HOpenGLCamera.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <QtCore/QMap>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HLearnGLFWPrivate
{
public:
    HLearnGLFWPrivate();

public:
    GLFWwindow *window = nullptr;
    bool lightPosLoop = false;
    bool lightColorLoop = false;
    QVector3D lightPos = QVector3D(1.2f, 1.0f, 2.0f);
    QVector3D lightColor = QVector3D(1.0f, 1.0f, 1.0f);
    QList<QVector3D> cubePositions;                     // world space positions of our cubes
    QMap<int, QVector3D> attenuations;
};

// camera
extern QVector3D cameraPos;
extern QVector3D cameraFront;
extern QVector3D cameraUp;
extern float fov;
// camera2
extern HOpenGLCamera *camera;

HE_REFERENCE_END_NAMESPACE
