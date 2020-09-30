HEADERS += \
    $$PWD/HAbstractStream.h \
    $$PWD/HAbstractStream_p.h \
    $$PWD/HDataStream.h \
    $$PWD/HDataStream_p.h \
    $$PWD/HMultStream.h \
    $$PWD/HMultStream_p.h \
    $$PWD/HTextStream.h \
    $$PWD/HTextStream_p.h \
    $$PWD/HXlsxStream.h \
    $$PWD/HXlsxStream_p.h \
    $$PWD/IDataStream.h \
    $$PWD/HStreamHelper.h \
    $$PWD/IMultStream.h \
    $$PWD/IStream.h \
    $$PWD/ITextStream.h \
    $$PWD/IXlsxStream.h

SOURCES += \
    $$PWD/HAbstractStream.cpp \
    $$PWD/HDataStream.cpp \
    $$PWD/HMultStream.cpp \
    $$PWD/HTextStream.cpp \
    $$PWD/HXlsxStream.cpp

QXlsxPath   = $$absolute_path("../../../modules/QXlsx", $$[QT_INSTALL_DATA])

INCLUDEPATH += $$QXlsxPath/include

LIBS        += -L$$QXlsxPath/lib -lQXlsx
