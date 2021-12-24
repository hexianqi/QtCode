#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T17:01:09
#
#-------------------------------------------------

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

TRANSLATIONS = HeCore_en.ts

DEFINES     += HE_BUILD_CORE_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES     += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS     += \
            HCoreGlobal.h \
            HCore.h \
            HCoreHelper.h \
            HCoreGlobalInstance.h \
            HAppContext.h \
            HDataFormatInfo.h \
            HDataFormatInfo_p.h \
            HCallorHelper.h \
            HDefine.h \
            HDumpTree.h \
            HDumpTree_p.h \
            HException.h \
            HThreadPool.h

SOURCES     += \
            HCore.cpp \
            HCoreHelper.cpp \
            HCoreGlobalInstance.cpp \
            HAppContext.cpp \
            HDataFormatInfo.cpp \
            HDumpTree.cpp \
            HException.cpp \
            HThreadPool.cpp

RESOURCES   += HeCore.qrc

INCLUDEPATH += ..

Debug:      TARGET  = HeCored
Release:    TARGET  = HeCore

include(container.pri)
include(interface.pri)
include(reflect.pri)
include(type.pri)
include(template.pri)
