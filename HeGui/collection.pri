HEADERS += \
    $$PWD/HListCollectionDialog.h \
    $$PWD/HListCollectionDialog_p.h \
    $$PWD/IDataDetail.h \
    $$PWD/HDataDetail.h \
    $$PWD/IDataEditer.h

SOURCES += \
    $$PWD/HListCollectionDialog.cpp

FORMS += \
    $$PWD/HListCollectionDialog.ui

include(adjust.pri)
include(chromatism.pri)
include(grade.pri)
include(location.pri)
include(quality.pri)
