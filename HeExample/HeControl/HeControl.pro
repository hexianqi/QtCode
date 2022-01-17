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
            HControlGlobal.h \
            HControlType.h \
            IControlFactory.h \
            HControlFactory.h \
            HControlFactory_p.h

RESOURCES   = \
            HeControl.qrc \
            qss.qrc

INCLUDEPATH += ../..

Debug {
    TARGET = HeControld
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeFiled \
            -L$$DESTDIR -lHePlugind
}

Release {
    TARGET  = HeControl
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeFile \
            -L$$DESTDIR -lHePlugin
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(_canpool.pri)
include(_liudianwu.pri)
include(_ww.pri)
include(event.pri)
include(helper.pri)
include(iconFont.pri)
include(layout.pri)
include(media.pri)
include(multimedia.pri)
include(network.pri)
include(openGL.pri)
include(service.pri)
include(sql.pri)
include(style.pri)
include(test.pri)
include(tools.pri)
include(widget.pri)
include($$[QT_INSTALL_PREFIX]/../Src/qttools/src/shared/qtpropertybrowser/qtpropertybrowser.pri)

include(z_demo.pri)
include(z_widget.pri)

