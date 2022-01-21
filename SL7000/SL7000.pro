QT              += core gui widgets

CONFIG          += c++11

DESTDIR         = "../Dest"

TRANSLATIONS    = SL7000_en.ts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES     += \
            SL7000 \
            SIMULATE


SOURCES     += \
            main.cpp

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

include(SL7000.pri)

TARGET_NAME                 = SL7000

TARGET                      = $$TARGET_NAME
VERSION                     = 1.0.0.1
RC_ICONS                    = Image/Icon.ico
RC_LANG                     = 0x0004
QMAKE_TARGET_COMPANY        = "SongLang"
QMAKE_TARGET_PRODUCT        = $$TARGET_NAME
QMAKE_TARGET_DESCRIPTION    = $$TARGET_NAME
QMAKE_TARGET_COPYRIGHT      = "版权所有：2017-2022 保留所有权利。"
