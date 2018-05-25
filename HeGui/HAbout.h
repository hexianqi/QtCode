#ifndef HABOUT_H
#define HABOUT_H


#include "HGuiGlobal.h"
#include "HeCore/IHandler.h"

HE_CORE_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAbout : public QObject, public IHandler
{
public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;
    virtual void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HABOUT_H
