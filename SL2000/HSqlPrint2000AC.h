/***************************************************************************************************
**      2021-04-07  HSqlPrint2000AC
***************************************************************************************************/

#pragma once

#include "HeSql/HSpecSqlPrint.h"

HE_SQL_USE_NAMESPACE

class HSqlPrint2000ACPrivate;

class HSqlPrint2000AC : public HSpecSqlPrint
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSqlPrint2000AC)

public:
    explicit HSqlPrint2000AC(QObject *parent = nullptr);
    ~HSqlPrint2000AC() override;

public:
    QString typeName() override;

protected:
    HSqlPrint2000AC(HSqlPrint2000ACPrivate &p, QObject *parent = nullptr);

protected:
    QString textForExcel() override;
    void paintPage(QPainter *painter, int page) override;
    void paintBody(QPainter *painter, double y1, double y2, int page) override;
};
