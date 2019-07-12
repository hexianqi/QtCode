/***************************************************************************************************
**      2019-07-12  HFileLog 文件日志。
***************************************************************************************************/

#ifndef HFILELOG_H
#define HFILELOG_H

#include "HAbstractFileLog.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFileLogPrivate;

class HFileLog : public HAbstractFileLog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HFileLog)

public:
    explicit HFileLog(QObject *parent = nullptr);
    ~HFileLog() override;

public:
    bool readContent(QStringList &value) override;
    bool writeContent(QStringList value) override;
    bool appendContent(QStringList value) override;

protected:
    HFileLog(HFileLogPrivate &p, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HFILELOG_H
