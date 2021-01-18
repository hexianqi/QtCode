QT          += designer charts

CONFIG      += plugin

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

SOURCES     += \
            class2Plugin.cpp \
            HCollectionInterface.cpp \
            HPluginHelper.cpp \
            HDrawHelper.cpp

HEADERS     += \
            class2Plugin.h \
            HCollectionInterface.h \
            HPluginHelper.h \
            HDrawHelper.h

RESOURCES   = HePlugin.qrc

QXlsxPath   = $$absolute_path("../../../modules/QXlsx", $$[QT_INSTALL_DATA])

INCLUDEPATH += \
            .. \
            $$QXlsxPath/include

Debug {
    TARGET  = HePlugind
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithmd \
            -L$$DESTDIR -lHeCored \
            -L$$QXlsxPath/lib -lQXlsx
}

Release {
    TARGET  = HePlugin
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithm \
            -L$$DESTDIR -lHeCore \
            -L$$QXlsxPath/lib -lQXlsx
}

include(chart.pri)
include(delegate.pri)
include(diagram.pri)
include(graphics.pri)
include(painter.pri)
include(strategy.pri)
include(widget.pri)
include(class2.pri)
