QT       += core gui
QT       += network
QT += sql
QT += charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
CONFIG += thread

DEFINES-= UNICODE

include(QRCode/QRCode.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
#QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colormatchingfunctions.cpp \
    combodelegate.cpp \
    fmoptstatus.cpp \
    frmabout.cpp \
    frmbaseset.cpp \
    frmbinauto.cpp \
    frmbinpara.cpp \
    frmbinset.cpp \
    frmbinxy.cpp \
    frmcie1931.cpp \
    frmedtkey.cpp \
    frmlogin.cpp \
    frmspeccurve.cpp \
    frmsystemset.cpp \
    frmtestdata.cpp \
    frmverify.cpp \
    main.cpp \
    frmmain.cpp \
    regmanage.cpp \
    single_application.cpp \
    testsortthread.cpp \
    unitprofile.cpp \
    unitpublic.cpp

HEADERS += \
    DES.h \
    WENYU_PIO32P_DLL.h \
    colormatchingfunctions.h \
    combodelegate.h \
    fmoptstatus.h \
    frmabout.h \
    frmbaseset.h \
    frmbinauto.h \
    frmbinpara.h \
    frmbinset.h \
    frmbinxy.h \
    frmcie1931.h \
    frmedtkey.h \
    frmlogin.h \
    frmmain.h \
    frmspeccurve.h \
    frmsystemset.h \
    frmtestdata.h \
    frmverify.h \
    regmanage.h \
    semielectricitydll.h \
    semispectrumerdll.h \
    single_application.h \
    testsortthread.h \
    unitprofile.h \
    unitpublic.h

FORMS += \
    fmoptstatus.ui \
    frmabout.ui \
    frmbaseset.ui \
    frmbinauto.ui \
    frmbinpara.ui \
    frmbinset.ui \
    frmbinxy.ui \
    frmcie1931.ui \
    frmedtkey.ui \
    frmlogin.ui \
    frmmain.ui \
    frmspeccurve.ui \
    frmsystemset.ui \
    frmtestdata.ui \
    frmverify.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    smlres.qrc


win32: LIBS += -L$$PWD/./ -lsemielectricity

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./semielectricity.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libsemielectricity.a

win32: LIBS += -L$$PWD/./ -lsemispectluminousflux

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./semispectluminousflux.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libsemispectluminousflux.a


win32: LIBS += -L$$PWD/./ -lWENYU_PIO32P

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./WENYU_PIO32P.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/./libWENYU_PIO32P.a
