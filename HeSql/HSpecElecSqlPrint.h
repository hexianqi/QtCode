/***************************************************************************************************
**      2019-11-22  HSpecElecSqlPrint 光谱加电数据库打印。
***************************************************************************************************/

#pragma once

#include "HSpecSqlPrint.h"

HE_SQL_BEGIN_NAMESPACE

class HSpecElecSqlPrintPrivate;

class HSpecElecSqlPrint : public HSpecSqlPrint
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecElecSqlPrint)

public:
    explicit HSpecElecSqlPrint(QObject *parent = nullptr);
    ~HSpecElecSqlPrint() override;

public:
    QString typeName() override;

protected:
    HSpecElecSqlPrint(HSpecElecSqlPrintPrivate &p, QObject *parent = nullptr);

protected:
    QString textForExcel() override;
    void paintPage(QPainter *painter, int page) override;
    void paintBody(QPainter *painter, double y1, double y2, int page) override;
};

HE_SQL_END_NAMESPACE
