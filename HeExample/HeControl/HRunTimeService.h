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
    Q_DECLARE_PRIVATE(HRunTimeService)

public:
    static HRunTimeService *instance(QObject *parent = nullptr);

public:
    ~HRunTimeService() override;

public:
    void start() override;
    void stop() override;
    void setPath(QString);
    void setFileName( QString);
    void setInterval(int);
    void initLog();
    void appendLog();
    void saveLog();

protected:
    HRunTimeService(QObject *parent = nullptr);
    HRunTimeService(HRunTimeServicePrivate &p, QObject *parent = nullptr);
    HRunTimeService(const HRunTimeService&) = delete;
    HRunTimeService &operator=(const HRunTimeService&) = delete;

protected:
    static QScopedPointer<HRunTimeService> __instance;
    QScopedPointer<HRunTimeServicePrivate> d_ptr;

private:
    void init();
    QString logFile();
};

HE_CONTROL_END_NAMESPACE

#endif // HRUNTIMESERVICE_H
