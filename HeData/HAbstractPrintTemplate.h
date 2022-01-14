/***************************************************************************************************
**      2021-10-19  HAbstractPrintTemplate 抽象打印模版。
***************************************************************************************************/

#pragma once

#include "IPrintTemplate.h"

HE_BEGIN_NAMESPACE

class HAbstractPrintTemplatePrivate;

class HAbstractPrintTemplate : public IPrintTemplate
{
    Q_OBJECT

public:
    explicit HAbstractPrintTemplate(QObject *parent = nullptr);
    ~HAbstractPrintTemplate() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QStringList dataType() override;
    void setData(QVariantMap) override;

protected:
    HAbstractPrintTemplate(HAbstractPrintTemplatePrivate &p, QObject *parent = nullptr);

protected:
    virtual bool checkData(QStringList);
    virtual QString toString(QString type);
    virtual QString toStringWhole(QString type);

protected:
    void readSettings();
    void writeSettings();

protected:
    QScopedPointer<HAbstractPrintTemplatePrivate> d_ptr;
};

HE_END_NAMESPACE

