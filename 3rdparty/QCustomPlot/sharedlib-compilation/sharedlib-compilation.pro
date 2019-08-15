#
#  Project to compile QCustomPlot as shared library (.so/.dll) from the amalgamated sources
#

QT          += widgets printsupport

TEMPLATE    = lib

DESTDIR     = "../../../Dest"

DEFINES     += QCUSTOMPLOT_COMPILE_LIBRARY

#CONFIG      += debug_and_release build_all
static {
  CONFIG += static
} else {
  CONFIG += shared
}

SOURCES     += ../qcustomplot.cpp
HEADERS     += ../qcustomplot.h

VERSION = 2.0.1

Debug {
    TARGET = qcustomplotd
    QMAKE_TARGET_PRODUCT = "QCustomPlot (debug mode)"
    QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt (debug mode)"
}

Release {
    TARGET  = qcustomplot
    QMAKE_TARGET_PRODUCT = "QCustomPlot"
    QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt"
}

QMAKE_TARGET_COMPANY = "www.qcustomplot.com"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) by Emanuel Eichhammer"
