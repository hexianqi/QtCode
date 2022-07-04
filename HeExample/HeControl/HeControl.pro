#-------------------------------------------------
#
# Project created by QtCreator 2019-06-04T14:52:21
#
#-------------------------------------------------

QT          += widgets serialport network xml svg concurrent sql

CONFIG      += resources_big warn_off

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
            HControlFactory.cpp

HEADERS     += \
            IControlFactory.h \
            HControlGlobal.h \
            HControlType.h \
            HControlFactory.h \
            HControlFactory_p.h

RESOURCES   = \
            HeControl.qrc \
            Resources.qrc \
            qss.qrc

INCLUDEPATH += ../..

Debug {
    TARGET = HeControld
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHePlugind
}

Release {
    TARGET  = HeControl
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHePlugin
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(_liudianwu.pri)
include(helper.pri)
include(media.pri)
include(multimedia.pri)
include(network.pri)
include(openGL.pri)
include(sql.pri)
include(style.pri)
include(test.pri)
include(tools.pri)
include(widget.pri)


include(z_demo.pri)
include(z_event.pri)
include(z_fyqy.pri)
include(z_helper.pri)
include(z_iconFont.pri)
include(z_layout.pri)
include(z_network.pri)
include(z_service.pri)
include(z_tool.pri)
include(z_style.pri)
include(z_widget.pri)
include(z_ww.pri)
