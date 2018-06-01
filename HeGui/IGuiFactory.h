#ifndef IGUIFACTORY_H
#define IGUIFACTORY_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"

//HE_CORE_BEGIN_NAMESPACE
//class IHandler;
//HE_CORE_END_NAMESPACE
HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IGuiHandler;
class HAction;

class IGuiFactory : public IInitializeable
{
public:
    virtual IGuiHandler *createHandler(QString type, QVariantMap param = QVariantMap()) = 0;
    virtual HAction *createAction(QString text, QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_GUI_END_NAMESPACE

#endif // IGUIFACTORY_H
