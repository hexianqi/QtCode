#pragma once

#include "HSpriteRenderer.h"

HE_REFERENCE_BEGIN_NAMESPACE

class HSpriteRendererPrivate
{
public:
    HOpenGLShaderProgram *shader = nullptr;
    unsigned int vao = 0;
};

HE_REFERENCE_END_NAMESPACE

