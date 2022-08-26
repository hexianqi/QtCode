QT          += core gui widgets

CONFIG      += c++11

DESTDIR     = "../../Dest"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES     += \
            HMainWindow.cpp \
            main.cpp

HEADERS     += \
            HMainWindow.h

Debug {
    LIBS    += \
            -L$$DESTDIR -lHeControld \
}

Release {
    LIBS    += \
            -L$$DESTDIR -lHeControl
}

ThirdPath   = $$PWD/../QCustomPlot

INCLUDEPATH += \
            $$ThirdPath \
            ../.. \
            ../../HeExample

include($$ThirdPath/QCustomPlot.pri)
