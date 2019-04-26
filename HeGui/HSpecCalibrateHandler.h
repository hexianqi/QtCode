/***************************************************************************************************
**      2019-04-25  HSpecCalibrateHandler 光谱定标处理者类。
***************************************************************************************************/

#ifndef HSPECCALIBRATEHANDLER_H
#define HSPECCALIBRATEHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateHandlerPrivate;

class HSpecCalibrateHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateHandler)

public:
    explicit HSpecCalibrateHandler(QObject *parent = nullptr);
    ~HSpecCalibrateHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATEHANDLER_H
