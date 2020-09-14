#pragma once

#include "HLearnGLFW.h"
#include "HOpenGLCamera.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <QtGui/QVector3D>

HE_REFERENCE_BEGIN_NAMESPACE

class HLearnGLFWPrivate
{
public:
    GLFWwindow *window = nullptr;
};

// camera
extern QVector3D cameraPos;
extern QVector3D cameraFront;
extern QVector3D cameraUp;
// timing
extern float deltaTime;
extern float lastFrame;

extern bool firstMouse;
extern float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
extern float pitch;
extern float lastX;
extern float lastY;
extern float fov;

extern HOpenGLCamera *camera;

HE_REFERENCE_END_NAMESPACE
