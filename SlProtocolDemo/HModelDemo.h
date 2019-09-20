/***************************************************************************************************
**      2019-09-16  HModelDemo
***************************************************************************************************/

#ifndef HMODELDEMO_H
#define HMODELDEMO_H

#include "HeController/HAbstractModel.h"

HE_CONTROLLER_USE_NAMESPACE

class HModelDemoPrivate;

class HModelDemo : public HAbstractModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HModelDemo)

public:
    explicit HModelDemo(QObject *parent = nullptr);
    ~HModelDemo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void addAction(HActionType action, ulong delay = 0) override;

protected:
    void syncTestData(quint32 type) override;
    void syncMachine(quint32 type) override;
};

#endif // HMODELDEMO_H
