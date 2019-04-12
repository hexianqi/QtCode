#-------------------------------------------------
#
# Project created by QtCreator 2019-04-12T08:56:39
#
#-------------------------------------------------

QT          += widgets sql

TEMPLATE    = lib

CONFIG      += c++11

DESTDIR     = "../Dest"

DEFINES     += HE_BUILD_SQL_LIB

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
            HSqlGlobal.h \
            HSql.h \
            HSqlGlobalInstance.h \
            HSqlHelper.h \
    ISqlFactory.h \
    HSqlFactory.h \
    HSqlFactory_p.h \
    ISqlDatabase.h \
    HSqlDatabase.h \
    HSqlDatabase_p.h \
    ISqlTableModel.h


SOURCES     += \
            HSql.cpp \
            HSqlGlobalInstance.cpp \
            HSqlHelper.cpp \
    HSqlFactory.cpp \
    HSqlDatabase.cpp

INCLUDEPATH += ..

Debug {
    TARGET = HeSqld
    LIBS    += -L$$DESTDIR -lHeCored

}

Release {
    TARGET  = HeSql
    LIBS    += -L$$DESTDIR -lHeCore
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
