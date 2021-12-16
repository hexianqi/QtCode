#pragma once

#include "HTextRenderer.h"

HE_BEGIN_NAMESPACE

class HFreeType;

class HTextRendererPrivate
{
public:
    HOpenGLShaderProgram *shader = nullptr;
    HFreeType *freeType = nullptr;
};

HE_END_NAMESPACE

