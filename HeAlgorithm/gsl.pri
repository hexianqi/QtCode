HEADERS += \
    $$PWD/HInterp.h

SOURCES += \
    $$PWD/HInterp.cpp

DEFINES     += GSL_DLL  #此句不加将会遇到一些连接错误

LIBS        += \
            -LD:/Qt/gsl-1.8/lib/ -lgsl \
            -LD:/Qt/gsl-1.8/lib/ -lgslcblas

INCLUDEPATH += D:/Qt/gsl-1.8/include
DEPENDPATH  += D:/Qt/gsl-1.8/include
