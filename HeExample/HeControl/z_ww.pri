# http://qt-apps.org/content/show.php/wwWidgets?content=126142

HEADERS += \
    $$PWD/HLedWidget.h \
    $$PWD/HLedWidget_p.h \
    $$PWD/HNumPad.h \
    $$PWD/HNumPad_p.h \
    $$PWD/HNavigationSlider.h \
    $$PWD/HNavigationSlider_p.h \
    $$PWD/HTipWidget.h \
    $$PWD/HTipWidget_p.h

SOURCES += \
    $$PWD/HLedWidget.cpp \
    $$PWD/HNumPad.cpp \
    $$PWD/HNavigationSlider.cpp \
    $$PWD/HTipWidget.cpp

RESOURCES += $$PWD/ww.qrc

include(z_ww_color.pri)
include(z_ww_lineEdit.pri)
include(z_ww_panel.pri)
include(z_ww_richText.pri)
include(z_ww_spinBox.pri)
