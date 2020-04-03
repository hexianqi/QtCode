/***************************************************************************************************
**      2019-07-12  HNetworkLog 网络日志（只监控一个IP）。
***************************************************************************************************/

#ifndef HNETWORKLOG_H
#define HNETWORKLOG_H

#include "HControlGlobal.h"
#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HNETWORKLOG_H
