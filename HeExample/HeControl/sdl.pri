HEADERS += \
    $$PWD/HSDLControl.h \
    $$PWD/HSDLControl_p.h

SOURCES += \
    $$PWD/HSDLControl.cpp


SDLPath     = $$absolute_path("../../../modules/SDL2/win32", $$[QT_INSTALL_DATA])

LIBS        += -L$$SDLPath/lib -lSDL2

INCLUDEPATH += $$SDLPath/include
DEPENDPATH  += $$SDLPath/include

# 复制动态库
#win32 {
#    src_file = $$FFmpegPath/bin/*
#    dst_file = $$OUT_PWD
#    target_file = $$DESTDIR
#    src_file ~= s,/,\\,g
#    dst_file ~= s,/,\\,g
#    target_file ~= s,/,\\,g
#    system(xcopy $$src_file $$dst_file /y /s/q/e)
#    system(xcopy $$src_file $$target_file /y /s/q/e)
#}
