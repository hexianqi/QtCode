/***************************************************************************************************
**      2019-07-12  HAbstractFileLog 抽象文件日志。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractFileLogPrivate;

class HAbstractFileLog : public QObject
{
    Q_OBJECT

public:
    explicit HAbstractFileLog(QObject *parent = nullptr);
    ~HAbstractFileLog() override;

public:
    virtual void setPath(const QString &);
    virtual void setName(const QString &);
    virtual void setDataFormat(const QString &);
    virtual bool readContent(QStringList &value) = 0;
    virtual bool writeContent(QStringList value) = 0;
    virtual bool appendContent(QStringList value) = 0;

protected:
    HAbstractFileLog(HAbstractFileLogPrivate &p, QObject *parent = nullptr);

protected:
    QString fileName();

protected:
    QScopedPointer<HAbstractFileLogPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
