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

Debug {
    TARGET = HePlugind
}

Release {
    TARGET  = HePlugin
}

include(domain.pri)
include(strategy.pri)
include(chart.pri)
include(diagram.pri)
include(class2.pri)
