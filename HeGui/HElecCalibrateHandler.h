/***************************************************************************************************
**      2019-10-23  HElecCalibrateHandler
***************************************************************************************************/

#ifndef HELECCALIBRATEHANDLER_H
#define HELECCALIBRATEHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateHandlerPrivate;

class HElecCalibrateHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HElecCalibrateHandler)

public:
    explicit HElecCalibrateHandler(QObject *parent = nullptr);
    ~HElecCalibrateHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;

protected:
    HElecCalibrateHandler(HElecCalibrateHandlerPrivate &p, QObject *parent = nullptr);
};

HE_GUI_END_NAMESPACE

#endif // HELECCALIBRATEHANDLER_H
