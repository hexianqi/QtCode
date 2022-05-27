/***************************************************************************************************
**      2022-05-26  HRunTimeService 运行时间记录服务。
***************************************************************************************************/

#pragma once

#include "HAbstractService.h"
#include "HeCore/HSingleton2.h"

HE_BEGIN_NAMESPACE

class ILogFile;
class HRunTimeServicePrivate;

class HRunTimeService : public HAbstractService
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HRunTimeService)
    H_SINGLETON2(HRunTimeService)

private:
    explicit HRunTimeService(QObject *parent = nullptr);
    ~HRunTimeService() override;

public:
signals:
    void dataChanged(const QString &value, bool append);

public:
    ILogFile *file();

public slots:
    bool start() override;
    bool stop() override;
    void setInterval(int);  // 设置保存间隔
    void initLog();         // 初始化日志文件
    void appendLog();       // 追加一条记录到日志文件
    void saveLog();         // 保存运行时间到日志文件

private:
    void init();
};

HE_END_NAMESPACE

