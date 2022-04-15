/***************************************************************************************************
**      2022-04-11  HAngleTextExportTemplate 光强角度数据导出模版。
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractTextExportTemplate.h"

HE_BEGIN_NAMESPACE

class HAngleTextExportTemplatePrivate;

class HAngleTextExportTemplate : public HAbstractTextExportTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleTextExportTemplate)

public:
    explicit HAngleTextExportTemplate(QObject *parent = nullptr);
    ~HAngleTextExportTemplate() override;

public:
    QString typeName() override;

public:
    QString content(bool title = true) override;

protected:
    HAngleTextExportTemplate(HAngleTextExportTemplatePrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

