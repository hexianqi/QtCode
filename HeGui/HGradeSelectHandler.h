/***************************************************************************************************
**      2019-04-25  HGradeSelectHandler 分级数据选择处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_GUI_BEGIN_NAMESPACE

class HGradeSelectHandlerPrivate;

class HGradeSelectHandler : public HAbstractConfigHandler
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
