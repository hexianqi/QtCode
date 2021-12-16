#pragma once

#include "HFFPlayerControl_old.h"
#include "HFFmpeg.h"
#include "SDL2/SDL.h"

HE_BEGIN_NAMESPACE

class HVideoState;
class HSDLControl;

class HFFPlayerControlPrivate
{
public:
    QString url;
    HVideoState *is = nullptr;
    HSDLControl *sdl = nullptr;
};

HE_END_NAMESPACE

