#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T13:10:40
#
#-------------------------------------------------

QT          += core-private

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

DEFINES     += HE_BUILD_EXAMPLE_LIB

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
            HDPointer.cpp

HEADERS     += \
            HExampleGlobal.h \
            HDPointer.h \
            HDPointer_p.h

INCLUDEPATH += ".."

Debug {
    TARGET  = HeExampled
#    LIBS    += -L$$DESTDIR -lHeFiled \
}

Release {
    TARGET  = HeExample
#    LIBS    += -L$$DESTDIR -lHeFile \
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(Reflect.pri)
