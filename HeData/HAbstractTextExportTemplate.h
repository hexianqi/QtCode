/***************************************************************************************************
**      2021-11-02  HAbstractTextExportTemplate 抽象文本导出模版。
***************************************************************************************************/

#pragma once

#include "ITextExportTemplate.h"

HE_DATA_BEGIN_NAMESPACE

class HAbstractTextExportTemplatePrivate;

class HE_DATA_EXPORT HAbstractTextExportTemplate : public QObject, public ITextExportTemplate
{
    Q_OBJECT

public:
    explicit HAbstractTextExportTemplate(QObject *parent = nullptr);
    ~HAbstractTextExportTemplate() override;

public:
    void initialize(QVariantMap param) override;

public:
    QStringList dataType() override;
    void setDataType(QStringList) override;
    void setData(QVariant) override;

protected:
    HAbstractTextExportTemplate(HAbstractTextExportTemplatePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractTextExportTemplatePrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

