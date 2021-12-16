#pragma once

#include "HAbstractBuilder.h"

HE_BEGIN_NAMESPACE

class ICommunicateFactory;
class IControllerFactory;
class IDataFactory;
class IConfigManage;
class ISqlFactory;
class IGuiFactory;

class HAbstractBuilderPrivate
{
public:
    HAbstractBuilderPrivate();

public:
    IMainWindow *mainWindow = nullptr;
    ICommunicateFactory *communicateFactory = nullptr;
    IControllerFactory *controllerFactory = nullptr;
    IDataFactory *dataFactory = nullptr;
    IGuiFactory *guiFactory = nullptr;
    ISqlFactory *sqlFactory = nullptr;
    IConfigManage *configManage = nullptr;
    QString configFileName;
    QVariantMap deploy;
};

HE_END_NAMESPACE
