/***************************************************************************************************
**      2019-06-10  HRunTimeService 运行时间服务。
***************************************************************************************************/

#pragma once

#include "IService.h"
#include "HeCore/HSingleton2.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HRunTimeServicePrivate;

class HRunTimeService : public QObject, public IService
{
    Q_OBJECT
    H_SINGLETON2(HRunTimeService)

private:
    HRunTimeService(QObject *parent = nullptr);
    ~HRunTimeService() override;

public:
    void start() override;
    void stop() override;
    void setInterval(int);

protected:
    void initLog();
    void saveLog();

protected:
    QScopedPointer<HRunTimeServicePrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
