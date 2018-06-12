#-------------------------------------------------
#
# Project created by QtCreator 2018-04-08T14:14:48
#
#-------------------------------------------------

QT          += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE    = app

CONFIG      += c++11

TARGET      = HeTest

DESTDIR     = "../Dest"

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
            main.cpp \
            MainWindow.cpp

HEADERS     += \
            MainWindow.h

FORMS       += \
            MainWindow.ui

RESOURCES   += \
            HeTest.qrc

INCLUDEPATH += ".."

Debug {
    CONFIG  += console
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithmd \
            -L$$DESTDIR -lHePlugind
}

Release {
    LIBS    += \
            -L$$DESTDIR -lHeAlgorithm \
            -L$$DESTDIR -lHePlugin
}





#LIBS    += \
#        -LD:/Qt/gsl-1.8/lib/ -lgsl \
#        -LD:/Qt/gsl-1.8/lib/ -lgslcblas

#INCLUDEPATH += D:/Qt/gsl-1.8/include
#DEPENDPATH += D:/Qt/gsl-1.8/include
