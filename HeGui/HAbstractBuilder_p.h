#ifndef HABSTRACTBUILDER_P_H
#define HABSTRACTBUILDER_P_H

#include "HAbstractBuilder.h"
#include "HeCommunicate/HCommunicateGlobal.h"
#include "HeController/HControllerGlobal.h"
#include "HeData/HDataGlobal.h"

#include "HeSql/HSqlGlobal.h"

HE_COMMUNICATE_BEGIN_NAMESPACE
class ICommunicateFactory;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IControllerFactory;
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class IConfigManage;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE
class ISqlFactory;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IGuiFactory;

class HE_GUI_EXPORT HAbstractBuilderPrivate
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
    IModel *model = nullptr;
    QString configFileName;
    QVariantMap deploy;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTBUILDER_P_H
