HEADERS += \
    $$PWD/HGslHelper.h \
    $$PWD/HComplexNumber.h \
    $$PWD/HPolynomial.h

#    $$PWD/HDigitalFilter.h \
#    $$PWD/HBSplines.h \

SOURCES += \
    $$PWD/HGslHelper.cpp \
    $$PWD/HComplexNumber.cpp \
    $$PWD/HPolynomial.cpp

#    $$PWD/HDigitalFilter.cpp \
#    $$PWD/HBSplines.cpp \

DEFINES     += GSL_DLL  #此句不加将会遇到一些连接错误

LIBS        += \
            -LD:/Qt/gsl64/lib/ -lgsl \
            -LD:/Qt/gsl64/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/gsl64/include
DEPENDPATH  += D:/Qt/gsl64/include

include(gsl_sf.pri)
include(gsl_interp.pri)
include(gsl_fit.pri)
