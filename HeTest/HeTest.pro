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
            MainWindow.cpp \
            HTestAlgorithm.cpp \
    HTestPlugin.cpp \
    HTestChart.cpp \
    HTestGsl.cpp \
    HChartView.cpp

HEADERS     += \
            MainWindow.h \
            HTestAlgorithm.h \
    HTestPlugin.h \
    HTestChart.h \
    HTestGsl.h \
    HChartView.h

FORMS       += \
            MainWindow.ui

RESOURCES   += \
            HeTest.qrc

INCLUDEPATH += .. D:/Qt/gsl/include

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

#版本信息
VERSION = 4.0.2.666
# 图标
RC_ICONS = Image/Icon.ico
# 公司名称
QMAKE_TARGET_COMPANY = "Digia"
# 产品名称
QMAKE_TARGET_PRODUCT = "Qt Creator"
# 文件说明
QMAKE_TARGET_DESCRIPTION = "Qt Creator based on Qt 5.7.0 (MSVC 2013, 32 bit)"
# 版权信息
QMAKE_TARGET_COPYRIGHT = "Copyright 2008-2016 The Qt Company Ltd. All rights reserved."
# 中文（简体）
RC_LANG = 0x0004
