/***************************************************************************************************
**      2019-04-25  HGradeSelectHandler 分级选择处理者类。
***************************************************************************************************/

#ifndef HGRADESELECTHANDLER_H
#define HGRADESELECTHANDLER_H

#include "HAbstractGuiHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HGradeSelectHandlerPrivate;

class HGradeSelectHandler : public HAbstractGuiHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeSelectHandler)

public:
    explicit HGradeSelectHandler(QObject *parent = nullptr);
    ~HGradeSelectHandler() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_GUI_END_NAMESPACE

#endif // HGRADESELECTHANDLER_H
