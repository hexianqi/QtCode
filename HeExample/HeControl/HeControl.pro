#-------------------------------------------------
#
# Project created by QtCreator 2019-06-04T14:52:21
#
#-------------------------------------------------

QT          += widgets serialport network

TEMPLATE    = lib

DESTDIR     = "../../Dest"

DEFINES     += HE_BUILD_CONTROL_LIB

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
            HControlHelper.cpp \
            HControlTester.cpp

HEADERS     += \
            HControlGlobal.h \
            HControlHelper.h \
            HControlTester.h

RESOURCES   = HeControl.qrc

INCLUDEPATH += \
            ../..

Debug {
    TARGET = HeControld
    LIBS    += \
            -L$$DESTDIR -lHeCored
}

Release {
    TARGET  = HeControl
    LIBS    += \
            -L$$DESTDIR -lHeCore \
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(event.pri)
include(table.pri)
include(tools.pri)
include(layout.pri)
