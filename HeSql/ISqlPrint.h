/***************************************************************************************************
**      2019-05-13  ISqlPrint 数据库记录打印接口。
***************************************************************************************************/

#ifndef ISQLPRINT_H
#define ISQLPRINT_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;

class ISqlPrint : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 设置模型
    virtual void setModel(ISqlTableModel *) = 0;
    // 设置导出Excel字段
    virtual void setFieldExportExcel(QStringList value) = 0;

public:
    // 导出Excel
    virtual void exportExcel() = 0;
    virtual void exportExcel(int index, int count = -1) = 0;
    // 导出Pdf
    virtual void exportPdf() = 0;
    // 打印
    virtual void print() = 0;
    // 打印预览
    virtual void printPreview() = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLPRINT_H
