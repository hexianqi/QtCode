HEADERS += \
    $$PWD/HSlideNavigation.h \
    $$PWD/HSlideNavigation_p.h \
    $$PWD/HAbstractProgress.h \
    $$PWD/HAbstractProgress_p.h \
    $$PWD/HAnimationProgress.h \
    $$PWD/HAnimationProgress_p.h \

SOURCES += \
    $$PWD/HSlideNavigation.cpp \
    $$PWD/HAbstractProgress.cpp \
    $$PWD/HAnimationProgress.cpp

include(_ldw_button.pri)
include(_ldw_calendar.pri)
include(_ldw_else.pri)

include(button.pri)
include(circular.pri)
include(color.pri)
include(combobox.pri)
include(draw.pri)
include(effect.pri)
include(else.pri)
include(gauge.pri)
include(nav.pri)
include(progressBar.pri)
include(ruler.pri)
include(texture.pri)
