#-------------------------------------------------
#
# Project created by QtCreator 2018-04-08T14:14:48
#
#-------------------------------------------------

QT          += core gui charts widgets opengl sql

TEMPLATE    = app

CONFIG      += c++11

TARGET      = HeTest

DESTDIR     = "../Dest"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES     += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES     += \
            HTestCore.cpp \
            HTestDir.cpp \
            HTestEigen.cpp \
            HTestMedia_ff.cpp \
            HTestMedia_vlc.cpp \
            HTestOpenGL.cpp \
            HTestSql.cpp \
            main.cpp \
            MainWindow.cpp \
            HTestAlgorithm.cpp \
            HTestPlugin.cpp \
            HTestGsl.cpp \
            HTestData.cpp \

HEADERS     += \
            HTestCore.h \
            HTestDir.h \
            HTestEigen.h \
            HTestMedia.h \
            HTestOpenGL.h \
            HTestSql.h \
            MainWindow.h \
            HTestAlgorithm.h \
            HTestPlugin.h \
            HTestGsl.h \
            HTestData.h

FORMS       += \
            MainWindow.ui

RESOURCES   += \
            HeTest.qrc

GslPath     = $$absolute_path("../../../modules/gsl/win32", $$[QT_INSTALL_DATA])
FFmpegPath  = $$absolute_path("../../../modules/ffmpeg/win32", $$[QT_INSTALL_DATA])
SDLPath     = $$absolute_path("../../../modules/SDL2/win32", $$[QT_INSTALL_DATA])
VLCPath     = $$absolute_path("../../../modules/vlc/win32", $$[QT_INSTALL_DATA])
EigenPath   = $$absolute_path("../../../modules/eigen3", $$[QT_INSTALL_DATA])

INCLUDEPATH += \
            .. \
            ../HeExample \
            $$GslPath/include \
            $$FFmpegPath/include \
            $$SDLPath/include \
            $$VLCPath/include \
            $$EigenPath/include

Debug {
#    CONFIG  += console
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithmd \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHePlugind \
            -L$$DESTDIR -lHeControld \
            -L$$DESTDIR -lHeReferenced \
            -L$$FFmpegPath/lib -lavcodec -lavdevice -lavfilter -lavformat -lavutil -lswresample -lswscale \
            -L$$SDLPath/lib -lSDL2 \
            -L$$VLCPath/lib -lvlccore -lvlc
}

Release {
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithm \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHePlugin \
            -L$$DESTDIR -lHeControl
}

#版本信息
VERSION                     = 1.0.1.1
# 图标
RC_ICONS                    = Image/Icon.ico
# 中文（简体）
RC_LANG                     = 0x0004
# 公司名称
QMAKE_TARGET_COMPANY        = "Digia"
# 产品名称
QMAKE_TARGET_PRODUCT        = "Qt Creator"
# 文件说明
QMAKE_TARGET_DESCRIPTION    = "Qt Creator based on Qt 5.7.0 (MSVC 2013, 32 bit)"
# 版权信息
QMAKE_TARGET_COPYRIGHT      = "Copyright 2008-2016 The Qt Company Ltd. All rights reserved."
