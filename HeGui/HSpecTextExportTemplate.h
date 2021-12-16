/***************************************************************************************************
**      2021-11-02  HSpecTextExportTemplate 光谱数据导出模版。
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractTextExportTemplate.h"

HE_BEGIN_NAMESPACE

class HSpecTextExportTemplatePrivate;

class HSpecTextExportTemplate : public HAbstractTextExportTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecTextExportTemplate)

public:
    explicit HSpecTextExportTemplate(QObject *parent = nullptr);
    ~HSpecTextExportTemplate() override;

public:
    QString typeName() override;

public:
    QString content(bool title = true) override;

protected:
    HSpecTextExportTemplate(HSpecTextExportTemplatePrivate &p, QObject *parent = nullptr);

protected:
    virtual QString parse(QVariantMap, bool title = true);
    virtual QString parse(QVariantList, bool title = true);
    virtual QString parse(QPolygonF);
};

HE_END_NAMESPACE

