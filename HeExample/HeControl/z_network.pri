HEADERS += \
#    $$PWD/HAbstractNetworkWidget.h \
#    $$PWD/HAbstractNetworkWidget_p.h \
#    $$PWD/HAbstractServerWidget.h \
#    $$PWD/HAbstractServerWidget_p.h \
#    $$PWD/HAbstractClientWidget.h \
#    $$PWD/HAbstractClientWidget_p.h

SOURCES += \
#    $$PWD/HAbstractNetworkWidget.cpp \
#    $$PWD/HAbstractServerWidget.cpp \
#    $$PWD/HAbstractClientWidget.cpp

include(z_tcp.pri)
#include(udp.pri)
#include(ntp.pri)
#include(http.pri)
include(z_smtp.pri)
