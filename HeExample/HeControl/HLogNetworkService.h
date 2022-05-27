/***************************************************************************************************
**      2022-05-25  HLogNetworkService 日志网络发送服务。
***************************************************************************************************/

#pragma once

#include "HAbstractService.h"
#include "HeCore/HSingleton3.h"

HE_BEGIN_NAMESPACE

class HLogNetworkServicePrivate;

class HLogNetworkService : public HAbstractService
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLogNetworkService)
    H_SINGLETON3(HLogNetworkService)

private:
    explicit HLogNetworkService();
    ~HLogNetworkService() override;

public:
    bool start() override;
    bool stop() override;

public slots:
    void setListenPort(int);
    void sendData(const QString &value);

private:
    void init();
    void handleNewConnection();
};

HE_END_NAMESPACE

