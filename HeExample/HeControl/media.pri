HEADERS += \
    $$PWD/HMediaPlayer.h \
    $$PWD/HMediaPlayer_p.h

SOURCES += \
    $$PWD/HMediaPlayer.cpp

include(ffplayer.pri)
include(ffmpeg.pri)
include(sdl.pri)
include(vlc.pri)

