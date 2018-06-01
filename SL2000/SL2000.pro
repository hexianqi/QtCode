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
        HBuilder2000.cpp \
        HModel2000.cpp \
        HMainWindow2000.cpp \


HEADERS += \
        HBuilder2000.h \
        HBuilder2000_p.h \
        HModel2000.h \
        HModel2000_p.h \
        HMainWindow2000.h \
        HMainWindow2000_p.h \

TARGET = SL2000

INCLUDEPATH += ".."

Debug {
    CONFIG  += console
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeDatad \
            -L$$DESTDIR -lHeCommunicated \
            -L$$DESTDIR -lHeControllerd \
            -L$$DESTDIR -lHeGuid
}

Release {
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeData \
            -L$$DESTDIR -lHeCommunicate \
            -L$$DESTDIR -lHeController \
            -L$$DESTDIR -lHeGui
}
