#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T10:35:38
#
#-------------------------------------------------

QT          += widgets

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

#TRANSLATIONS = HeData_en.ts

DEFINES     += HE_BUILD_DATA_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS     += \
            IDataFactory.h \
            IConfigManage.h \
            IDataItem.h \
            IDataCollection.h \
            HDataGlobal.h \
            HDataFactory.h \
            HDataFactory_p.h \
            HConfigManage.h \
            HConfigManage_p.h \
            HAbstractDataItem.h \
            HAbstractDataItem_p.h \
            HDataHelper.h \
            HDataCollection.h \
            HDataType.h

SOURCES     += \
            HDataFactory.cpp \
            HConfigManage.cpp \
            HAbstractDataItem.cpp \
            HDataHelper.cpp

RESOURCES   = HeData.qrc

INCLUDEPATH += ..

Debug {
    TARGET = HeDatad
    LIBS    += \
            -L$$DESTDIR -lHeCored \
            -L$$DESTDIR -lHeAlgorithmd
}

Release {
    TARGET  = HeData
    LIBS    += \
            -L$$DESTDIR -lHeCore \
            -L$$DESTDIR -lHeAlgorithm
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(adjust.pri)
include(chromatism.pri)
include(elec.pri)
include(grade.pri)
include(luminous.pri)
include(quality.pri)
include(spec.pri)
include(stream.pri)
include(test.pri)
