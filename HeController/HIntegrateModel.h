/***************************************************************************************************
**      2020-05-29  HIntegrateModel 光色电综合模型类。
***************************************************************************************************/

#pragma once

#include "HAbstractModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HIntegrateModelPrivate;

class HIntegrateModel : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIntegrateModel)

public:
    explicit HIntegrateModel(QObject *parent = nullptr);
    ~HIntegrateModel() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HIntegrateModel(HIntegrateModelPrivate &p, QObject *parent = nullptr);

protected:
    void syncTestData(quint32 type) override;
    void syncMachine(quint32 type) override;
};

HE_CONTROLLER_END_NAMESPACE

