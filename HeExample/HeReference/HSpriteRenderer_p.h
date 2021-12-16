#pragma once

#include "HSpriteRenderer.h"

HE_BEGIN_NAMESPACE

class HSpriteRendererPrivate
{
public:
    HOpenGLShaderProgram *shader = nullptr;
    unsigned int vao = 0;
};

HE_END_NAMESPACE

