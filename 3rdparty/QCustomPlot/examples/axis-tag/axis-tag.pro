QT          += widgets printsupport

TEMPLATE    = app

TARGET      = axis-tag

INCLUDEPATH += ../../

SOURCES     += \
            main.cpp \
            mainwindow.cpp \
            axistag.cpp \
            ../../qcustomplot.cpp

HEADERS     += \
            mainwindow.h \
            axistag.h \
            ../../qcustomplot.h

FORMS       += \
            mainwindow.ui
