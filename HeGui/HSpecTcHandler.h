/***************************************************************************************************
**      2020-04-08  HSpecTcHandler 色温配置处理者类。
***************************************************************************************************/

#ifndef HSPECTCHANDLER_H
#define HSPECTCHANDLER_H

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecTcHandlerPrivate;

class HSpecTcHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecTcHandler)

public:
    explicit HSpecTcHandler(QObject *parent = nullptr);
    ~HSpecTcHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HSPECTCHANDLER_H
