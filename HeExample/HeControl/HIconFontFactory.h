/***************************************************************************************************
**      2019-12-12  HIconFontFactory
***************************************************************************************************/

#ifndef HICONFONTFACTORY_H
#define HICONFONTFACTORY_H

#include "IIconFontFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HIconFontFactoryPrivate;

class HIconFontFactory : public QObject, public IIconFontFactory
{
    Q_OBJECT

public:
    explicit HIconFontFactory(QObject *parent = nullptr);
    ~HIconFontFactory() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList families() override;
    QFont createFont(const QString &family) override;

protected:
    HIconFontFactory(HIconFontFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HIconFontFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_CONTROL_END_NAMESPACE

#endif // HICONFONTFACTORY_H
