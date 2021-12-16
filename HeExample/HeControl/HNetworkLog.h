/***************************************************************************************************
**      2019-07-12  HNetworkLog 网络日志（只监控一个IP）。
***************************************************************************************************/

#pragma once

#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HNetworkLogPrivate;

class HNetworkLog : public QObject
{
    Q_OBJECT
    H_SINGLETON3(HNetworkLog)

private:
   HNetworkLog(QObject *parent = nullptr);
   ~HNetworkLog() override;

public slots:
    void send(const QString &value);

protected:
    QScopedPointer<HNetworkLogPrivate> d_ptr;

private:
    void init();
    void handleNewConnection();
};

HE_END_NAMESPACE
