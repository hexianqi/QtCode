HEADERS += \
    $$PWD/HGslHelper.h \
    $$PWD/HInterp.h \
    $$PWD/HPolynomial.h \
    $$PWD/HSpecialFunction.h \
    $$PWD/HDigitalFilter.h \
    $$PWD/HBSplines.h \
    $$PWD/HComplexNumber.h \
    $$PWD/HLinearFit.h \
    $$PWD/HMultiFit.h


SOURCES += \
    $$PWD/HGslHelper.cpp \
    $$PWD/HInterp.cpp \
    $$PWD/HPolynomial.cpp \
    $$PWD/HSpecialFunction.cpp \
    $$PWD/HDigitalFilter.cpp \
    $$PWD/HBSplines.cpp \
    $$PWD/HComplexNumber.cpp \
    $$PWD/HLinearFit.cpp \
    $$PWD/HMultiFit.cpp


DEFINES     += GSL_DLL  #此句不加将会遇到一些连接错误

LIBS        += \
            -LD:/Qt/gsl/lib/ -lgsl \
            -LD:/Qt/gsl/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/gsl/include
DEPENDPATH  += D:/Qt/gsl/include
