HEADERS += \
    $$PWD/IExcelStream.h \
    $$PWD/IFileStream.h \
    $$PWD/HExcelStream.h \
    $$PWD/HExcelStream_p.h \
    $$PWD/HFileStream.h \
    $$PWD/HFileStream_p.h \
    $$PWD/HStreamHelper.h

SOURCES += \
    $$PWD/HExcelStream.cpp \
    $$PWD/HFileStream.cpp

QXlsxPath   = $$absolute_path("../../../modules/QXlsx", $$[QT_INSTALL_DATA])

INCLUDEPATH += $$QXlsxPath/include

LIBS        += -L$$QXlsxPath/lib -lQXlsx
