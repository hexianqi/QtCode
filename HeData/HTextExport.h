/***************************************************************************************************
**      2021-11-02  HTextExport 通用文本导出类。
***************************************************************************************************/

#pragma once

#include "ITextExport.h"

HE_DATA_BEGIN_NAMESPACE

class HTextExportPrivate;

class HTextExport : public QObject, public virtual ITextExport
{
    Q_OBJECT

public:
    explicit HTextExport(QObject *parent = nullptr);
    ~HTextExport() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    ITextExportTemplate *textTemplate() override;
    void setTextTemplate(ITextExportTemplate *) override;
    void setExportPath(const QString &) override;

public:
    bool save() override;
    bool append() override;
    void clear() override;

protected:
    HTextExport(HTextExportPrivate &p, QObject *parent = nullptr);

protected:
    virtual bool isValid();

protected:
    QScopedPointer<HTextExportPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

