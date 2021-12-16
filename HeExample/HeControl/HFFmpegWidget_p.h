#pragma once

#include "HFFmpegWidget.h"

HE_BEGIN_NAMESPACE

class HFFmpegThread;

class HFFmpegWidgetPrivate
{
public:
    HFFmpegThread *ffmpeg;
    QImage image;
};

HE_END_NAMESPACE

