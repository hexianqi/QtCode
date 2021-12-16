/***************************************************************************************************
**      2019-04-25  HGradeEditHandler 分级数据编辑处理者类。
***************************************************************************************************/

#pragma once

#include "HAbstractConfigHandler.h"

HE_BEGIN_NAMESPACE

class HGradeEditHandlerPrivate;

class HGradeEditHandler : public HAbstractConfigHandler
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGradeEditHandler)

public:
    explicit HGradeEditHandler(QObject *parent = nullptr);
    ~HGradeEditHandler() override;

public:
    QString typeName() override;

public:
    void execute(QObject *sender = nullptr, QVariantMap param = QVariantMap()) override;
};

HE_END_NAMESPACE
