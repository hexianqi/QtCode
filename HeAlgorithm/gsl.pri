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

3RDPARTY    = $$absolute_path("../../../libgsl", $$[QT_INSTALL_DATA])

LIBS        += \
            -L$$3RDPARTY/lib -lgsl \
            -L$$3RDPARTY/lib -lgslcblas

INCLUDEPATH += $$3RDPARTY/include
DEPENDPATH  += $$3RDPARTY/include

include(gsl_sf.pri)
include(gsl_interp.pri)
include(gsl_fit.pri)
