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

#此句不加将会遇到一些连接错误
DEFINES     += GSL_DLL

LIBS        += \
            -LD:/Qt/libgsl/lib/ -lgsl \
            -LD:/Qt/libgsl/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/libgsl/include
DEPENDPATH  += D:/Qt/libgsl/include

include(gsl_sf.pri)
include(gsl_interp.pri)
include(gsl_fit.pri)
