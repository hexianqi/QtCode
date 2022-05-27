/***************************************************************************************************
**      2022-05-25  HAbstractService
***************************************************************************************************/

#pragma once

#include "IService.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HAbstractServicePrivate;

class HAbstractService : public QObject, public IService
{
    Q_OBJECT

public:
    explicit HAbstractService(QObject *parent = nullptr);
    ~HAbstractService() override;

public:
    bool start() override;
    bool stop() override;

public:
    bool isRunning();

protected:
    HAbstractService(HAbstractServicePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractServicePrivate> d_ptr;
};

HE_END_NAMESPACE

