HEADERS += \
    $$PWD/HAbstractNetworkWidget.h \
    $$PWD/HAbstractNetworkWidget_p.h \
    $$PWD/HAbstractServerWidget.h \
    $$PWD/HAbstractServerWidget_p.h \
    $$PWD/HAbstractClientWidget.h \
    $$PWD/HAbstractClientWidget_p.h

SOURCES += \
    $$PWD/HAbstractNetworkWidget.cpp \
    $$PWD/HAbstractServerWidget.cpp \
    $$PWD/HAbstractClientWidget.cpp

include(tcp.pri)
include(udp.pri)
include(smtp.pri)
include(ntp.pri)
include(http.pri)
