/***************************************************************************************************
**      2019-05-16  HSpecSqlPrint 光谱数据库打印。
***************************************************************************************************/

#pragma once

#include "HAbstractSqlPrint.h"

HE_SQL_BEGIN_NAMESPACE

class HSpecSqlPrintPrivate;

class HE_SQL_EXPORT HSpecSqlPrint : public HAbstractSqlPrint
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecSqlPrint)

public:
    explicit HSpecSqlPrint(QObject *parent = nullptr);
    ~HSpecSqlPrint() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HSpecSqlPrint(HSpecSqlPrintPrivate &p, QObject *parent = nullptr);

protected:
    QString textForExcel() override;
    int pageCount() override;
    void paintPage(QPainter *painter, int page) override;
    double paintFooter(QPainter *painter, const QString &text) override;
    void paintBody(QPainter *painter, double y1, double y2, int page) override;

protected:
    QPointF drawChartSpec(QPainter *painter, QRectF rect, QPolygonF poly);
    QPointF drawChartCie(QPainter *painter, QRectF rect, QPointF point);
};

HE_SQL_END_NAMESPACE
