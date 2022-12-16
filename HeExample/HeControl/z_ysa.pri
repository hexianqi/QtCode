#https://blog.csdn.net/kenfan1647?type=blog

HEADERS += \
    $$PWD/HBinaryTreeWidget.h \
    $$PWD/HBinaryTreeWidget_p.h \
    $$PWD/HChatWidget.h \
    $$PWD/HChatWidget_p.h \
    $$PWD/HColorGradientRoundedButton.h \
    $$PWD/HColorGradientRoundedButton_p.h \
    $$PWD/HColorSelectionRing.h \
    $$PWD/HColorSelectionRing_p.h \
    $$PWD/HColorSlipRing.h \
    $$PWD/HColorSlipRing_p.h \
    $$PWD/HComboBoxTableView.h \
    $$PWD/HComboBoxTableView_p.h \
    $$PWD/HDiscButton.h \
    $$PWD/HDiscButton_p.h \
    $$PWD/HGradientProgressBar.h \
    $$PWD/HGradientProgressBar_p.h \
    $$PWD/HHoverShowWidget.h \
    $$PWD/HHoverShowWidget_p.h \
    $$PWD/HIrregularPopupWidget.h \
    $$PWD/HIrregularPopupWidget_p.h \
    $$PWD/HJsonTextEdit.h \
    $$PWD/HJsonTextEdit_p.h \
    $$PWD/HLineShadowWidget.h \
    $$PWD/HLineShadowWidget_p.h \
    $$PWD/HLotteryTurntableWidget.h \
    $$PWD/HLotteryTurntableWidget_p.h \
    $$PWD/HOnOffWidget.h \
    $$PWD/HOnOffWidget_p.h \
    $$PWD/HPatternLockWidget.h \
    $$PWD/HPatternLockWidget_p.h \
    $$PWD/HProcessDisplayWidget.h \
    $$PWD/HProcessDisplayWidget_p.h \
    $$PWD/HRotatingClockWidget.h \
    $$PWD/HRotatingClockWidget_p.h \
    $$PWD/HRoundMenuWidget.h \
    $$PWD/HRoundMenuWidget_p.h \
    $$PWD/HRoundShadowWidget.h \
    $$PWD/HRoundShadowWidget_p.h \
    $$PWD/HRulerWidget.h \
    $$PWD/HRulerWidget_p.h \
    $$PWD/HTimeSlider.h \
    $$PWD/HTimeSlider_p.h \
    $$PWD/HTimelineWidget.h \
    $$PWD/HTimelineWidget_p.h \
    $$PWD/HYsaSpecialWidget.h

SOURCES += \
    $$PWD/HBinaryTreeWidget.cpp \
    $$PWD/HChatWidget.cpp \
    $$PWD/HColorGradientRoundedButton.cpp \
    $$PWD/HColorSelectionRing.cpp \
    $$PWD/HColorSlipRing.cpp \
    $$PWD/HComboBoxTableView.cpp \
    $$PWD/HDiscButton.cpp \
    $$PWD/HGradientProgressBar.cpp \
    $$PWD/HHoverShowWidget.cpp \
    $$PWD/HIrregularPopupWidget.cpp \
    $$PWD/HJsonTextEdit.cpp \
    $$PWD/HLineShadowWidget.cpp \
    $$PWD/HLotteryTurntableWidget.cpp \
    $$PWD/HOnOffWidget.cpp \
    $$PWD/HPatternLockWidget.cpp \
    $$PWD/HProcessDisplayWidget.cpp \
    $$PWD/HRotatingClockWidget.cpp \
    $$PWD/HRoundMenuWidget.cpp \
    $$PWD/HRoundShadowWidget.cpp \
    $$PWD/HRulerWidget.cpp \
    $$PWD/HTimeSlider.cpp \
    $$PWD/HTimelineWidget.cpp \
    $$PWD/HYsaSpecialWidget.cpp

RESOURCES += $$PWD/ysa.qrc

include(z_ysa_graphics.pri)

FORMS += \
    $$PWD/HYsaSpecialWidget.ui
