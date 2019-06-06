QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DESTDIR     = "../../Dest"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        HAdapter.cpp \
        HBridge.cpp \
        HBuilder.cpp \
        HChain.cpp \
        HCommand.cpp \
        HComposite.cpp \
        HDecorator.cpp \
        HFacade.cpp \
        HFlyweight.cpp \
        HInterpreter.cpp \
        HMediator.cpp \
        HMemento.cpp \
        HObserver.cpp \
        HPrototype.cpp \
        HProxy.cpp \
        HSingleton.cpp \
        HState.cpp \
        HStrategy.cpp \
        HTemplate.cpp \
        HTestDesignPattern.cpp \
        HVisitor.cpp

HEADERS += \
        HAdapter.h \
        HBridge.h \
        HBuilder.h \
        HChain.h \
        HCommand.h \
        HComposite.h \
        HDecorator.h \
        HDesignPattern.h \
        HFacade.h \
        HFlyweight.h \
        HInterpreter.h \
        HMediator.h \
        HMemento.h \
        HObserver.h \
        HPrototype.h \
        HProxy.h \
        HSingleton.h \
        HState.h \
        HStrategy.h \
        HTemplate.h \
        HTestDesignPattern.h \
        HVisitor.h
