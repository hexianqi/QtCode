HEADERS += \
    $$PWD/HGslHelper.h \
    $$PWD/HComplexNumber.h \
    $$PWD/HPoly.h

#    $$PWD/HDigitalFilter.h \
#    $$PWD/HBSplines.h \

SOURCES += \
    $$PWD/HGslHelper.cpp \
    $$PWD/HComplexNumber.cpp \
    $$PWD/HPoly.cpp

#    $$PWD/HDigitalFilter.cpp \
#    $$PWD/HBSplines.cpp \

DEFINES     += GSL_DLL  #此句不加将会遇到一些连接错误

LIBS        += \
            -LD:/Qt/gsl/lib/ -lgsl \
            -LD:/Qt/gsl/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/gsl/include
DEPENDPATH  += D:/Qt/gsl/include

include(gsl_sf.pri)
include(gsl_interp.pri)
include(gsl_fit.pri)
