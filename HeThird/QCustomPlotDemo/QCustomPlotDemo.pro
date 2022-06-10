QT          += core gui widgets

CONFIG      += c++11

DESTDIR     = "../../Dest"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES     += \
            main.cpp \
            MainWindow.cpp

HEADERS     += \
            MainWindow.h

FORMS       += \
            MainWindow.ui

ThirdPath   = $$PWD/../QCustomPlot

INCLUDEPATH += $$ThirdPath

include($$ThirdPath/QCustomPlot.pri)
