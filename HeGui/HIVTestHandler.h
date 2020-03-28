/***************************************************************************************************
**      2019-11-29  HIVTestHandler
***************************************************************************************************/

#ifndef HIVTESTHANDLER_H
#define HIVTESTHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HIVTestHandlerPrivate;

class HIVTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIVTestHandler)

public:
    explicit HIVTestHandler(QObject *parent = nullptr);
    ~HIVTestHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTHANDLER_H
