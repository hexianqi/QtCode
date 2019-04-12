/***************************************************************************************************
**      2019-03-01  HTestHandler 测试处理者类。
***************************************************************************************************/

#ifndef HTESTHANDLER_H
#define HTESTHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HTestHandlerPrivate;

class HTestHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestHandler)

public:
    explicit HTestHandler(QObject *parent = nullptr);
    ~HTestHandler() override;

public:
    QString typeName() override;
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HTESTHANDLER_H
