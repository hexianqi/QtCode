/***************************************************************************************************
**      2019-07-12  HKeepFileLog 文件日志（文件一直打开）
***************************************************************************************************/

#ifndef HKEEPFILELOG_H
#define HKEEPFILELOG_H

#include "HAbstractFileLog.h"

HE_CONTROL_BEGIN_NAMESPACE

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
    void reopenFileIfNeeded();
};

HE_CONTROL_END_NAMESPACE

#endif // HKEEPFILELOG_H
