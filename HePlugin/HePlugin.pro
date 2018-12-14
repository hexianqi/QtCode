QT          += designer charts

CONFIG      += plugin debug_and_release

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

SOURCES     += \
            class2Plugin.cpp \
            HCollectionInterface.cpp \
            HePluginHelper.cpp

HEADERS     += \
            class2Plugin.h \
            HCollectionInterface.h \
            HPluginHelper.h

RESOURCES   = HePlugin.qrc

INCLUDEPATH += ..

Debug {
    TARGET  = HePlugind
    LIBS    += -L$$DESTDIR -lHeAlgorithmd
}

Release {
    TARGET  = HePlugin
    LIBS    += -L$$DESTDIR -lHeAlgorithm
}

include(strategy.pri)
include(extend.pri)
include(chart.pri)
include(view.pri)
include(diagram.pri)
include(class2.pri)
