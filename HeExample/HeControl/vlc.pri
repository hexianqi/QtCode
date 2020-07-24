#HEADERS += \
#    $$PWD/HSDLControl.h \
#    $$PWD/HSDLControl_p.h

#SOURCES += \
#    $$PWD/HSDLControl.cpp


VLCPath     = $$absolute_path("../../../modules/vlc/win32", $$[QT_INSTALL_DATA])

LIBS        += -L$$VLCPath/lib -lvlccore -lvlc

INCLUDEPATH += $$VLCPath/include
DEPENDPATH  += $$VLCPath/include
