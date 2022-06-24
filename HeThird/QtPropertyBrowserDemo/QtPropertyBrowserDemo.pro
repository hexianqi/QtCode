QT          += core gui widgets

CONFIG      += c++11

DESTDIR     = "../../Dest"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES     += \
            HDemoWidget.cpp \
            HDoublePropertyManager.cpp \
            HDoubleSpinBoxFactory.cpp \
            HPointFPropertyManager.cpp \
            HPropertyBrowser.cpp \
            HVariantWidget.cpp \
            main.cpp \
            MainWindow.cpp

HEADERS     += \
            HDemoWidget.h \
            HDoublePropertyManager.h \
            HDoublePropertyManager_p.h \
            HDoubleSpinBoxFactory.h \
            HDoubleSpinBoxFactory_p.h \
            HPointFPropertyManager.h \
            HPointFPropertyManager_p.h \
            HPropertyBrowser.h \
            HPropertyBrowser_p.h \
            HVariantWidget.h \
            MainWindow.h

FORMS       += \
            MainWindow.ui

RESOURCES   += \
            QtPropertyBrowserDemo.qrc

ThirdPath   = $$[QT_INSTALL_PREFIX]/../Src/qttools/src/shared/qtpropertybrowser

INCLUDEPATH += $$ThirdPath

include(Canvas.pri)
include($$ThirdPath/QtPropertyBrowser.pri)


