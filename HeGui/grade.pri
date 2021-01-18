HEADERS += \
    $$PWD/HAbstractGradeItemDialog.h \
    $$PWD/HAbstractGradeItemDialog_p.h \
    $$PWD/HAbstractGradeWidget.h \
    $$PWD/HAbstractGradeWidget_p.h \
    $$PWD/HGradeItemDialog.h \
    $$PWD/HGradeItemDialog_p.h \
    $$PWD/HGradeItem2DDialog.h \
    $$PWD/HGradeItem2DDialog_p.h \
    $$PWD/HGradeIsothermDialog.h \
    $$PWD/HGradeIsothermDialog_p.h \
    $$PWD/HGradeEditWidget.h \
    $$PWD/HGradeEditWidget_p.h \
    $$PWD/HParallelGradeWidget.h \
    $$PWD/HParallelGradeWidget_p.h \
    $$PWD/HSequentialGradeWidget.h \
    $$PWD/HSequentialGradeWidget_p.h

SOURCES += \
    $$PWD/HAbstractGradeItemDialog.cpp \
    $$PWD/HAbstractGradeWidget.cpp \
    $$PWD/HGradeItemDialog.cpp \
    $$PWD/HGradeItem2DDialog.cpp \
    $$PWD/HGradeIsothermDialog.cpp \
    $$PWD/HGradeEditWidget.cpp \
    $$PWD/HParallelGradeWidget.cpp \
    $$PWD/HSequentialGradeWidget.cpp

FORMS += \
    $$PWD/HGradeItemDialog.ui \
    $$PWD/HGradeItem2DDialog.ui \
    $$PWD/HGradeIsothermDialog.ui \
    $$PWD/HGradeEditWidget.ui \
    $$PWD/HParallelGradeWidget.ui \
    $$PWD/HSequentialGradeWidget.ui

QXlsxPath   = $$absolute_path("../../../modules/QXlsx", $$[QT_INSTALL_DATA])

INCLUDEPATH += $$QXlsxPath/include

LIBS        += -L$$QXlsxPath/lib -lQXlsx
