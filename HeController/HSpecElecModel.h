/***************************************************************************************************
**      2019-10-24  HSpecElecModel
***************************************************************************************************/

#pragma once

#include "HAbstractModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecModelPrivate;

class HSpecElecModel : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecElecModel)

public:
    explicit HSpecElecModel(QObject *parent = nullptr);
    ~HSpecElecModel() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HSpecElecModel(HSpecElecModelPrivate &p, QObject *parent = nullptr);

protected:
    void syncTestData(quint32 type) override;
    void syncDevice(quint32 type) override;
};

HE_CONTROLLER_END_NAMESPACE
