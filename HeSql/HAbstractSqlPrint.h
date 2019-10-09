/***************************************************************************************************
**      2019-05-15  HAbstractSqlPrint 抽象数据库打印。
***************************************************************************************************/

#ifndef HABSTRACTSQLPRINT_H
#define HABSTRACTSQLPRINT_H

#include "ISqlPrint.h"

class QPrinter;
class QPainter;

HE_SQL_BEGIN_NAMESPACE

class HAbstractSqlPrintPrivate;

class HE_SQL_EXPORT HAbstractSqlPrint : public ISqlPrint
{
    Q_OBJECT

public:
    explicit HAbstractSqlPrint(QObject *parent = nullptr);
    ~HAbstractSqlPrint() override;

public:
    void setModel(ISqlTableModel *) override;
    void setFieldExportExcel(QStringList value) override;

public:
    void exportExcel() override;
    void exportExcel(int index, int count = -1) override;
    void exportPdf() override;
    void print() override;
    void printPreview() override;

protected:
    HAbstractSqlPrint(HAbstractSqlPrintPrivate &p, QObject *parent = nullptr);

protected:
    virtual bool isValid();
    virtual QVariant recordValue(QString field, int index = -1);
    virtual QString toString(QString field, int index = -1);
    virtual QString toWhole(QString field, int index = -1);
    virtual QPolygonF toPolygonF(QString field, int index = -1);
    virtual QString textForExcel() = 0;
    virtual QString textForExcel(int index, int count);

protected:
    virtual void printPages(QPrinter *printer);
    virtual int pageCount() = 0;
    virtual void paintPage(QPainter *painter, int page) = 0;
    virtual double paintHeader(QPainter *painter, QString text);
    virtual double paintFooter(QPainter *painter, QString text);
    virtual double paintTitle(QPainter *painter, QString text, double y);
    virtual void paintBody(QPainter *painter, double y1, double y2, int page) = 0;

protected:
    QScopedPointer<HAbstractSqlPrintPrivate> d_ptr;
};

HE_SQL_END_NAMESPACE

#endif // HABSTRACTSQLPRINT_H
