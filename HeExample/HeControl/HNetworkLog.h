/***************************************************************************************************
**      2019-07-12  HNetworkLog 网络日志
***************************************************************************************************/

#ifndef HNETWORKLOG_H
#define HNETWORKLOG_H

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HNetworkLogPrivate;

class HNetworkLog : public QObject
{
    Q_OBJECT

public:
    static HNetworkLog *instance(QObject *parent = nullptr);

public:    
    ~HNetworkLog() override;

public slots:
    void send(const QString &value);

protected:
    HNetworkLog(QObject *parent = nullptr);
    HNetworkLog(HNetworkLogPrivate &p, QObject *parent = nullptr);
    HNetworkLog(const HNetworkLog&) = delete;
    HNetworkLog &operator=(const HNetworkLog&) = delete;

protected:
    static QScopedPointer<HNetworkLog> __instance;
    QScopedPointer<HNetworkLogPrivate> d_ptr;

private:
    void init();
    void handleNewConnection();
};

HE_CONTROL_END_NAMESPACE

#endif // HNETWORKLOG_H
