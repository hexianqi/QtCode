#pragma once

#include "HBreakout.h"
#include "glad/glad.h"

HE_BEGIN_NAMESPACE

class HBreakoutPrivate
{
public:
    GLFWwindow *window = nullptr;
    int width = 800;
    int height = 600;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

HE_END_NAMESPACE

