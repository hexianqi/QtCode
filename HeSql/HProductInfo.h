/***************************************************************************************************
**      2019-05-14  HProductInfo 产品信息。
***************************************************************************************************/

#pragma once

#include "IProductInfo.h"

HE_SQL_BEGIN_NAMESPACE

class HProductInfoPrivate;

class HProductInfo : public QObject, public IProductInfo
{
    Q_OBJECT

public:
    explicit HProductInfo(QObject *parent = nullptr);
    ~HProductInfo() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setRelationTableName(QString value) override;
    void setData(QString type, QVariant value) override;
    void setData(QVariantMap value) override;
    QVariant data(QString type) override;
    bool contains(QString type) override;
    bool enable() override;
    bool increase() override;
    bool editable() override;
    void saveOnce() override;

protected:
    HProductInfo(HProductInfoPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HProductInfoPrivate> d_ptr;

private:
    void readSettings();
    void writeSettings();
};

HE_SQL_END_NAMESPACE
