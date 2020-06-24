#pragma once

#include <QtCore/qglobal.h>

class HTestMedia
{
public:
    static bool videoPlayer(QString fileName, bool output = true);
    static bool videoPlayer_SU(QString fileName);
    static bool audioPlayer(QString fileName, bool output = true);
    static bool yuv2jpg(QString inFileName, QString outFileName);
    static bool videoEncoder(QString inFileName, QString outFileName);
    static bool audioEncoder(QString inFileName, QString outFileName);
};

