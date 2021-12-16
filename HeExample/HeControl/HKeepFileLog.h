/***************************************************************************************************
**      2019-07-12  HKeepFileLog 文件日志（文件一直打开）
***************************************************************************************************/

#pragma once

#include "HAbstractFileLog.h"

HE_BEGIN_NAMESPACE

class HKeepFileLogPrivate;

class HKeepFileLog : public HAbstractFileLog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKeepFileLog)

public:
    explicit HKeepFileLog(QObject *parent = nullptr);
    ~HKeepFileLog() override;

public:
    bool readContent(QStringList &value) override;
    bool writeContent(QStringList value) override;
    bool appendContent(QStringList value) override;

protected:
    HKeepFileLog(HKeepFileLogPrivate &p, QObject *parent = nullptr);

private:
    void init();
    void reopenIfNeeded();
};

HE_END_NAMESPACE
