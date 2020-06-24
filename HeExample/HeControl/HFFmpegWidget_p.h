#pragma once

#include "HFFmpegWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFFmpegThread;

class HFFmpegWidgetPrivate
{
public:
    HFFmpegThread *ffmpeg;
    QImage image;
};

HE_CONTROL_END_NAMESPACE

