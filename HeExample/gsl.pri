HEADERS += \
    $$PWD/HComplexNumbers.h \
    $$PWD/HPolynomials.h \
    $$PWD/HSpecial.h \
    $$PWD/HInterpolation.h


SOURCES += \
    $$PWD/HComplexNumbers.cpp \
    $$PWD/HPolynomials.cpp \
    $$PWD/HSpecial.cpp \
    $$PWD/HInterpolation.cpp

DEFINES     += GSL_DLL  #此句不加将会遇到一些连接错误

LIBS        += \
            -LD:/Qt/gsl-1.8/lib/ -lgsl \
            -LD:/Qt/gsl-1.8/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/gsl-1.8/include
DEPENDPATH  += D:/Qt/gsl-1.8/include
