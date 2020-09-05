/***************************************************************************************************
**      2019-05-13  HSqlHandle 数据库记录处理。
***************************************************************************************************/

#ifndef HSQLHANDLE_H
#define HSQLHANDLE_H

#include "ISqlHandle.h"
#include <QtCore/QObject>

HE_SQL_BEGIN_NAMESPACE

class HSqlHandlePrivate;

class HSqlHandle : public ISqlHandle
{
    Q_OBJECT

public:
    explicit HSqlHandle(QObject *parent = nullptr);
    ~HSqlHandle() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setModel(ISqlTableModel *) override;
    void setFieldFind(QStringList value) override;
    void setProductInfo(IProductInfo *) override;
    QStringList field() override;

public:
    bool addRecord(QVariantMap value, bool edit = true) override;
    void removeRecord() override;
    void removeRecord(int row, int count) override;
    void revertRecord() override;
    void findRecord() override;
    void editProductInfo() override;

protected:
    HSqlHandle(HSqlHandlePrivate &p, QObject *parent = nullptr);

protected:
    void setFilter(const QString &);
    QString toString(QPolygonF value);

protected:
    QScopedPointer<HSqlHandlePrivate> d_ptr;
};

HE_SQL_END_NAMESPACE

#endif // HSQLHANDLE_H
