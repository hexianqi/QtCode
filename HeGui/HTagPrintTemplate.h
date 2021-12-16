/***************************************************************************************************
**      2021-11-01  HTagPrintTemplate 标签打印模版
***************************************************************************************************/

#pragma once

#include "HeData/HAbstractPrintTemplate.h"

class QPainter;

HE_BEGIN_NAMESPACE

class HTagPrintTemplatePrivate;

class HTagPrintTemplate : public HAbstractPrintTemplate
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTagPrintTemplate)

public:
    explicit HTagPrintTemplate(QObject *parent = nullptr);
    ~HTagPrintTemplate() override;

public:
    QString typeName() override;

public:
    bool printPages(QPrinter *) override;

protected:
    HTagPrintTemplate(HTagPrintTemplatePrivate &p, QObject *parent = nullptr);

protected:
    void drawText(QPainter *painter, double x1, double y1, double x2, double y2, QString text);

private:
    void init();
};

HE_END_NAMESPACE

