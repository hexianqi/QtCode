/***************************************************************************************************
**      2022-05-25  HLogFile
***************************************************************************************************/

#pragma once

#include "HAbstractLogFile.h"

HE_BEGIN_NAMESPACE

class HLogFilePrivate;

class HLogFile : public HAbstractLogFile
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLogFile)

public:
    explicit HLogFile(QObject *parent = nullptr);
    ~HLogFile() override;

public:
    QStringList readLines() override;
    QString readAll() override;
    bool write(const QStringList &) override;
    bool write(const QString &) override;
    bool append(const QStringList &) override;
    bool append(const QString &) override;

protected:
    HLogFile(HLogFilePrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

