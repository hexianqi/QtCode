/***************************************************************************************************
**      2021-11-02  HAbstractTextExportTemplate 抽象文本导出模版。
***************************************************************************************************/

#pragma once

#include "ITextExportTemplate.h"

HE_BEGIN_NAMESPACE

class HAbstractTextExportTemplatePrivate;

class HAbstractTextExportTemplate : public QObject, public ITextExportTemplate
{
    Q_OBJECT

public:
    explicit HAbstractTextExportTemplate(QObject *parent = nullptr);
    ~HAbstractTextExportTemplate() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QStringList dataType() override;
    void setDataType(QStringList) override;
    void setData(QVariant) override;

protected:
    HAbstractTextExportTemplate(HAbstractTextExportTemplatePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractTextExportTemplatePrivate> d_ptr;
};

HE_END_NAMESPACE

