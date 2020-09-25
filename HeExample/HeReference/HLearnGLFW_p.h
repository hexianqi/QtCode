#pragma once

#include "HLearnGLFW.h"
#include "HOpenGLCamera.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HLearnGLFWPrivate
{
public:
    HLearnGLFWPrivate();

public:
    GLFWwindow *window = nullptr;
    int width = 800;
    int height = 600;
    QMap<int, QVector3D> attenuations;
    bool lightPosLoop = false;
    bool lightColorLoop = false;
    QVector3D lightPos = QVector3D(1.2f, 1.0f, 2.0f);
    QVector3D lightColor = QVector3D(1.0f, 1.0f, 1.0f);
    QVector<float> cubeVertices1;                   // positions
    QVector<float> cubeVertices2;                   // positions + texture coords
    QVector<float> cubeVertices3;                   // positions + normal
    QVector<float> cubeVertices4;                   // positions + normal + texture coords
    QList<QVector3D> cubePositions;                 // world space positions of our cubes
//    QVector<float> planeVertices1;                   // positions
    QVector<float> planeVertices2;                  // positions + texture coords
    QVector<float> transparentVertices2;            // positions + texture coords
    QVector<float> skyboxVertices1;                 // positions


};

// camera
extern QVector3D cameraPos;
extern QVector3D cameraFront;
extern QVector3D cameraUp;
extern float fov;
// camera2
extern HOpenGLCamera *camera;

HE_REFERENCE_END_NAMESPACE
