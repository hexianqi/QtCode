/***************************************************************************************************
**      2019-05-20  HChromatismEditHandler 色容差编辑处理者类。
***************************************************************************************************/

#ifndef HCHROMATISMEDITHANDLER_H
#define HCHROMATISMEDITHANDLER_H

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HChromatismEditHandlerPrivate;

class HChromatismEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismEditHandler)

public:
    explicit HChromatismEditHandler(QObject *parent = nullptr);
    ~HChromatismEditHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMEDITHANDLER_H
