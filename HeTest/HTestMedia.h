#pragma once

#include <QtCore/qglobal.h>

class HTestMedia
{
public:
    static bool videoPlayer(QString fileName, bool output = true);
    static bool videoPlayer_SU(QString fileName);
    static bool audioPlayer(QString fileName, bool output = true);
    static bool yuv2jpg(QString iFileName, QString oFileName);
    static bool videoEncoder(QString iFileName, QString oFileName);
    static bool audioEncoder(QString iFileName, QString oFileName);
    static bool remuxer(QString iFileName, QString oFileName);
    static bool demuxer(QString iFileName, QString oFileNameV, QString oFileNameA);
    static bool muxer(QString iFileNameV, QString iFileNameA, QString oFileName);
    static bool streamer(QString iFileName, QString oFileName);
    static bool receiver(QString iFileName, QString oFileName);
    static bool videoFilter(QString fileName, QString filters);
    static bool videoScale(QString iFileName, QString oFileName);
    static bool grabDesktop();
    static bool readCamera();
    static bool memPlayer(QString fileName);

    static bool videoPlayer_vlc(QString fileName);
};

