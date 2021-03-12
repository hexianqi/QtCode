/***************************************************************************************************
**      2019-07-12  HLogService 日志服务。
**                  http://www.qtcn.org/bbs/read-htm-tid-85387-ds-1.html#tpc
***************************************************************************************************/

#pragma once

#include "IService.h"
#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class HLogServicePrivate;

class HLogService : public QObject, public IService
{
    Q_OBJECT
    H_SINGLETON3(HLogService)

private:
    HLogService(QObject *parent = nullptr);
    ~HLogService() override;

signals:
    void send(const QString &value);

public:
    void start() override;
    void stop() override;
    void save(const QString &value);
    void setToNet(bool b);

protected:
    QScopedPointer<HLogServicePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
