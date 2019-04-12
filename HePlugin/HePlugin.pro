QT          += designer charts

CONFIG      += plugin

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

SOURCES     += \
            class2Plugin.cpp \
            HCollectionInterface.cpp \
            HPluginHelper.cpp \

HEADERS     += \
            class2Plugin.h \
            HCollectionInterface.h \
            HPluginHelper.h

RESOURCES   = HePlugin.qrc

INCLUDEPATH += ..

Debug {
    TARGET  = HePlugind
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithmd \
            -L$$DESTDIR -lHeCored
}

Release {
    TARGET  = HePlugin
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithm \
            -L$$DESTDIR -lHeCore
}

include(chart.pri)
include(chartView.pri)
include(delegate.pri)
include(diagram.pri)
include(dialog.pri)
include(extend.pri)
include(graphics.pri)
include(promotion.pri)
include(strategy.pri)
include(table.pri)
include(widget.pri)

include(class2.pri)


