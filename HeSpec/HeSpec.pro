#-------------------------------------------------
#
# Project created by QtCreator 2019-03-20T14:11:56
#
#-------------------------------------------------

QT       += core gui widgets

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG  += c++11

DESTDIR = "../Dest"

SOURCES += \
        main.cpp \
        HMainWindowSpec.cpp \
        HBuilderSpec.cpp \
        HModelSpec.cpp \
        HTestWidgetSpec.cpp

HEADERS += \
        HMainWindowSpec.h \
        HMainWindowSpec_p.h \
        HBuilderSpec.h \
        HBuilderSpec_p.h \
        HModelSpec.h \
        HModelSpec_p.h \
        HTestWidgetSpec.h \
        HTestWidgetSpec_p.h

FORMS   += \
        HTestWidgetSpec.ui

TARGET = HeSpec

INCLUDEPATH += ..

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
