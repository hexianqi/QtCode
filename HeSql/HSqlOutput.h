/***************************************************************************************************
**      2021-11-05  HSqlOutput 数据库记录输出类。
***************************************************************************************************/

#pragma once

#include "ISqlOutput.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlOutputPrivate;

class HSqlOutput : public QObject, public virtual ISqlOutput
{
    Q_OBJECT

public:
    explicit HSqlOutput(QObject *parent = nullptr);
    ~HSqlOutput() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setModel(ISqlTableModel *) override;
    void setTextTemplate(ITextExportTemplate *) override;
    void setPrintTemplate(IPrintTemplate *) override;

public:
    void outputExcel() override;
    void outputExcel(int index, int count = -1) override;
    void print() override;
    void printPreview() override;
    void printPdf() override;

protected:
    HSqlOutput(HSqlOutputPrivate &p, QObject *parent = nullptr);

protected:
    virtual bool isValid();
    virtual bool preparePrint();
    virtual void saveExcel(QStringList type, QVariant data);

protected:
    QScopedPointer<HSqlOutputPrivate> d_ptr;
};

HE_SQL_END_NAMESPACE

