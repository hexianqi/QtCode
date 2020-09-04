#pragma once

#include "HOpenGLWidget_1.h"

HE_REFERENCE_BEGIN_NAMESPACE

class HOpenGLWidget_1Private
{
public:
    int tri = 0;
    int quad = 0;
    QTimer *timer = nullptr;
};

HE_REFERENCE_END_NAMESPACE

