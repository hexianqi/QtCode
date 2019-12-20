/***************************************************************************************************
**      2019-06-10  HRunTimeService 运行时间服务。
***************************************************************************************************/

#ifndef HRUNTIMESERVICE_H
#define HRUNTIMESERVICE_H

#include "IService.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HRunTimeServicePrivate;

class HRunTimeService : public QObject, public IService
{
    Q_OBJECT

public:
    static HRunTimeService *instance();

public:
    ~HRunTimeService() override;

public:
    void start() override;
    void stop() override;
    void setInterval(int);

protected:
    HRunTimeService(QObject *parent = nullptr);
    HRunTimeService(const HRunTimeService&) = delete;
    HRunTimeService &operator=(const HRunTimeService&) = delete;

protected:
    void initLog();
    void saveLog();

protected:
    static QScopedPointer<HRunTimeService> __instance;
    QScopedPointer<HRunTimeServicePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE

#endif // HRUNTIMESERVICE_H
