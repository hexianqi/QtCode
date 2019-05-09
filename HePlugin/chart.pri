HEADERS += \
    $$PWD/HChart.h \
    $$PWD/HChart_p.h \
    $$PWD/HSingleAxisChart.h \
    $$PWD/HSingleAxisChart_p.h \
    $$PWD/HCIE1931Chart.h \
    $$PWD/HCIE1931Chart_p.h

SOURCES += \
    $$PWD/HChart.cpp \
    $$PWD/HSingleAxisChart.cpp \
    $$PWD/HCIE1931Chart.cpp

include(chartView.pri)
include(chartExtend.pri)
