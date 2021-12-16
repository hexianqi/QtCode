#pragma once

#include "HGeometryEngine.h"

HE_BEGIN_NAMESPACE

class HGeometryEnginePrivate
{
public:
    unsigned int triangleVao = 0;
    unsigned int rectVao = 0;
    unsigned int screenVao = 0;
    unsigned int planeVao = 0;
    unsigned int quadVao = 0;
    unsigned int cubeVao = 0;
    unsigned int sphereVao = 0;
    unsigned int skyboxVao = 0;
};

HE_END_NAMESPACE

