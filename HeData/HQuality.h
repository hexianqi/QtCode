/***************************************************************************************************
**      2019-05-05  HQuality 品质数据。
***************************************************************************************************/

#pragma once

#include "IQuality.h"

HE_BEGIN_NAMESPACE

class HQualityPrivate;
class IQualityItemCollection;

class HQuality : public IQuality
{
public:
    explicit HQuality();
    ~HQuality();

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    IQualityItemCollection *itemCollection(HQualityType type) override;
    void setColor(HQualityReport type, const QColor &value) override;
    QColor color(HQualityReport type) override;
    HQualityReport check(QVariantMap value, QVariantMap *color) override;
    double drift(QString type, QVariant value) override;

protected:
    HQuality(HQualityPrivate &p);

protected:
    QScopedPointer<HQualityPrivate> d_ptr;
};

HE_END_NAMESPACE
