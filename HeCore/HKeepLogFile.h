/***************************************************************************************************
**      2022-05-25  HKeepLogFile
***************************************************************************************************/

#pragma once

#include "HAbstractLogFile.h"

HE_BEGIN_NAMESPACE

class HKeepLogFilePrivate;

class HKeepLogFile : public HAbstractLogFile
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKeepLogFile)

public:
    explicit HKeepLogFile(QObject *parent = nullptr);
    ~HKeepLogFile() override;

public slots:
    QStringList readLines() override;
    QString readAll() override;
    bool write(const QStringList &) override;
    bool write(const QString &) override;
    bool append(const QStringList &) override;
    bool append(const QString &) override;
    void clear();
    void setMaxRow(int);
    void setMaxSize(int);

protected:
    HKeepLogFile(HKeepLogFilePrivate &p, QObject *parent = nullptr);

private:
    void init();
    void openFile();
    QString generateFileName();
};

HE_END_NAMESPACE

