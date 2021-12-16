#pragma once

#include "HEffectRenderer.h"

HE_BEGIN_NAMESPACE

class HOpenGLTexture2D;

class HEffectRendererPrivate
{
public:
    HOpenGLShaderProgram *shader = nullptr;
    HOpenGLTexture2D *texture = nullptr;
    int width = 0;
    int height = 0;
    bool confuse = false;
    bool chaos = false;
    bool shake = false;
    float shakeTime = 0.0f;
    unsigned int vao;
    unsigned int fbo1;
    unsigned int fbo2;
    unsigned int rbo;
};

HE_END_NAMESPACE

