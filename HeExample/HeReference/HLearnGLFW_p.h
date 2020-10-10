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
    QVector<float> cubePosition;                // cube positions
    QVector<float> cubeTexture;                 // cube texture
    QVector<float> cubeNormal;                  // cube normal
    QList<QVector3D> cubeWorldPosition;         // cube world space positions
    QVector<float> planePosition;               // plane positions
    QVector<float> planeTexture;                // plane texture
    QVector<float> transparentPosition;         // transparent positions
    QVector<float> transparentTexture;          // transparent texture
    QVector<float> skyboxPosition;              // skybox positions
    int cubePositionSize = 0;
    int cubeTextureSize = 0;
    int cubeNormalSize = 0;
    int planePositionSize = 0;
    int planeTextureSize = 0;
    int transparentPositionSize = 0;
    int transparentTextureSize = 0;
    int skyboxPositionSize = 0;
};

// camera
extern QVector3D cameraPos;
extern QVector3D cameraFront;
extern QVector3D cameraUp;
extern float fov;
// camera2
extern HOpenGLCamera *camera;

HE_REFERENCE_END_NAMESPACE
