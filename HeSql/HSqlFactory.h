/***************************************************************************************************
**      2019-04-12  HSqlFactory Sql工厂类。
***************************************************************************************************/

#pragma once

#include "ISqlFactory.h"

HE_BEGIN_NAMESPACE

class HSqlFactoryPrivate;

class HSqlFactory : public QObject, public ISqlFactory
{
    Q_OBJECT

public:
    explicit HSqlFactory(QObject *parent = nullptr);
    ~HSqlFactory() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    ISqlDatabase *createDatabase(QString type, QVariantMap param = QVariantMap()) override;
    ISqlTableModel *createTableModel(QString type, QVariantMap param = QVariantMap()) override;
    ISqlHandle *createHandle(QString type, QVariantMap param = QVariantMap()) override;
    ISqlOutput *createOutput(QString type, QVariantMap param = QVariantMap()) override;
    ISqlBrowser *createBrowser(QString type, QWidget *parent = nullptr, QVariantMap param = QVariantMap()) override;

protected:
    HSqlFactory(HSqlFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSqlFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_END_NAMESPACE
