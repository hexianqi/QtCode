HEADERS += \
    $$PWD/HVlcPlayer.h \
    $$PWD/HVlcPlayerControl.h \
    $$PWD/HVlcPlayerControl_p.h \
    $$PWD/HVlcPlayer_p.h

SOURCES += \
    $$PWD/HVlcPlayer.cpp \
    $$PWD/HVlcPlayerControl.cpp

FORMS += \
    $$PWD/HVlcPlayer.ui

VLCPath     = $$absolute_path("../../../modules/vlc/win32", $$[QT_INSTALL_DATA])

LIBS        += -L$$VLCPath/lib -lvlccore -lvlc

INCLUDEPATH += $$VLCPath/include
DEPENDPATH  += $$VLCPath/include
