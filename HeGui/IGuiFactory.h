#ifndef IGUIFACTORY_H
#define IGUIFACTORY_H

#include "HGuiGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_BEGIN_NAMESPACE
class IHandler;
HE_CORE_END_NAMESPACE
HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAction;

class IGuiFactory : public IInitializeable
{
public:
    virtual IHandler *createHandler(QString type, QVariantMap param = QVariantMap()) = 0;
};


HE_GUI_END_NAMESPACE

#endif // IGUIFACTORY_H
