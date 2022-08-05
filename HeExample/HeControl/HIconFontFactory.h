/***************************************************************************************************
**      2019-12-12  HIconFontFactory
***************************************************************************************************/

#pragma once

#include "IIconFontFactory.h"

HE_BEGIN_NAMESPACE

class HIconFontFactoryPrivate;

class HIconFontFactory : public QObject, public IIconFontFactory
{
    Q_OBJECT

public:
    explicit HIconFontFactory(QObject *parent = nullptr);
    ~HIconFontFactory() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QStringList families() override;
    QFont createFont(const QString &family) override;
    QPoint fontRange(const QString &family) override;

protected:
    QScopedPointer<HIconFontFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_END_NAMESPACE
