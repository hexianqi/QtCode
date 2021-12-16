/***************************************************************************************************
**      2019-05-13  HSqlHandle 数据库记录处理。
***************************************************************************************************/

#pragma once

#include "ISqlHandle.h"

HE_BEGIN_NAMESPACE

class HSqlHandlePrivate;

class HSqlHandle : public QObject, public ISqlHandle
{
    Q_OBJECT

public:
    explicit HSqlHandle(QObject *parent = nullptr);
    ~HSqlHandle() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void setModel(ISqlTableModel *) override;
    void setFieldFind(QStringList value) override;
    QStringList field() override;

public:
    bool addRecord(QVariantMap value) override;
    void removeRecord() override;
    void removeRecord(int row, int count) override;
    void revertRecord() override;
    void findRecord() override;

protected:
    HSqlHandle(HSqlHandlePrivate &p, QObject *parent = nullptr);

protected:
    void setFilter(const QString &);
    QString toString(QPolygonF value);

protected:
    QScopedPointer<HSqlHandlePrivate> d_ptr;
};

HE_END_NAMESPACE
