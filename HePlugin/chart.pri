HEADERS += \
    $$PWD/HChart.h \
    $$PWD/HChart_p.h \
    $$PWD/HSingleAxisChart.h \
    $$PWD/HSingleAxisChart_p.h \
    $$PWD/HCie1931Chart.h \
    $$PWD/HCie1931Chart_p.h \
    $$PWD/HChromatismChart.h \
    $$PWD/HChromatismChart_p.h

SOURCES += \
    $$PWD/HChart.cpp \
    $$PWD/HSingleAxisChart.cpp \
    $$PWD/HCie1931Chart.cpp \
    $$PWD/HChromatismChart.cpp

include(chartView.pri)
include(chartExtend.pri)
