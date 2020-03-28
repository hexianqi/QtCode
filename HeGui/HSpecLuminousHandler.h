/***************************************************************************************************
**      2020-03-26  HSpecLuminousHandler 光通量自吸收配置处理者类。
***************************************************************************************************/

#ifndef HSPECLUMINOUSHANDLER_H
#define HSPECLUMINOUSHANDLER_H

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecLuminousHandlerPrivate;

class HSpecLuminousHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecLuminousHandler)

public:
    explicit HSpecLuminousHandler(QObject *parent = nullptr);
    ~HSpecLuminousHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HSPECLUMINOUSHANDLER_H
