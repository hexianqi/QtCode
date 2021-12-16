/***************************************************************************************************
**      2018-06-19  HAbstractModel 抽象模型类。
***************************************************************************************************/

#pragma once

#include "IModel.h"

HE_BEGIN_NAMESPACE

class HAbstractModelPrivate;

class HE_CONTROLLER_EXPORT HAbstractModel : public IModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractModel)

public:
    explicit HAbstractModel(QObject *parent = nullptr);
    ~HAbstractModel() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void start() override;
    void addAction(HActionType action, ulong delay = 0) override;
    void syncDeviceAll() override;

public:
    bool openFile() override;
    bool saveFile() override;
    bool saveAsFile() override;
    bool importFile(quint32 type) override;
    bool exportFile(quint32 type) override;

protected:
    HAbstractModel(HAbstractModelPrivate &p, QObject *parent = nullptr);

protected:
    void setConfigFile(const QString &fileName);
    void initDelayThread();
    void stopDelayThread();
    void initWorkThread();
    void stopWorkThread();

protected:
    QScopedPointer<HAbstractModelPrivate> d_ptr;
};

HE_END_NAMESPACE
