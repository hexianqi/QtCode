#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T09:26:40
#
#-------------------------------------------------

QT          += core

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

DEFINES     += HE_BUILD_CONTROLLER_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES     += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES     +=

HEADERS     += \
            HControllerGlobal.h

INCLUDEPATH += ".."

Debug {
    TARGET = HeControllerd
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeCommunicated

}

Release {
    TARGET  = HeController
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeCommunicate
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(Thread.pri)
include(Model.pri)
include(Test.pri)
