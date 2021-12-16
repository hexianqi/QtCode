#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T09:26:40
#
#-------------------------------------------------

#QT          += core gui

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

TRANSLATIONS = HeController_en.ts

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

HEADERS     += \
            HControllerGlobal.h \
            IControllerFactory.h \
            HControllerFactory.h \
            HControllerFactory_p.h

SOURCES     += \
            HControllerFactory.cpp

INCLUDEPATH += ..

Debug {
    TARGET = HeControllerd
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeCommunicated \
            -L$$DESTDIR -lHeDatad
}

Release {
    TARGET  = HeController
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeCommunicate \
            -L$$DESTDIR -lHeData
}

include(memento.pri)
include(model.pri)
include(thread.pri)
include(strategy.pri)
