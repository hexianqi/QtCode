/***************************************************************************************************
**      2021-10-19  HPrint 通用打印类。
***************************************************************************************************/

#pragma once

#include "IPrint.h"

class QPrinter;

HE_BEGIN_NAMESPACE

class HPrintPrivate;

class HPrint : public QObject, public virtual IPrint
{
    Q_OBJECT

public:
    explicit HPrint(QObject *parent = nullptr);
    ~HPrint() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    IPrintTemplate *printTemplate() override;
    void setPrintTemplate(IPrintTemplate *) override;

public:
    bool print() override;
    bool printPreview() override;
    bool printPdf() override;

protected:
    HPrint(HPrintPrivate &p, QObject *parent = nullptr);

protected:
    virtual bool isValid();
    virtual bool printPages(QPrinter *);

protected:
    QScopedPointer<HPrintPrivate> d_ptr;
};

HE_END_NAMESPACE
