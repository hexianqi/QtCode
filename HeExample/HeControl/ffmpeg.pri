HEADERS += \
    $$PWD/HFFmpeg.h \
    $$PWD/HFFmpegSupportWidget.h \
    $$PWD/HFFmpegSupportWidget_p.h \
    $$PWD/HFFmpegThread.h \     # 参考
    $$PWD/HFFmpegThread_p.h \   # 参考
    $$PWD/HFFmpegUtil.h \
    $$PWD/HFFmpegWidget.h \     # 参考
    $$PWD/HFFmpegWidget_p.h     # 参考

SOURCES += \
    $$PWD/HFFmpegSupportWidget.cpp \
    $$PWD/HFFmpegThread.cpp \   # 参考
    $$PWD/HFFmpegUtil.cpp \
    $$PWD/HFFmpegWidget.cpp     # 参考


FFmpegPath  = $$absolute_path("../../../modules/ffmpeg/win32", $$[QT_INSTALL_DATA])

LIBS        += -L$$FFmpegPath/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale

INCLUDEPATH += $$FFmpegPath/include
DEPENDPATH  += $$FFmpegPath/include

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

FORMS +=
