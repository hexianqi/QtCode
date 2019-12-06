#-------------------------------------------------
#
# Project created by QtCreator 2018-05-14T09:35:52
#
#-------------------------------------------------

QT          += core gui widgets

TEMPLATE    = app

CONFIG      += c++11

DESTDIR     = "../Dest"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \

INCLUDEPATH += ..

Debug {
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeDatad \
            -L$$DESTDIR -lHeCommunicated \
            -L$$DESTDIR -lHeControllerd \
            -L$$DESTDIR -lHeGuid \
            -L$$DESTDIR -lHePlugind \
            -L$$DESTDIR -lHeSqld
}

Release {
    DEFINES += QT_NO_DEBUG_OUTPUT
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeData \
            -L$$DESTDIR -lHeCommunicate \
            -L$$DESTDIR -lHeController \
            -L$$DESTDIR -lHeGui \
            -L$$DESTDIR -lHePlugin \
            -L$$DESTDIR -lHeSql
}

include(SL2000.pri)
include(SL2000DC.pri)

DEFINES += SL2000DC

if (contains(DEFINES, SL2000)) {
    TARGET_NAME = SL2000
} else : if (contains(DEFINES, SL2000DC)) {
    TARGET_NAME = SL2000DC
} else {
    TARGET_NAME = Test
}

TARGET = $$TARGET_NAME

#版本信息
VERSION = 1.0.0.1
# 图标
RC_ICONS = Image/Icon.ico
# 公司名称
QMAKE_TARGET_COMPANY = "SongLang"
# 产品名称
QMAKE_TARGET_PRODUCT = $$TARGET_NAME
# 文件说明
QMAKE_TARGET_DESCRIPTION = $$TARGET_NAME
# 版权信息
QMAKE_TARGET_COPYRIGHT = "版权所有：2017-2019 保留所有权利。"
# 中文（简体）
RC_LANG = 0x0004
