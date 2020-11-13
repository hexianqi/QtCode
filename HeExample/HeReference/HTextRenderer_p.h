#pragma once

#include "HTextRenderer.h"

HE_REFERENCE_BEGIN_NAMESPACE

class HFreeType;

class HTextRendererPrivate
{
public:
    HOpenGLShaderProgram *shader = nullptr;
    HFreeType *freeType = nullptr;
};

HE_REFERENCE_END_NAMESPACE

