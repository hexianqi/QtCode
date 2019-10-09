#-------------------------------------------------
#
# Project created by QtCreator 2019-09-12T08:37:20
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
        HMainWindowDemo.cpp \
        HBuilderDemo.cpp \
        HProtocolDemo.cpp \
        HThreadDemo.cpp \
        HModelDemo.cpp \
        HTestWidgetDemo.cpp \
        HTestSetWidgetDemo.cpp \
        HTestSpecDemo.cpp

HEADERS += \
        HMainWindowDemo.h \
        HMainWindowDemo_p.h \
        HBuilderDemo.h \
        HBuilderDemo_p.h \
        HProtocolDemo.h \
        HProtocolDemo_p.h \
        HThreadDemo.h \
        HThreadDemo_p.h \
        HModelDemo.h \
        HModelDemo_p.h \
        HTestWidgetDemo.h \
        HTestWidgetDemo_p.h \
        HTestSetWidgetDemo.h \
        HTestSetWidgetDemo_p.h \
        HTestSpecDemo.h \
        HTestSpecDemo_p.h

TARGET  = SlProtocolDemo

INCLUDEPATH += ..

Debug {
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeAlgorithmd \
            -L$$DESTDIR -lHeDatad \
            -L$$DESTDIR -lHeCommunicated \
            -L$$DESTDIR -lHeControllerd \
            -L$$DESTDIR -lHeGuid \
            -L$$DESTDIR -lHePlugind
}

Release {
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeAlgorithm \
            -L$$DESTDIR -lHeData \
            -L$$DESTDIR -lHeCommunicate \
            -L$$DESTDIR -lHeController \
            -L$$DESTDIR -lHeGui \
            -L$$DESTDIR -lHePlugin
}

FORMS += \
    HTestSetWidgetDemo.ui
