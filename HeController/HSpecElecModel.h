/***************************************************************************************************
**      2019-10-24  HSpecElecModel
***************************************************************************************************/

#ifndef HSPECELECMODEL_H
#define HSPECELECMODEL_H

#include "HSpecModel.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecModelPrivate;

class HSpecElecModel : public HSpecModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecElecModel)

public:
    explicit HSpecElecModel(QObject *parent = nullptr);
    ~HSpecElecModel() override;

public:
    QString typeName() override;

protected:
    HSpecElecModel(HSpecElecModelPrivate &p, QObject *parent = nullptr);

protected:
    void syncTestData(quint32 type) override;
    void syncMachine(quint32 type) override;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECELECMODEL_H
