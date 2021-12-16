#pragma once

#include "HTextRenderer.h"
#include "HAbstractRenderer_p.h"

HE_BEGIN_NAMESPACE

class HTextEngine;

class HTextRendererPrivate : public HAbstractRendererPrivate
{
public:
    HTextEngine *engine = nullptr;
};

HE_END_NAMESPACE

