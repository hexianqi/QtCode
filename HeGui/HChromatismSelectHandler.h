/***************************************************************************************************
**      2019-05-20  HChromatismSelectHandler 色容差数据选择处理者类。
***************************************************************************************************/

#ifndef HCHROMATISMSELECTHANDLER_H
#define HCHROMATISMSELECTHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HChromatismSelectHandlerPrivate;

class HChromatismSelectHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismSelectHandler)

public:
    explicit HChromatismSelectHandler(QObject *parent = nullptr);
    ~HChromatismSelectHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HCHROMATISMSELECTHANDLER_H
