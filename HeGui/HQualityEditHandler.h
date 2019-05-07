/***************************************************************************************************
**      2019-05-07  HQualityEditHandler 品质数据编辑处理者类。
***************************************************************************************************/

#ifndef HQUALITYEDITHANDLER_H
#define HQUALITYEDITHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HQualityEditHandlerPrivate;

class HQualityEditHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HQualityEditHandler)

public:
    explicit HQualityEditHandler(QObject *parent = nullptr);
    ~HQualityEditHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HQUALITYEDITHANDLER_H
