/***************************************************************************************************
**      2019-07-19  HQssStyle Qss样式
***************************************************************************************************/

#pragma once

#include "IQssStyle.h"

HE_BEGIN_NAMESPACE

class HQssStylePrivate;

class HQssStyle : public QObject, public IQssStyle
{
    Q_OBJECT

public:
    explicit HQssStyle(QObject *parent = nullptr);
    ~HQssStyle() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QString toStyleSheet() override;
    QPalette toPalette() override;
    QColor color(const QString &flag) override;
    QStringList styles() override;
    bool selectStyle(const QString &vlaue) override;
    void addStyle(const QString &key, const QString &fileName) override;

protected:
    HQssStyle(HQssStylePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HQssStylePrivate> d_ptr;

private:
    void init();
};

HE_END_NAMESPACE
