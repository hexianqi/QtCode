/***************************************************************************************************
**      2022-05-25  HAbstractLogFile
***************************************************************************************************/

#pragma once

#include "ILogFile.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HAbstractLogFilePrivate;

class HAbstractLogFile : public QObject, public ILogFile
{
    Q_OBJECT

public:
    explicit HAbstractLogFile(QObject *parent = nullptr);
    ~HAbstractLogFile() override;

public:
    void setPath(const QString &) override;
    void setName(const QString &) override;
    void setDataTimeFormat(const QString &) override;

protected:
    HAbstractLogFile(HAbstractLogFilePrivate &p, QObject *parent = nullptr);

protected:
    QString fileName(QString format = QString());

protected:
    QScopedPointer<HAbstractLogFilePrivate> d_ptr;
};

HE_END_NAMESPACE

