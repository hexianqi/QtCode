/***************************************************************************************************
**      2021-01-25  HSqlPrint2100DC
***************************************************************************************************/

#pragma once

#include "HeSql/HSpecSqlPrint.h"

HE_SQL_USE_NAMESPACE

class HSqlPrint2100DCPrivate;

class HSqlPrint2100DC : public HSpecSqlPrint
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSqlPrint2100DC)

public:
    explicit HSqlPrint2100DC(QObject *parent = nullptr);
    ~HSqlPrint2100DC() override;

public:
    QString typeName() override;

protected:
    HSqlPrint2100DC(HSqlPrint2100DCPrivate &, QObject *parent = nullptr);

protected:
    QString textForExcel() override;
    void paintPage(QPainter *painter, int page) override;
    void paintBody(QPainter *painter, double y1, double y2, int page) override;
};



