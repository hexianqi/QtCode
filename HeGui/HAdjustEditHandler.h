/***************************************************************************************************
**      2019-04-29  HAdjustEditHandler 调整编辑处理者类。
***************************************************************************************************/

#ifndef HADJUSTEDITHANDLER_H
#define HADJUSTEDITHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HAdjustEditHandlerPrivate;

class HAdjustEditHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAdjustEditHandler)

public:
    explicit HAdjustEditHandler(QObject *parent = nullptr);
    ~HAdjustEditHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITHANDLER_H
