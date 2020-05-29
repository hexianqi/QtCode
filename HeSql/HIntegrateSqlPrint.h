/***************************************************************************************************
**      2020-05-29  HIntegrateSqlPrint 综合数据库打印。
***************************************************************************************************/

#pragma once

#include "HSpecSqlPrint.h"

HE_SQL_BEGIN_NAMESPACE

class HIntegrateSqlPrintPrivate;

class HIntegrateSqlPrint : public HSpecSqlPrint
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIntegrateSqlPrint)

public:
    explicit HIntegrateSqlPrint(QObject *parent = nullptr);
    ~HIntegrateSqlPrint() override;

public:
    QString typeName() override;

protected:
    HIntegrateSqlPrint(HIntegrateSqlPrintPrivate &p, QObject *parent = nullptr);

protected:
    QString textForExcel() override;
    void paintPage(QPainter *painter, int page) override;
    void paintBody(QPainter *painter, double y1, double y2, int page) override;
};

HE_SQL_END_NAMESPACE

