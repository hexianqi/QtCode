#ifndef HTESTHANDLER_H
#define HTESTHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT

public:
    explicit HTestHandler(QObject *parent = nullptr);

public:
    virtual QString typeName() override;
    virtual void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HTESTHANDLER_H
