HEADERS += \
    $$PWD/HLightButton.h \
    $$PWD/HLightButton_p.h \
    $$PWD/HLedNumber.h \
    $$PWD/HLedNumber_p.h \
    $$PWD/HSlideNavigation.h \
    $$PWD/HSlideNavigation_p.h \
    $$PWD/HAbstractProgress.h \
    $$PWD/HAbstractProgress_p.h \
    $$PWD/HAnimationProgress.h \
    $$PWD/HAnimationProgress_p.h

SOURCES += \
    $$PWD/HLightButton.cpp \
    $$PWD/HLedNumber.cpp \
    $$PWD/HSlideNavigation.cpp \
    $$PWD/HAbstractProgress.cpp \
    $$PWD/HAnimationProgress.cpp

include(circular.pri)
include(progressBar.pri)

include(else.pri)
include(gauge.pri)
include(ruler.pri)
include(texture.pri)

