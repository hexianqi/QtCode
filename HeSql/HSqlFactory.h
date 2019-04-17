/***************************************************************************************************
**      2019-04-12  HSqlFactory Sql工厂类。
***************************************************************************************************/

#ifndef HSQLFACTORY_H
#define HSQLFACTORY_H

#include "ISqlFactory.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlFactoryPrivate;

class HE_SQL_EXPORT HSqlFactory : public QObject, public ISqlFactory
{
    Q_OBJECT

public:
    explicit HSqlFactory(QObject *parent = nullptr);
    ~HSqlFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    ISqlDatabase *createDatabase(QString type, QVariantMap param = QVariantMap()) override;
    ISqlTableModel *createTableModel(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HSqlFactory(HSqlFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSqlFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_SQL_END_NAMESPACE

#endif // HSQLFACTORY_H
