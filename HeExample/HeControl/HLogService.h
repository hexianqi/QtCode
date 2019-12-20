/***************************************************************************************************
**      2019-07-12  HLogService 日志服务。
**                  http://www.qtcn.org/bbs/read-htm-tid-85387-ds-1.html#tpc
***************************************************************************************************/

#ifndef HLOGSERVICE_H
#define HLOGSERVICE_H

#include "IService.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HLogServicePrivate;

class HLogService : public QObject, public IService
{
    Q_OBJECT

public:
    static HLogService *instance();

public:
    ~HLogService() override;

signals:
    void send(const QString &value);

public:
    void start() override;
    void stop() override;
    void save(const QString &value);
    void setToNet(bool b);

protected:
    HLogService(QObject *parent = nullptr);
    HLogService(const HLogService&) = delete;
    HLogService &operator=(const HLogService&) = delete;

protected:
    static QScopedPointer<HLogService> __instance;
    QScopedPointer<HLogServicePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HLOGSERVICE_H
