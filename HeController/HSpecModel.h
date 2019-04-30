/***************************************************************************************************
**      2019-04-09  HSpecModel 光谱模型类。
***************************************************************************************************/

#ifndef HSPECMODEL_H
#define HSPECMODEL_H

#include "HAbstractModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecModelPrivate;

class HSpecModel : public HAbstractModel
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
    void syncTestData(quint32 type) override;
    void syncMachine(quint32 type) override;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECMODEL_H
