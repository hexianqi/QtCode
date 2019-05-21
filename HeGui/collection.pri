HEADERS += \
    $$PWD/IDataDetailWidget.h \
    $$PWD/IDataEditWidget.h \
    $$PWD/HListCollectionDialog.h \
    $$PWD/HListCollectionDialog_p.h \
    $$PWD/HAbstractDataDetailWidget.h

SOURCES += \
    $$PWD/HListCollectionDialog.cpp

FORMS += \
    $$PWD/HListCollectionDialog.ui

include(adjust.pri)
include(chromatism.pri)
include(grade.pri)
include(quality.pri)
