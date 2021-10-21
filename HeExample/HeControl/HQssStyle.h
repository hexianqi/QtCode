/***************************************************************************************************
**      2019-07-19  HQssStyle Qss样式
***************************************************************************************************/

#pragma once

#include "IQssStyle.h"

HE_CONTROL_BEGIN_NAMESPACE

class HQssStylePrivate;

class HQssStyle : public QObject, public IQssStyle
{
    Q_OBJECT

public:
    explicit HQssStyle(QObject *parent = nullptr);
    ~HQssStyle() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QString toStyleSheet() override;
    QPalette toPalette() override;
    QStringList styles() override;
    bool selectStyle(QString value) override;
    void addStyle(QString key, QString fileName) override;

protected:
    HQssStyle(HQssStylePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HQssStylePrivate> d_ptr;

private:
    void init();
};

HE_CONTROL_END_NAMESPACE
