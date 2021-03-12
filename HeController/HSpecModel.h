/***************************************************************************************************
**      2019-04-09  HSpecModel 光谱模型类。
***************************************************************************************************/

#pragma once

#include "HAbstractModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecModelPrivate;

class HE_CONTROLLER_EXPORT HSpecModel : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecModel)

public:
    explicit HSpecModel(QObject *parent = nullptr);
    ~HSpecModel() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HSpecModel(HSpecModelPrivate &p, QObject *parent = nullptr);

protected:
    void syncTestData(quint32 type) override;
    void syncDevice(quint32 type) override;
};

HE_CONTROLLER_END_NAMESPACE
