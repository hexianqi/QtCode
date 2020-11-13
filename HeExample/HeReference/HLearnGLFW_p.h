#pragma once

#include "HLearnGLFW.h"
#include "HOpenGLCamera.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HGeometryEngine;

class HLearnGLFWPrivate
{
public:
    HLearnGLFWPrivate();

public:
    bool lightPosLoop = false;
    bool lightColorLoop = false;
    bool enableCursor = true;
    bool lineMode = false;

public:
    HGeometryEngine *engine = nullptr;
    GLFWwindow *window = nullptr;
    int width = 800;
    int height = 600;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:
    bool blinn = false;
    bool bloom = true;
    bool gamma = false;
    bool linearize = false;
    bool shadows = false;
    bool hdr = true;
    float heightScale = 0.1;
    float exposure = 1.0f;
    bool keyPressed_B = false;
    bool keyPressed_G = false;
    bool keyPressed_L = false;
    bool keyPressed_H = false;

public:
    QMap<int, QVector3D> attenuations;
    QVector3D lightPos = QVector3D(1.2f, 1.0f, 2.0f);
    QVector3D lightColor = QVector3D(1.0f, 1.0f, 1.0f);
    QList<QVector3D> cubeWorldPosition;                 // cube world space positions
};

extern HOpenGLCamera *camera;

HE_REFERENCE_END_NAMESPACE
