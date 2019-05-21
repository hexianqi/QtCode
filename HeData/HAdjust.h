/***************************************************************************************************
**      2019-04-28  HAdjust 调整数据。
***************************************************************************************************/

#ifndef HADJUST_H
#define HADJUST_H

#include "IAdjust.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustPrivate;

class HAdjust : public IAdjust
{
    Q_DECLARE_PRIVATE(HAdjust)

public:
    explicit HAdjust();
    virtual ~HAdjust();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &, IDataFactory *) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    QVariantMap correct(QVariantMap value) override;

protected:
    HAdjust(HAdjustPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HADJUST_H
